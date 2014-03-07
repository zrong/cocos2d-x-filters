#include "CCShaderFilter.h"

//================== CCShaderFilter

CCShaderFilter::CCShaderFilter()
: shaderName(NULL)
, _pProgram(NULL)
{
}


CCShaderFilter::~CCShaderFilter()
{
	CC_SAFE_RELEASE(_pProgram);
	delete shaderName;
}

CCGLProgram* CCShaderFilter::getProgram()
{
	return _pProgram;
}

void CCShaderFilter::initProgram()
{
	CCGLProgram* __pProgram = CCShaderCache::sharedShaderCache()->programForKey(shaderName);
	CCLOG("CCShaderFilter::initProgram %s", shaderName);
	if (!__pProgram)
	{
		__pProgram = loadShader();
		this->setAttributes(__pProgram);
		CHECK_GL_ERROR_DEBUG();

		__pProgram->link();
		CHECK_GL_ERROR_DEBUG();

		__pProgram->updateUniforms();
		CHECK_GL_ERROR_DEBUG();

		this->setUniforms(__pProgram);
		CHECK_GL_ERROR_DEBUG();

		CCShaderCache::sharedShaderCache()->addProgram(__pProgram, this->shaderName);
		__pProgram->release();
		CCLOG("CCShaderFilter::getProgram1 %d", __pProgram);
	}
	CCLOG("CCShaderFilter::getProgram2 %d", __pProgram);
	if (!_pProgram)
	{
		_pProgram = __pProgram;
		_pProgram->retain();
	}
}

void CCShaderFilter::draw()
{
}

//================== CCGrayFilter

CCGrayFilter* CCGrayFilter::create()
{
	CCGrayFilter* __filter = new CCGrayFilter();
	__filter->autorelease();
	return __filter;
}

CCGrayFilter* CCGrayFilter::create(ccColor4F $param)
{
	CCGrayFilter* __filter = CCGrayFilter::create();
	__filter->setParameter($param);
	return __filter;
}

CCGrayFilter::CCGrayFilter()
: _param(ccc4f(0.299f, 0.587f, 0.114f, 0.0f))
{
	this->shaderName = kCCFilterShader_gray;
}

void CCGrayFilter::setParameter(ccColor4F $param)
{
	_param = $param;
	initProgram();
}

CCGLProgram* CCGrayFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	__p->initWithVertexShaderByteArray(ccFilterShader_gray_vert, ccFilterShader_gray_frag);
	return __p;
}

void CCGrayFilter::setAttributes(CCGLProgram* $cgp)
{
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCGrayFilter::setUniforms(CCGLProgram* $cgp)
{
	int __grayParam = $cgp->getUniformLocationForName("u_grayParam");
	CCLOG("CCGrayFilter::setUniforms, u_grayParam:%d", __grayParam);
	$cgp->setUniformLocationWith4f(__grayParam, _param.r, _param.g, _param.b, _param.a);
}

CCGrayFilter::~CCGrayFilter()
{
}

//================== CCBlurBaseFilter

CCBlurBaseFilter::CCBlurBaseFilter()
: _param(0.1f)
{
}

CCBlurBaseFilter::~CCBlurBaseFilter()
{
}

void CCBlurBaseFilter::setAttributes(CCGLProgram* $cgp)
{
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCBlurBaseFilter::setUniforms(CCGLProgram* $cgp)
{
	int __radius = $cgp->getUniformLocationForName("u_radius");
	//CCLOG("CCShaderFilter::getProgram %d", $cgp);
	$cgp->setUniformLocationWith1f(__radius, _param);
	CCLOG("CCBlurFilter::setUniforms radius:%d", __radius);
}

void CCBlurBaseFilter::setParameter(float $param)
{
	_param = $param;
	CCLOG("CCBlurFilter::setParameter %f", _param);
	initProgram();
}

//================== CCHBlurFilter

CCHBlurFilter* CCHBlurFilter::create()
{
	CCHBlurFilter* __filter = new CCHBlurFilter();
	__filter->autorelease();
	return __filter;
}

CCHBlurFilter* CCHBlurFilter::create(float $param)
{
	CCHBlurFilter* __filter = CCHBlurFilter::create();
	__filter->setParameter($param);
	return __filter;
}

CCHBlurFilter::CCHBlurFilter()
{
	this->shaderName = kCCFilterShader_hblur;
}

CCGLProgram* CCHBlurFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	__p->initWithVertexShaderByteArray(ccFilterShader_blur_vert, ccFilterShader_blur_frag);
	CCLOG("CCHBlurFilter::loadShader %f", _param);
	return __p;
}

//================== CCVBlurFilter

CCVBlurFilter* CCVBlurFilter::create()
{
	CCVBlurFilter* __filter = new CCVBlurFilter();
	__filter->autorelease();
	return __filter;
}

CCVBlurFilter* CCVBlurFilter::create(float $param)
{
	CCVBlurFilter* __filter = CCVBlurFilter::create();
	__filter->setParameter($param);
	return __filter;
}

CCVBlurFilter::CCVBlurFilter()
{
	this->shaderName = kCCFilterShader_vblur;
}

CCGLProgram* CCVBlurFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	__p->initWithVertexShaderByteArray(ccFilterShader_vblur_vert, ccFilterShader_blur_frag);
	CCLOG("CCVBlurFilter::loadShader %f", _param);
	return __p;
}