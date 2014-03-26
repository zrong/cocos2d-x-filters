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
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_gray_frag);
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

CCSharpenFilter* CCSharpenFilter::create(float $sharpness, int $amount)
{
	CCSharpenFilter* __filter = CCSharpenFilter::create();
	__filter->setParameter($sharpness, $amount);
	return __filter;
}

CCSharpenFilter::CCSharpenFilter()
: _sharpness(0.f)
, _widthFactor(0.f)
, _heightFactor(0.f)
, _amount(0)
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
	//The initProgram() will perform in initSprite()
}

void CCSharpenFilter::setParameter(float $sharpness, int $amount)
{
	_sharpness = $sharpness;
	_amount = $amount;
	//The initProgram() will perform in initSprite()
}

void CCSharpenFilter::initSprite(CCFilteredSprite* $sprite)
{
	// If _amount is not 0, then calculate the value of the widthFactor and the heightFactor.
	if (_amount != 0)
	{
		CCSize __size = $sprite->getContentSize();
		_widthFactor = 1.0f / __size.width * _amount;
		_heightFactor = 1.0f / __size.height * _amount;
	}
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
	CCLOG("CCSharpenFilter::setUniforms %d, %d, %d", __sharpness, __widthFactor, __heightFactor);
	$cgp->setUniformLocationWith1f(__sharpness, _sharpness);
	$cgp->setUniformLocationWith1f(__widthFactor, _widthFactor);
	$cgp->setUniformLocationWith1f(__heightFactor, _heightFactor);
	CCLOG("CCSharpenFilter::setUniforms u_sharpness:%.2f, u_widthFactor:%.5f, u_heightFctor:%.5f",
		_sharpness, _widthFactor, _heightFactor);
}

CCSharpenFilter::~CCSharpenFilter()
{

}

//================== CCRGBFilter

CCRGBFilter* CCRGBFilter::create()
{
	CCRGBFilter* __filter = new CCRGBFilter();
	__filter->autorelease();
	return __filter;
}

CCRGBFilter* CCRGBFilter::create(float $readAdj, float $greenAdj, float $blueAdj)
{
	CCRGBFilter* __filter = CCRGBFilter::create();
	__filter->setParameter($readAdj, $greenAdj, $blueAdj);
	return __filter;
}

CCRGBFilter::CCRGBFilter()
: _redAdj(1.f)
, _greenAdj(1.f)
, _blueAdj(1.f)
{
	this->shaderName = kCCFilterShader_rgb;
}

CCGLProgram* CCRGBFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCRGBFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_rgb_frag);
	return __p;
}

void CCRGBFilter::setParameter(float $redAdj, float $greenAdj, float $blueAdj)
{
	_redAdj = $redAdj;
	_greenAdj = $greenAdj;
	_blueAdj = $blueAdj;
	initProgram();
}

void CCRGBFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCRGBFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCRGBFilter::setUniforms(CCGLProgram* $cgp)
{
	int __redAdj = $cgp->getUniformLocationForName("u_redAdj");
	int __greenAdj = $cgp->getUniformLocationForName("u_greenAdj");
	int __blueAdj = $cgp->getUniformLocationForName("u_blueAdj");
	CCLOG("CCRGBFilter::setUniforms %d, %d, %d", __redAdj, __greenAdj, __blueAdj);
	$cgp->setUniformLocationWith1f(__redAdj, _redAdj);
	$cgp->setUniformLocationWith1f(__greenAdj, _greenAdj);
	$cgp->setUniformLocationWith1f(__blueAdj, _blueAdj);
	CCLOG("CCRGBFilter::setUniforms u_redAdj:%.2f, u_greenAdj:%.5f, u_blueAdj:%.5f",
		_redAdj, _greenAdj, _blueAdj);
}


CCRGBFilter::~CCRGBFilter()
{

}

//================== CCBrightnessFilter

CCBrightnessFilter* CCBrightnessFilter::create()
{
	CCBrightnessFilter* __filter = new CCBrightnessFilter();
	__filter->autorelease();
	return __filter;
}

CCBrightnessFilter* CCBrightnessFilter::create(float $brightness)
{
	CCBrightnessFilter* __filter = CCBrightnessFilter::create();
	__filter->setParameter($brightness);
	return __filter;
}

CCBrightnessFilter::CCBrightnessFilter()
: _brightness(0.f)
{
	this->shaderName = kCCFilterShader_brightness;
}

CCGLProgram* CCBrightnessFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCBrightnessFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_brightness_frag);
	return __p;
}

void CCBrightnessFilter::setParameter(float $brightness)
{
	_brightness = MIN(1.f, MAX($brightness, -1.f)); 
	initProgram();
}

void CCBrightnessFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCRGBFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCBrightnessFilter::setUniforms(CCGLProgram* $cgp)
{
	int __brightness = $cgp->getUniformLocationForName("u_brightness");
	CCLOG("CCBrightnessFilter::setUniforms %d", __brightness);
	$cgp->setUniformLocationWith1f(__brightness, _brightness);
	CCLOG("CCBrightnessFilter::setUniforms _brightness:%.2f",_brightness);
}

CCBrightnessFilter::~CCBrightnessFilter()
{

}

//================== CCExposureFilter

CCExposureFilter* CCExposureFilter::create()
{
	CCExposureFilter* __filter = new CCExposureFilter();
	__filter->autorelease();
	return __filter;
}

CCExposureFilter* CCExposureFilter::create(float $brightness)
{
	CCExposureFilter* __filter = CCExposureFilter::create();
	__filter->setParameter($brightness);
	return __filter;
}

CCExposureFilter::CCExposureFilter()
: _param(0.f)
{
	this->shaderName = kCCFilterShader_exposure;
}

CCGLProgram* CCExposureFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCExposureFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_exposure_frag);
	return __p;
}

void CCExposureFilter::setParameter(float $param)
{
	_param = MIN(10.f, MAX($param, -10.f));
	initProgram();
}

void CCExposureFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCExposureFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCExposureFilter::setUniforms(CCGLProgram* $cgp)
{
	int __param = $cgp->getUniformLocationForName("u_exposure");
	CCLOG("CCExposureFilter::setUniforms %d", __param);
	$cgp->setUniformLocationWith1f(__param, _param);
	CCLOG("CCExposureFilter::setUniforms _param:%.2f", _param);
}

CCExposureFilter::~CCExposureFilter()
{

}

//================== CCContrastFilter

CCContrastFilter* CCContrastFilter::create()
{
	CCContrastFilter* __filter = new CCContrastFilter();
	__filter->autorelease();
	return __filter;
}

CCContrastFilter* CCContrastFilter::create(float $brightness)
{
	CCContrastFilter* __filter = CCContrastFilter::create();
	__filter->setParameter($brightness);
	return __filter;
}

CCContrastFilter::CCContrastFilter()
: _param(1.f)
{
	this->shaderName = kCCFilterShader_contrast;
}

CCGLProgram* CCContrastFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCContrastFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_contrast_frag);
	return __p;
}

void CCContrastFilter::setParameter(float $param)
{
	_param = MIN(4.f, MAX($param, 0.f));
	initProgram();
}

void CCContrastFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCContrastFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCContrastFilter::setUniforms(CCGLProgram* $cgp)
{
	int __param = $cgp->getUniformLocationForName("u_contrast");
	CCLOG("CCContrastFilter::setUniforms %d", __param);
	$cgp->setUniformLocationWith1f(__param, _param);
	CCLOG("CCContrastFilter::setUniforms _param:%.2f", _param);
}

CCContrastFilter::~CCContrastFilter()
{

}

//================== CCSaturationFilter

CCSaturationFilter* CCSaturationFilter::create()
{
	CCSaturationFilter* __filter = new CCSaturationFilter();
	__filter->autorelease();
	return __filter;
}

CCSaturationFilter* CCSaturationFilter::create(float $brightness)
{
	CCSaturationFilter* __filter = CCSaturationFilter::create();
	__filter->setParameter($brightness);
	return __filter;
}

CCSaturationFilter::CCSaturationFilter()
: _param(1.f)
{
	this->shaderName = kCCFilterShader_saturation;
}

CCGLProgram* CCSaturationFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCSaturationFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_saturation_frag);
	return __p;
}

void CCSaturationFilter::setParameter(float $param)
{
	_param = MIN(2.f, MAX($param, 0.f));
	initProgram();
}

void CCSaturationFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCSaturationFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCSaturationFilter::setUniforms(CCGLProgram* $cgp)
{
	int __param = $cgp->getUniformLocationForName("u_saturation");
	CCLOG("CCSaturationFilter::setUniforms %d", __param);
	$cgp->setUniformLocationWith1f(__param, _param);
	CCLOG("CCSaturationFilter::setUniforms _param:%.2f", _param);
}

CCSaturationFilter::~CCSaturationFilter()
{

}

//================== CCGammaFilter

CCGammaFilter* CCGammaFilter::create()
{
	CCGammaFilter* __filter = new CCGammaFilter();
	__filter->autorelease();
	return __filter;
}

CCGammaFilter* CCGammaFilter::create(float $brightness)
{
	CCGammaFilter* __filter = CCGammaFilter::create();
	__filter->setParameter($brightness);
	return __filter;
}

CCGammaFilter::CCGammaFilter()
: _param(1.f)
{
	this->shaderName = kCCFilterShader_gamma;
}

CCGLProgram* CCGammaFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCGammaFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_gamma_frag);
	return __p;
}

void CCGammaFilter::setParameter(float $param)
{
	_param = MIN(3.f, MAX($param, 0.f));
	initProgram();
}

void CCGammaFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCGammaFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCGammaFilter::setUniforms(CCGLProgram* $cgp)
{
	int __param = $cgp->getUniformLocationForName("u_gamma");
	CCLOG("CCGammaFilter::setUniforms %d", __param);
	$cgp->setUniformLocationWith1f(__param, _param);
	CCLOG("CCGammaFilter::setUniforms _param:%.2f", _param);
}

CCGammaFilter::~CCGammaFilter()
{

}

//================== CCHueFilter

CCHueFilter* CCHueFilter::create()
{
	CCHueFilter* __filter = new CCHueFilter();
	__filter->autorelease();
	return __filter;
}

CCHueFilter* CCHueFilter::create(float $brightness)
{
	CCHueFilter* __filter = CCHueFilter::create();
	__filter->setParameter($brightness);
	return __filter;
}

CCHueFilter::CCHueFilter()
: _param(0.f)
{
	this->shaderName = kCCFilterShader_hue;
}

CCGLProgram* CCHueFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCHueFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_hue_frag);
	return __p;
}

void CCHueFilter::setParameter(float $param)
{
	_param = fmodf($param, 360.f)*M_PI/180;
	initProgram();
}

void CCHueFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCHueFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCHueFilter::setUniforms(CCGLProgram* $cgp)
{
	int __param = $cgp->getUniformLocationForName("u_hueAdjust");
	CCLOG("CCHueFilter::setUniforms %d", __param);
	$cgp->setUniformLocationWith1f(__param, _param);
	CCLOG("CCHueFilter::setUniforms _param:%.2f", _param);
}

CCHueFilter::~CCHueFilter()
{

}


//================== CCHazeFilter

CCHazeFilter* CCHazeFilter::create()
{
	CCHazeFilter* __filter = new CCHazeFilter();
	__filter->autorelease();
	return __filter;
}

CCHazeFilter* CCHazeFilter::create(float $hazeDistance, float $slope)
{
	CCHazeFilter* __filter = CCHazeFilter::create();
	__filter->setParameter($hazeDistance, $slope);
	return __filter;
}

CCHazeFilter::CCHazeFilter()
: _hazeDistance(0.f)
, _slope(0.f)
{
	this->shaderName = kCCFilterShader_haze;
}

CCGLProgram* CCHazeFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCHazeFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_haze_frag);
	return __p;
}

void CCHazeFilter::setParameter(float $hazeDistance, float $slope)
{
	_hazeDistance = MIN(0.5f, MAX($hazeDistance, -0.5f));
	_slope = MIN(0.5f, MAX($slope, -0.5f));
	initProgram();
}

void CCHazeFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCHazeFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCHazeFilter::setUniforms(CCGLProgram* $cgp)
{
	int __hazeDistance = $cgp->getUniformLocationForName("u_hazeDistance");
	int __slope = $cgp->getUniformLocationForName("u_slope");
	CCLOG("CCHazeFilter::setUniforms %d, %d", __hazeDistance, __slope);
	$cgp->setUniformLocationWith1f(__hazeDistance, _hazeDistance);
	$cgp->setUniformLocationWith1f(__slope, _slope);
	CCLOG("CCHazeFilter::setUniforms _hazeDistance:%.5f, _slope:%.5f", _hazeDistance, _slope);
}

CCHazeFilter::~CCHazeFilter()
{

}

//================== CCZoomBlurFilter

CCZoomBlurFilter* CCZoomBlurFilter::create()
{
	CCZoomBlurFilter* __filter = new CCZoomBlurFilter();
	__filter->autorelease();
	return __filter;
}

CCZoomBlurFilter* CCZoomBlurFilter::create(float $blurSize, float $centerX, float $centerY)
{
	CCZoomBlurFilter* __filter = CCZoomBlurFilter::create();
	__filter->setParameter($blurSize, $centerX, $centerY);
	return __filter;
}

CCZoomBlurFilter::CCZoomBlurFilter()
: _blurSize(1.f)
, _centerX(0.5f)
, _centerY(0.5f)
{
	this->shaderName = kCCFilterShader_zoom_blur;
}

CCGLProgram* CCZoomBlurFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCZoomBlurFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccPositionTexture_vert, ccFilterShader_zoom_blur_frag);
	return __p;
}

void CCZoomBlurFilter::setParameter(float $blurSize, float $centerX, float $centerY)
{
	_blurSize = $blurSize < 0 ? 0.f : $blurSize;
	//_blurSize = MIN(10.f, MAX($blurSize, 0.f));
	//_centerX = MIN(1.f, MAX($centerX, 0.f));
	//_centerY = MIN(1.f, MAX($centerY, 0.f));
	_blurSize = $blurSize;
	_centerX = $centerX;
	_centerY = $centerY;
	initProgram();
}

void CCZoomBlurFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCZoomBlurFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCZoomBlurFilter::setUniforms(CCGLProgram* $cgp)
{
	int __blurSize = $cgp->getUniformLocationForName("u_blurSize");
	int __blurCenter = $cgp->getUniformLocationForName("u_blurCenter");
	CCLOG("CCZoomBlurFilter::setUniforms %d, %d", __blurSize, __blurCenter);
	$cgp->setUniformLocationWith1f(__blurSize, _blurSize);
	$cgp->setUniformLocationWith2f(__blurCenter, _centerX, _centerY);
	CCLOG("CCZoomBlurFilter::setUniforms _blurSize:%.5f, _centerX:%.5f, _centerY:%.5f", _blurSize, _centerX, _centerY);
}

CCZoomBlurFilter::~CCZoomBlurFilter()
{

}


//================== CCMotionBlurFilter

CCMotionBlurFilter* CCMotionBlurFilter::create()
{
	CCMotionBlurFilter* __filter = new CCMotionBlurFilter();
	__filter->autorelease();
	return __filter;
}

CCMotionBlurFilter* CCMotionBlurFilter::create(float $blurSize, float $blurAngle)
{
	CCMotionBlurFilter* __filter = CCMotionBlurFilter::create();
	__filter->setParameter($blurSize, $blurAngle);
	return __filter;
}

CCMotionBlurFilter::CCMotionBlurFilter()
: _blurSize(1.f)
, _blurAngle(0.f)
, _texelOffsetX(0.f)
, _texelOffsetY(0.f)
{
	this->shaderName = kCCFilterShader_motion_blur;
}

CCGLProgram* CCMotionBlurFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCMotionBlurFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccFilterShader_motion_blur_vert, ccFilterShader_motion_blur_frag);
	return __p;
}

void CCMotionBlurFilter::setParameter(float $blurSize, float $blurAngle)
{
	_blurSize = $blurSize < 0 ? 0.f : $blurSize;
	_blurAngle = $blurAngle;
	//The initProgram() will perform in initSprite()
}

void CCMotionBlurFilter::initSprite(CCFilteredSprite* $sprite)
{
	float __aspectRatio = 1.0f;
	CCSize __size = $sprite->getContentSize();
	__aspectRatio = __size.height / __size.width;
	_texelOffsetX = _blurSize*cos(_blurAngle*M_PI / 180.0f) / __size.width;
	_texelOffsetY = _blurSize*sin(_blurAngle*M_PI / 180.0f) / __size.width;
	initProgram();
}

void CCMotionBlurFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCMotionBlurFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
}

void CCMotionBlurFilter::setUniforms(CCGLProgram* $cgp)
{
	int __directionalTexelStep = $cgp->getUniformLocationForName("u_directionalTexelStep");
	CCLOG("CCMotionBlurFilter::setUniforms %d", __directionalTexelStep);
	$cgp->setUniformLocationWith2f(__directionalTexelStep, _texelOffsetX, _texelOffsetY);
	CCLOG("CCMotionBlurFilter::setUniforms _blurSize:%.5f,_blurAngle:%.5f, _texelOffsetX:%.5f, _texelOffsetY:%.5f", 
		_blurSize, _blurAngle, _texelOffsetX, _texelOffsetY);
}

CCMotionBlurFilter::~CCMotionBlurFilter()
{

}


//================== CCDropShadowFilter

CCDropShadowFilter* CCDropShadowFilter::create()
{
	CCDropShadowFilter* __filter = new CCDropShadowFilter();
	__filter->autorelease();
	return __filter;
}

CCDropShadowFilter* CCDropShadowFilter::create(float $resolation)
{
	CCDropShadowFilter* __filter = CCDropShadowFilter::create();
	__filter->setParameter($resolation);
	return __filter;
}

CCDropShadowFilter::CCDropShadowFilter()
{
	this->shaderName = kCCFilterShader_drop_shadow_blur;
}

CCGLProgram* CCDropShadowFilter::loadShader()
{
	CCGLProgram* __p = new CCGLProgram();
	CCLOG("CCDropShadowFilter::loadShader, program:%d", __p);
	__p->initWithVertexShaderByteArray(ccFilterShader_drop_shadow_vert, ccFilterShader_drop_shadow_frag);
	return __p;
}

void CCDropShadowFilter::setParameter(float $resolation)
{
	//The initProgram() will perform in initSprite()
}

void CCDropShadowFilter::initSprite(CCFilteredSprite* $sprite)
{
	float __aspectRatio = 1.0f;
	CCSize __size = $sprite->getContentSize();
	/*_textureWidth = __size.width;
	_textureHeight = __size.height;*/
	_textureWidth = 480;
	_textureHeight = 320;
	initProgram();
}

void CCDropShadowFilter::setAttributes(CCGLProgram* $cgp)
{
	CCLOG("CCDropShadowFilter::setAttributes");
	$cgp->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	$cgp->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	$cgp->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
}

void CCDropShadowFilter::setUniforms(CCGLProgram* $cgp)
{
	int u_resolution = $cgp->getUniformLocationForName("u_resolution");
	CCLOG("CCDropShadowFilter::setUniforms %d", u_resolution);
	$cgp->setUniformLocationWith2f(u_resolution, _textureWidth, _textureHeight);
	CCLOG("CCDropShadowFilter::setUniforms _textureWidth:%.5f,_textureHeight:%.5f",
		_textureWidth, _textureHeight);
}

CCDropShadowFilter::~CCDropShadowFilter()
{

}