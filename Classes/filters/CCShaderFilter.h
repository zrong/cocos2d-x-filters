#ifndef __CCSHADER_FILTER_H__
#define __CCSHADER_FILTER_H__

#include "cocos2d.h"
#include "CCGL.h"
#include "ccFilterShaders.h"


#define kCCFilterShader_gray	"ccFilterShader_gray"
#define kCCFilterShader_blur	"ccFilterShader_blur"

//define attribute names
#define kCCAttributeName_grayParam        "a_grayParam"
#define kCCVertexAttrib_grayParam   4

USING_NS_CC;

class CCShaderFilter :	public CCObject
{
public:
	CCShaderFilter();
	~CCShaderFilter();

	virtual void draw()=0;
	CCGLProgram* getProgram();

	const char* shaderName;
protected:
	CCArray* _pAttributes;
	CCGLProgram* _pProgram;
	void initProgram();
	virtual CCGLProgram* loadShader() = 0;
	virtual void setAttributes(CCGLProgram* $glp) = 0;
	virtual void setUniforms(CCGLProgram* $glp) = 0;
};

class CCGrayFilter : public CCShaderFilter
{
public:
	static CCGrayFilter* create();
	static CCGrayFilter* create(ccColor4F $param);

	CCGrayFilter();
	~CCGrayFilter();
	virtual void draw();
	void setParameter(ccColor4F $param);

protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);

private:
	ccColor4F _pParam;
};

class CCBlurFilter : public CCShaderFilter
{
public:
	static CCBlurFilter* create();

	CCBlurFilter();
	~CCBlurFilter();
	virtual void draw();
protected:
	virtual CCGLProgram* loadShader();
	virtual void setAttributes(CCGLProgram* $glp);
	virtual void setUniforms(CCGLProgram* $glp);

};

#endif /* __CCSHADER_FILTER_H__ */