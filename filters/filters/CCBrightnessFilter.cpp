#include "CCBrightnessFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN
//================== BrightnessFilter

BrightnessFilter* BrightnessFilter::create()
{
	BrightnessFilter* filter = new BrightnessFilter();
	filter->autorelease();
	return filter;
}

BrightnessFilter* BrightnessFilter::create(float brightness)
{
	BrightnessFilter* filter = BrightnessFilter::create();
	filter->setParameter(brightness);
	return filter;
}

BrightnessFilter::BrightnessFilter()
{
	this->shaderName = kCCFilterShader_brightness;
	_param = 0.f;
}

GLProgram* BrightnessFilter::loadShader()
{
    GLProgram* p = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_brightness_frag);
    
//	GLProgram* p = new GLProgram();
//	p->initWithByteArrays(ccPositionTexture_vert, ccFilterShader_brightness_frag);
	return p;
}

void BrightnessFilter::setParameter(float brightness)
{
	_param = MIN(1.f, MAX(brightness, -1.f));
	initProgram();
}

void BrightnessFilter::setAttributes(GLProgram* cgp)
{
	//CCLOG("CCRGBFilter::setAttributes");
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
}

void BrightnessFilter::setUniforms(GLProgram* cgp)
{
//	int u_brightness = cgp->getUniformLocationForName("u_brightness");
//	cgp->setUniformLocationWith1f(u_brightness, _param);
    
    _pProgramState->setUniformFloat("u_brightness", _param);
}
NS_CC_EXT_END