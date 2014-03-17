#include "CCShaderFilter.h"
#include "CCFilteredSprite.h"

//================== CCShaderFilter

CCShaderFilter::CCShaderFilter()
: shaderName(NULL)
, _pProgram(NULL)
{
}


CCShaderFilter::~CCShaderFilter()
{
	CC_SAFE_RELEASE(_pProgram);
}

CCGLProgram* CCShaderFilter::getProgram()
{
	return _pProgram;
}

void CCShaderFilter::initProgram()
{
	CCGLProgram* __pProgram = CCShaderCache::sharedShaderCache()->programForKey(shaderName);
	CCLOG("CCShaderFilter::initProgram %s, program:%d", shaderName, __pProgram);
	if (!__pProgram)
	{
		__pProgram = loadShader();
		CCLOG("CCShaderFilter::initProgram %s, after loadShader program:%d", shaderName, __pProgram);
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

void CCShaderFilter::initSprite(CCFilteredSprite* $sprite)
{
}

void CCShaderFilter::draw()
{
}

CCGLProgram* CCShaderFilter::loadShader()
{
	CCLOG("CCShaderFilter::loadShader");
	return NULL;
}

void CCShaderFilter::setAttributes(CCGLProgram* $glp)
{
}

void CCShaderFilter::setUniforms(CCGLProgram* $glp)
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
	CCLOG("CCBlurBaseFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCBlurBaseFilter::setUniforms(CCGLProgram* $cgp)
{
	int __radius = $cgp->getUniformLocationForName("u_radius");
	//CCLOG("CCShaderFilter::getProgram %d", $cgp);
	$cgp->setUniformLocationWith1f(__radius, _param);
	CCLOG("CCBlurBaseFilter::setUniforms radius:%d", __radius);
}

void CCBlurBaseFilter::setParameter(float $param)
{
	_param = $param;
	CCLOG("CCBlurBaseFilter::setParameter %f", _param);
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
	__p->initWithVertexShaderByteArray(ccFilterShader_hblur_vert, ccFilterShader_blur_frag);
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

//================== CCGaussianHBlurFilter

CCGaussianHBlurFilter* CCGaussianHBlurFilter::create()
{
	CCGaussianHBlurFilter* __filter = new CCGaussianHBlurFilter();
	__filter->autorelease();
	return __filter;
}

CCGaussianHBlurFilter* CCGaussianHBlurFilter::create(float $param)
{
	CCGaussianHBlurFilter* __filter = CCGaussianHBlurFilter::create();
	__filter->setParameter($param);
	return __filter;
}

CCGaussianHBlurFilter::CCGaussianHBlurFilter()
{
	this->shaderName = kCCFilterShader_gaussian_hblur;
}

CCGLProgram* CCGaussianHBlurFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCGaussianHBlurFilter::loadShader %f, program:%d", _param, __p);
	__p->initWithVertexShaderByteArray(ccFilterShader_gaussian_hblur_vert, ccFilterShader_gaussian_hblur_frag);
	return __p;
	//return NULL;
}

void CCGaussianHBlurFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCBlurBaseFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCGaussianHBlurFilter::setUniforms(CCGLProgram* $cgp)
{
	int __radius = $cgp->getUniformLocationForName("u_radius");
	//CCLOG("CCShaderFilter::getProgram %d", $cgp);
	$cgp->setUniformLocationWith1f(__radius, _param);
	CCLOG("CCGaussianHBlurFilter::setUniforms radius:%d", __radius);
}

void CCGaussianHBlurFilter::setParameter(float $param)
{
	_param = $param;
	//initProgram();
}

void CCGaussianHBlurFilter::initSprite(CCFilteredSprite* $sprite)
{

	ccBlendFunc __maskBF = { GL_ONE, GL_ONE };
	ccBlendFunc __imgBF = { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA };

	CCSprite* __pMask = CCSprite::createWithTexture($sprite->getTexture());
	__pMask->setAnchorPoint(ccp(0, 0));
	__pMask->setPosition(ccp(0, 0));

	CCSprite* __pImg = CCSprite::createWithTexture($sprite->getTexture());
	__pImg->setAnchorPoint(ccp(0, 0));
	__pImg->setPosition(ccp(0, 0));

	__pMask->setBlendFunc(__maskBF);
	__pImg->setBlendFunc(__imgBF);

	CCSize __size = __pImg->getContentSize();
	CCRenderTexture* __pRender = CCRenderTexture::create(__size.width, __size.height);
	__pRender->begin();
	__pMask->visit();
	__pImg->visit();
	__pRender->end();

	CCTexture2D* __pTex = new CCTexture2D();
	__pTex->initWithImage(__pRender->newCCImage(true));
	__pTex->autorelease();
	$sprite->setTexture(__pTex);
}

//================== CCMaskFilter

CCMaskFilter* CCMaskFilter::create()
{
	CCMaskFilter* __filter = new CCMaskFilter();
	__filter->autorelease();
	return __filter;
}

CCMaskFilter* CCMaskFilter::create(CCString* $maskImage)
{
	CCMaskFilter* __filter = CCMaskFilter::create();
	__filter->setParameter($maskImage);
	return __filter;
}

CCMaskFilter::CCMaskFilter()
: _param(NULL)
{
	this->shaderName = NULL;
}

void CCMaskFilter::initProgram()
{
	//Do nothing in CCMaskFilter
	CCLOG("CCMaskFilter initProgram");
}

void CCMaskFilter::initSprite(CCFilteredSprite* $sprite)
{
	CCLOG("CCMaskFilter initSprite maskImage:%s", _param->getCString());
	ccBlendFunc __maskBF = { GL_ONE, GL_ZERO };
	ccBlendFunc __imgBF = { GL_DST_ALPHA, GL_ZERO };

	CCSprite* __pMask = CCSprite::create(_param->getCString());
	__pMask->setAnchorPoint(ccp(0, 0));
	__pMask->setPosition(ccp(0, 0));

	CCSprite* __pImg = CCSprite::createWithTexture($sprite->getTexture());
	__pImg->setAnchorPoint(ccp(0, 0));
	__pImg->setPosition(ccp(0, 0));

	__pMask->setBlendFunc(__maskBF);
	__pImg->setBlendFunc(__imgBF);
	
	CCSize __size = __pImg->getContentSize();
	CCRenderTexture* __pRender = CCRenderTexture::create(__size.width, __size.height);
	__pRender->begin();
	__pMask->visit();
	__pImg->visit();
	__pRender->end();

	CCTexture2D* __pTex = new CCTexture2D();
	__pTex->initWithImage(__pRender->newCCImage(true));
	__pTex->autorelease();
	$sprite->setTexture(__pTex);
}

void CCMaskFilter::setParameter(CCString* $maskImage)
{
	_param = $maskImage;
}

CCMaskFilter::~CCMaskFilter()
{
}

//================== CCSharpenFilter

CCSharpenFilter* CCSharpenFilter::create()
{
	CCSharpenFilter* __filter = new CCSharpenFilter();
	__filter->autorelease();
	return __filter;
}

CCSharpenFilter* CCSharpenFilter::create(float $sharpness, float $widthFactor, float $heightFactor)
{
	CCSharpenFilter* __filter = CCSharpenFilter::create();
	__filter->setParameter($sharpness, $widthFactor, $heightFactor);
	return __filter;
}

CCSharpenFilter::CCSharpenFilter()
: _sharpness(0.f)
, _widthFactor(0.f)
, _heightFactor(0.f)
{
	this->shaderName = kCCFilterShader_sharpen;
}

CCGLProgram* CCSharpenFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCSharpenFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccFilterShader_sharpen_vert, ccFilterShader_sharpen_frag);
	return __p;
}

void CCSharpenFilter::setParameter(float $sharpness, float $widthFactor, float $heightFactor)
{
	_sharpness = $sharpness;
	_widthFactor = $widthFactor;
	_heightFactor = $heightFactor;
	initProgram();
}

void CCSharpenFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCBlurBaseFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCSharpenFilter::setUniforms(CCGLProgram* $cgp)
{
	int __sharpness = $cgp->getUniformLocationForName("u_sharpness");
	int __widthFactor = $cgp->getUniformLocationForName("u_widthFactor");
	int __heightFactor = $cgp->getUniformLocationForName("u_heightFactor");
	//CCLOG("CCSharpenFilter::getProgram %d", $cgp);
	$cgp->setUniformLocationWith1f(__sharpness, _sharpness);
	$cgp->setUniformLocationWith1f(__widthFactor, _widthFactor);
	$cgp->setUniformLocationWith1f(__heightFactor, _heightFactor);
	CCLOG("CCSharpenFilter::setUniforms u_sharpness:%.2f, u_widthFactor:%.2f, u_heightFctor:%.2f",
		_sharpness, _widthFactor, _heightFactor);
}


CCSharpenFilter::~CCSharpenFilter()
{

}