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

	CCArray* getAttributes();
	CCArray* getParameters();
	virtual void draw()=0;
	virtual CCGLProgram* getProgram();

	const GLchar* vertex;
	const GLchar* fragment;
	const char* shaderName;
protected:
	CCArray* _pAttributes;
	void addAttribute(GLint $value, const char* $key);
	void addDictionary(GLint $value, const char* $key, CCArray* $arr);
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
	virtual CCGLProgram* getProgram();

};

#endif /* __CCSHADER_FILTER_H__ */