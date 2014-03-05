#include "CCShaderFilter.h"

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
	initProgram();
}

void CCGrayFilter::setParameter(ccColor4F $param)
{
	_param = $param;
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

CCBlurFilter* CCBlurFilter::create()
{
	CCBlurFilter* __filter = new CCBlurFilter();
	__filter->autorelease();
	return __filter;
}

CCBlurFilter* CCBlurFilter::create(float $param)
{
	CCBlurFilter* __filter = CCBlurFilter::create();
	__filter->setParameter($param);
	return __filter;
}

void CCBlurFilter::setParameter(float $param)
{
	_param = $param;
}

CCBlurFilter::CCBlurFilter()
: _param(0.1f)
{
	this->shaderName = kCCFilterShader_blur;
	initProgram();
}

CCGLProgram* CCBlurFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	__p->initWithVertexShaderByteArray(ccFilterShader_blur_vert, ccFilterShader_blur_frag);
	return __p;
}

void CCBlurFilter::setAttributes(CCGLProgram* $cgp)
{
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCBlurFilter::setUniforms(CCGLProgram* $cgp)
{
	int __radius = $cgp->getUniformLocationForName("u_radius");
	//CCLOG("CCShaderFilter::getProgram %d", $cgp);
	$cgp->setUniformLocationWith1f(__radius, _param);
	CCLOG("GOGOG %d", __radius);
}

CCBlurFilter::~CCBlurFilter()
{
}