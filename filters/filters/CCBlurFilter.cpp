#include "CCBlurFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== BlurBaseFilter

BlurBaseFilter::BlurBaseFilter()
: _param(0.1f)
{
}

void BlurBaseFilter::setAttributes(GLProgram* cgp)
{
	//CCLOG("BlurBaseFilter::setAttributes");
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
}

void BlurBaseFilter::setUniforms(GLProgram* cgp)
{
//	int radius = cgp->getUniformLocationForName("u_radius");
//	cgp->setUniformLocationWith1f(radius, _param);
    
    _pProgramState->setUniformFloat("u_radius", _param);
}

void BlurBaseFilter::setParameter(float param)
{
	_param = param;
	//CCLOG("BlurBaseFilter::setParameter %f", _param);
	initProgram();
}

//================== HBlurFilter

HBlurFilter* HBlurFilter::create()
{
	HBlurFilter* filter = new HBlurFilter();
	filter->autorelease();
	return filter;
}

HBlurFilter* HBlurFilter::create(float param)
{
	HBlurFilter* filter = HBlurFilter::create();
	filter->setParameter(param);
	return filter;
}

HBlurFilter::HBlurFilter()
{
	this->shaderName = kCCFilterShader_hblur;
}

GLProgram* HBlurFilter::loadShader()
{
    GLProgram* p = GLProgram::createWithByteArrays(ccFilterShader_hblur_vert, ccFilterShader_blur_frag);
//	GLProgram* p = new GLProgram();
//	p->initWithByteArrays(ccFilterShader_hblur_vert, ccFilterShader_blur_frag);
	//CCLOG("HBlurFilter::loadShader %f", _param);
	return p;
}

//================== VBlurFilter

VBlurFilter* VBlurFilter::create()
{
	VBlurFilter* filter = new VBlurFilter();
	filter->autorelease();
	return filter;
}

VBlurFilter* VBlurFilter::create(float param)
{
	VBlurFilter* filter = VBlurFilter::create();
	filter->setParameter(param);
	return filter;
}

VBlurFilter::VBlurFilter()
{
	this->shaderName = kCCFilterShader_vblur;
}

GLProgram* VBlurFilter::loadShader()
{
    GLProgram* p = GLProgram::createWithByteArrays(ccFilterShader_vblur_vert, ccFilterShader_blur_frag);
//	GLProgram* p = new GLProgram();
//	p->initWithByteArrays(ccFilterShader_vblur_vert, ccFilterShader_blur_frag);

	return p;
}

//================== GaussianHBlurFilter

GaussianHBlurFilter* GaussianHBlurFilter::create()
{
	GaussianHBlurFilter* filter = new GaussianHBlurFilter();
	filter->autorelease();
	return filter;
}

GaussianHBlurFilter* GaussianHBlurFilter::create(float param)
{
	GaussianHBlurFilter* filter = GaussianHBlurFilter::create();
	filter->setParameter(param);
	return filter;
}

GaussianHBlurFilter::GaussianHBlurFilter()
: _resolation(800.f)
{
	this->shaderName = kCCFilterShader_gaussian_hblur;
}

GLProgram* GaussianHBlurFilter::loadShader()
{
    GLProgram* p = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_gaussian_hblur_frag);
//	GLProgram* p = new GLProgram();
//	p->initWithByteArrays(ccPositionTextureColor_vert,
//		ccFilterShader_gaussian_hblur_frag);
	return p;
}

void GaussianHBlurFilter::setUniforms(GLProgram* cgp)
{
	BlurBaseFilter::setUniforms(cgp);

//	int u_resolution = cgp->getUniformLocationForName("u_resolution");
//	cgp->setUniformLocationWith1f(u_resolution, _resolation);
    
    _pProgramState->setUniformFloat("u_resolution", _resolation);
}

void GaussianHBlurFilter::initSprite(FilteredSprite* sprite)
{
	//_resolation = sprite->getContentSize().width;
	_resolation = 1024;
	//CCLOG("GaussianHBlurFilter.initSprite resulation:%f", _resolation);
    BlurBaseFilter::initSprite(nullptr);
}

//================== GaussianVBlurFilter

GaussianVBlurFilter* GaussianVBlurFilter::create()
{
	GaussianVBlurFilter* filter = new GaussianVBlurFilter();
	filter->autorelease();
	return filter;
}

GaussianVBlurFilter* GaussianVBlurFilter::create(float param)
{
	GaussianVBlurFilter* filter = GaussianVBlurFilter::create();
	filter->setParameter(param);
	return filter;
}

GaussianVBlurFilter::GaussianVBlurFilter()
: _resolation(800.f)
{
	this->shaderName = kCCFilterShader_gaussian_vblur;
}

GLProgram* GaussianVBlurFilter::loadShader()
{
    GLProgram* p = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_gaussian_vblur_frag);
//	GLProgram* p = new GLProgram();
//	p->initWithByteArrays(ccPositionTextureColor_vert,
//		ccFilterShader_gaussian_vblur_frag);
	return p;
}

void GaussianVBlurFilter::setUniforms(GLProgram* cgp)
{
	BlurBaseFilter::setUniforms(cgp);

//	int u_resolution = cgp->getUniformLocationForName("u_resolution");
//	cgp->setUniformLocationWith1f(u_resolution, _resolation);
    
    _pProgramState->setUniformFloat("u_resolution", _resolation);
}

void GaussianVBlurFilter::initSprite(FilteredSprite* sprite)
{
	//_resolation = sprite->getContentSize().height;
	_resolation = 1024;
	//CCLOG("GaussianVBlurFilter.initSprite resulation:%f", _resolation);
    BlurBaseFilter::initSprite(nullptr);
}

//================== ZoomBlurFilter

ZoomBlurFilter* ZoomBlurFilter::create()
{
	ZoomBlurFilter* filter = new ZoomBlurFilter();
	filter->autorelease();
	return filter;
}

ZoomBlurFilter* ZoomBlurFilter::create(float blurSize, float centerX, float centerY)
{
	ZoomBlurFilter* filter = ZoomBlurFilter::create();
	filter->setParameter(blurSize, centerX, centerY);
	return filter;
}

ZoomBlurFilter::ZoomBlurFilter()
: _blurSize(1.f)
, _centerX(0.5f)
, _centerY(0.5f)
{
	this->shaderName = kCCFilterShader_zoom_blur;
}

GLProgram* ZoomBlurFilter::loadShader()
{
    GLProgram* p = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_zoom_blur_frag);
    
//	GLProgram* p = new GLProgram();
//	p->initWithByteArrays(ccPositionTexture_vert, ccFilterShader_zoom_blur_frag);
	return p;
}

void ZoomBlurFilter::setParameter(float blurSize, float centerX, float centerY)
{
	_blurSize = blurSize < 0 ? 0.f : blurSize;
	//_blurSize = MIN(10.f, MAX(blurSize, 0.f));
	//_centerX = MIN(1.f, MAX(centerX, 0.f));
	//_centerY = MIN(1.f, MAX(centerY, 0.f));
	_blurSize = blurSize;
	_centerX = centerX;
	_centerY = centerY;
	initProgram();
}

void ZoomBlurFilter::setAttributes(GLProgram* cgp)
{
	//CCLOG("ZoomBlurFilter::setAttributes");
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
}

void ZoomBlurFilter::setUniforms(GLProgram* cgp)
{
//	int blurSize = cgp->getUniformLocationForName("u_blurSize");
//	int blurCenter = cgp->getUniformLocationForName("u_blurCenter");
//	cgp->setUniformLocationWith1f(blurSize, _blurSize);
//	cgp->setUniformLocationWith2f(blurCenter, _centerX, _centerY);
    
    _pProgramState->setUniformFloat("u_blurSize", _blurSize);
    _pProgramState->setUniformVec2("u_blurCenter", Vec2(_centerX, _centerY));
}

//================== MotionBlurFilter

MotionBlurFilter* MotionBlurFilter::create()
{
	MotionBlurFilter* filter = new MotionBlurFilter();
	filter->autorelease();
	return filter;
}

MotionBlurFilter* MotionBlurFilter::create(float blurSize, float blurAngle)
{
	MotionBlurFilter* filter = MotionBlurFilter::create();
	filter->setParameter(blurSize, blurAngle);
	return filter;
}

MotionBlurFilter::MotionBlurFilter()
: _blurSize(1.f)
, _blurAngle(0.f)
, _texelOffsetX(0.f)
, _texelOffsetY(0.f)
{
	this->shaderName = kCCFilterShader_motion_blur;
}

GLProgram* MotionBlurFilter::loadShader()
{
    GLProgram* p = GLProgram::createWithByteArrays(ccFilterShader_motion_blur_vert, ccFilterShader_motion_blur_frag);
    
//	GLProgram* p = new GLProgram();
//	p->initWithByteArrays(ccFilterShader_motion_blur_vert, ccFilterShader_motion_blur_frag);
	return p;
}

void MotionBlurFilter::setParameter(float blurSize, float blurAngle)
{
	_blurSize = blurSize < 0 ? 0.f : blurSize;
	_blurAngle = blurAngle;
	//The initProgram() will perform in initSprite()
}

void MotionBlurFilter::initSprite(FilteredSprite* sprite)
{
	float aspectRatio = 1.0f;
	Size size = sprite->getContentSize();
	aspectRatio = size.height / size.width;
	_texelOffsetX = _blurSize*cos(_blurAngle*M_PI / 180.0f) / size.width;
	_texelOffsetY = _blurSize*sin(_blurAngle*M_PI / 180.0f) / size.width;
	initProgram();
    
    Filter::initSprite(nullptr);
}

void MotionBlurFilter::setAttributes(GLProgram* cgp)
{
	//CCLOG("MotionBlurFilter::setAttributes");
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
}

void MotionBlurFilter::setUniforms(GLProgram* cgp)
{
//	int directionalTexelStep = cgp->getUniformLocationForName("u_directionalTexelStep");
//	cgp->setUniformLocationWith2f(directionalTexelStep, _texelOffsetX, _texelOffsetY);
    
    _pProgramState->setUniformVec2("u_directionalTexelStep", Vec2(_texelOffsetX, _texelOffsetY));
}

NS_CC_EXT_END