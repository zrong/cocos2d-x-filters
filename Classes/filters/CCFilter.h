#ifndef __CCSHADER_FILTER_H__
#define __CCSHADER_FILTER_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "CCGL.h"
#include "shaders/ccFilterShaders.h"

USING_NS_CC;

NS_CC_EXT_BEGIN

class CCFilteredSprite;

//================== CCFilter

class CCFilter :	public CCObject
{
public:
	CCFilter();
	~CCFilter();

	virtual void initSprite(CCFilteredSprite* $sprite);
	virtual void draw();
	CCGLProgram* getProgram();

	const char* shaderName;
protected:
	CCGLProgram* _pProgram;
	void initProgram();
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
};

class CCSingleFloatParamFilter : public CCFilter
{
public:
	CCSingleFloatParamFilter();

	virtual void setParameter(float $param);
protected:
	float _param;
};


//================== CCBlurFilter

class CCBlurBaseFilter : public CCFilter
{
	
public:
	CCBlurBaseFilter();
	~CCBlurBaseFilter();

	void setParameter(float $param);
protected:
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _param;
};

class CCHBlurFilter : public CCBlurBaseFilter
{
public:
	static CCHBlurFilter* create();
	static CCHBlurFilter* create(float $param);

	CCHBlurFilter();
protected:
	virtual CCGLProgram* loadShader();
	
};

class CCVBlurFilter : public CCBlurBaseFilter
{
public:
	static CCVBlurFilter* create();
	static CCVBlurFilter* create(float $param);

	CCVBlurFilter();
protected:
	virtual CCGLProgram* loadShader();
};

class CCGaussianHBlurFilter : public CCBlurBaseFilter
{
public:
	static CCGaussianHBlurFilter* create();
	static CCGaussianHBlurFilter* create(float $param);

	CCGaussianHBlurFilter();
protected:
	virtual CCGLProgram* loadShader();
	virtual void setUniforms(CCGLProgram* $glp);
};

class CCGaussianVBlurFilter : public CCBlurBaseFilter
{
public:
	static CCGaussianVBlurFilter* create();
	static CCGaussianVBlurFilter* create(float $param);

	CCGaussianVBlurFilter();
protected:
	virtual CCGLProgram* loadShader();
	virtual void setUniforms(CCGLProgram* $glp);
};

//================== CCMaskFilter

class CCMaskFilter : public CCFilter
{

public:
	static CCMaskFilter* create();
	static CCMaskFilter* create(CCString* $maskImage);
	static CCMaskFilter* createWithSpriteFrameName(CCString* $maskImage);

	CCMaskFilter();
	~CCMaskFilter();

	void setParameter(CCString* $param);
	virtual void initSprite(CCFilteredSprite* $sprite);
	inline void setIsSpriteFrame(bool $isSpriteFrame){ _isSpriteFrame = $isSpriteFrame; };
protected:
	void initProgram();
	CCString* _param;
	bool _isSpriteFrame;
	
};

//================== CCSharpenFilter

class CCSharpenFilter : public CCFilter
{

public:
	static CCSharpenFilter* create();
	static CCSharpenFilter* create(float $sharpness, float $widthFactor, float $heightFactor);
	static CCSharpenFilter* create(float $sharpness, int $amount);

	CCSharpenFilter();
	~CCSharpenFilter();

	void setParameter(float $sharpness, float $widthFactor, float $heightFactor);
	void setParameter(float $sharpness, int $amount);
	virtual void initSprite(CCFilteredSprite* $sprite);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _sharpness;
	float _widthFactor;
	float _heightFactor;
	int _amount;

};

//================== CCRGBFilter

class CCRGBFilter : public CCFilter
{

public:
	static CCRGBFilter* create();
	static CCRGBFilter* create(float $redAdj, float $greenAdj, float $blueAdj);

	CCRGBFilter();
	~CCRGBFilter();

	void setParameter(float $redAdj, float $greenAdj, float $blueAdj);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _redAdj;
	float _greenAdj;
	float _blueAdj;
};


//================== CCBrightnessFilter

class CCBrightnessFilter : public CCFilter
{

public:
	static CCBrightnessFilter* create();
	static CCBrightnessFilter* create(float $brightness);

	CCBrightnessFilter();
	~CCBrightnessFilter();

	void setParameter(float $brightness);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _brightness;
};

//================== CCExposureFilter

class CCExposureFilter : public CCFilter
{

public:
	static CCExposureFilter* create();
	static CCExposureFilter* create(float $param);

	CCExposureFilter();
	~CCExposureFilter();

	void setParameter(float $param);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _param;
};


//================== CCContrastFilter

class CCContrastFilter : public CCFilter
{

public:
	static CCContrastFilter* create();
	static CCContrastFilter* create(float $param);

	CCContrastFilter();
	~CCContrastFilter();

	void setParameter(float $param);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _param;
};

//================== CCSaturationFilter

class CCSaturationFilter : public CCFilter
{

public:
	static CCSaturationFilter* create();
	static CCSaturationFilter* create(float $param);

	CCSaturationFilter();
	~CCSaturationFilter();

	void setParameter(float $param);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _param;
};

//================== CCGammaFilter

class CCGammaFilter : public CCFilter
{

public:
	static CCGammaFilter* create();
	static CCGammaFilter* create(float $param);

	CCGammaFilter();
	~CCGammaFilter();

	void setParameter(float $param);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _param;
};

//================== CCHueFilter

class CCHueFilter : public CCFilter
{

public:
	static CCHueFilter* create();
	static CCHueFilter* create(float $param);

	CCHueFilter();
	~CCHueFilter();

	void setParameter(float $param);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _param;
};

//================== CCHazeFilter

class CCHazeFilter : public CCFilter
{

public:
	static CCHazeFilter* create();
	static CCHazeFilter* create(float $hazeDistance, float $slope);

	CCHazeFilter();
	~CCHazeFilter();

	void setParameter(float $hazeDistance, float $slope);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _hazeDistance;
	float _slope;
};

//================== CCZoomBlurFilter

class CCZoomBlurFilter : public CCFilter
{

public:
	static CCZoomBlurFilter* create();
	static CCZoomBlurFilter* create(float $blurSize, float $centerX, float $centerY);

	CCZoomBlurFilter();
	~CCZoomBlurFilter();

	void setParameter(float $blurSize, float $centerX, float $centerY);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _blurSize;
	float _centerX;
	float _centerY;
};

//================== CCMotionBlurFilter

class CCMotionBlurFilter : public CCFilter
{

public:
	static CCMotionBlurFilter* create();
	static CCMotionBlurFilter* create(float $blurSize, float $blurAngle);

	CCMotionBlurFilter();
	~CCMotionBlurFilter();

	void setParameter(float $blurSize, float $blurAngle);
	virtual void initSprite(CCFilteredSprite* $sprite);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _blurSize;
	float _blurAngle;
	float _texelOffsetX;
	float _texelOffsetY;
};

//================== CCDropShadowFilter

class CCDropShadowFilter : public CCFilter
{

public:
	static CCDropShadowFilter* create();
	static CCDropShadowFilter* create(float $resolation);

	CCDropShadowFilter();
	~CCDropShadowFilter();

	void setParameter(float $resolation);
	virtual void initSprite(CCFilteredSprite* $sprite);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _textureWidth;
	float _textureHeight;
};


//================== CCSepiaFilter

class CCSepiaFilter : public CCFilter
{

public:
	static CCSepiaFilter* create();
	static CCSepiaFilter* create(float $resolation);

	CCSepiaFilter();
	~CCSepiaFilter();

	void setParameter();
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
};

//================== CCTestFilter

class CCTestFilter : public CCFilter
{

public:
	static CCTestFilter* create();
	static CCTestFilter* create(float $resolation);

	CCTestFilter();
	~CCTestFilter();

	void setParameter(float $resolation);
	virtual void initSprite(CCFilteredSprite* $sprite);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	float _textureWidth;
	float _textureHeight;
};


NS_CC_EXT_END

#endif /* __CCSHADER_FILTER_H__ */
