#ifndef __CCSHADER_FILTER_H__
#define __CCSHADER_FILTER_H__

#include "cocos2d.h"
#include "CCGL.h"
#include "ccFilterShaders.h"

#define kCCFilterShader_gray	"ccFilterShader_gray"
#define kCCFilterShader_hblur	"ccFilterShader_hblur"
#define kCCFilterShader_vblur	"ccFilterShader_vblur"
#define kCCFilterShader_gaussian_hblur	"ccFilterShader_gaussian_hblur"
#define kCCFilterShader_gaussian_vblur	"ccFilterShader_gaussian_vblur"
#define kCCFilterShader_sharpen	"ccFilterShader_sharpen"
#define kCCFilterShader_rgb	"ccFilterShader_rgb"
#define kCCFilterShader_brightness	"ccFilterShader_brightness"

USING_NS_CC;

class CCFilteredSprite;

//================== CCShaderFilter

class CCShaderFilter :	public CCObject
{
public:
	CCShaderFilter();
	~CCShaderFilter();

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

//================== CCGrayFilter

class CCGrayFilter : public CCShaderFilter
{
public:
	static CCGrayFilter* create();
	static CCGrayFilter* create(ccColor4F $param);

	CCGrayFilter();
	~CCGrayFilter();
	void setParameter(ccColor4F $param);

protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);

private:
	ccColor4F _param;
};

//================== CCBlurFilter

class CCBlurBaseFilter : public CCShaderFilter
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

class CCGaussianHBlurFilter : public CCShaderFilter
{
public:
	static CCGaussianHBlurFilter* create();
	static CCGaussianHBlurFilter* create(float $param);

	CCGaussianHBlurFilter();
	void setParameter(float $param);
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);
	virtual void initSprite(CCFilteredSprite* $sprite);
	float _param;

};

//================== CCMaskFilter

class CCMaskFilter : public CCShaderFilter
{

public:
	static CCMaskFilter* create();
	static CCMaskFilter* create(CCString* $maskImage);

	CCMaskFilter();
	~CCMaskFilter();

	void setParameter(CCString* $param);
	virtual void initSprite(CCFilteredSprite* $sprite);
protected:
	void initProgram();
	CCString* _param;
	
};

//================== CCSharpenFilter

class CCSharpenFilter : public CCShaderFilter
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

class CCRGBFilter : public CCShaderFilter
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

class CCBrightnessFilter : public CCShaderFilter
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
#endif /* __CCSHADER_FILTER_H__ */