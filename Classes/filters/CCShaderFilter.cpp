#include "CCShaderFilter.h"

CCShaderFilter::CCShaderFilter()
: vertex(NULL)
, fragment(NULL)
, shaderName(NULL)
, _pAttributes(NULL)
{

}


CCShaderFilter::~CCShaderFilter()
{
}

CCArray* CCShaderFilter::getAttributes()
{
	return _pAttributes;
}

void CCShaderFilter::addAttribute(GLint $value, const char* $key)
{
	if (!_pAttributes)
	{
		_pAttributes = CCArray::createWithCapacity(4);
	}
	addDictionary($value, $key, _pAttributes);
}

void CCShaderFilter::addDictionary(GLint $value, const char* $key, CCArray* $arr)
{
	CCDictionary* __dict = CCDictionary::create();
	__dict->setObject(CCString::create($key), "name");
	__dict->setObject(CCInteger::create($value), "index");
	$arr->addObject(__dict);
}

CCGLProgram* CCShaderFilter::getProgram()
{
	CCGLProgram* __pProgram = CCShaderCache::sharedShaderCache()->programForKey(shaderName);
	CCLOG("CCShaderFilter::getProgram %s", shaderName);
	if (!__pProgram)
	{
		__pProgram = loadShader();
		this->setAttributes(__pProgram);
		__pProgram->link();
		__pProgram->updateUniforms();
		CCLOG("CCShaderFilter::getProgram tt:%d", glGetUniformLocation(__pProgram->getProgram(), kCCUniformPMatrix_s));
		this->setUniforms(__pProgram);
		CCShaderCache::sharedShaderCache()->addProgram(__pProgram, this->shaderName);
		__pProgram->release();
		CCLOG("CCShaderFilter::getProgram1 %d", __pProgram);
	}
	CCLOG("CCShaderFilter::getProgram2 %d", __pProgram);
	return __pProgram;
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
: _pParam(ccc4f(0.299f, 0.587f, 0.114f, 0.0f))
{
	this->shaderName = kCCFilterShader_gray;
}

void CCGrayFilter::draw()
{
	//gray filter
	//GLfloat __param[] = { _pParam.r, _pParam.g, _pParam.b, _pParam.a};
	//glVertexAttrib4fv(kCCVertexAttrib_grayParam, __param);

	CCGLProgram* __program = CCShaderCache::sharedShaderCache()->programForKey(shaderName);
	int __grayParam = __program->getUniformLocationForName("u_grayParam");
	//CCLOG("CCGrayFilter::draw, grayParam %d", __grayParam);
	__program->setUniformLocationWith4f(__grayParam, _pParam.r, _pParam.g, _pParam.b, _pParam.a);
}


void CCGrayFilter::setParameter(ccColor4F $param)
{
	_pParam = $param;
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
	$cgp->addAttribute(kCCAttributeName_grayParam, kCCVertexAttrib_grayParam);
}

void CCGrayFilter::setUniforms(CCGLProgram* $cgp)
{
	int __grayParam = $cgp->getUniformLocationForName("u_grayParam");
	CCLOG("CCGrayFilter::setUniforms, grayParam %d", __grayParam);
	$cgp->setUniformLocationWith4f(__grayParam, _pParam.r, _pParam.g, _pParam.b, _pParam.a);
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

CCBlurFilter::CCBlurFilter()
{
	this->vertex = ccFilterShader_blur_vert;
	this->fragment = ccFilterShader_blur_frag;
	this->shaderName = kCCFilterShader_blur;

	this->addAttribute(kCCVertexAttrib_Position, kCCAttributeNamePosition);
	this->addAttribute(kCCVertexAttrib_Color, kCCAttributeNameColor);
	this->addAttribute(kCCVertexAttrib_TexCoords, kCCAttributeNameTexCoord);
}

CCGLProgram* CCBlurFilter::getProgram()
{
	CCGLProgram* __program = CCShaderFilter::getProgram();
	//int __radius = __program->getUniformLocationForName("u_radius");
	//CCLOG("CCShaderFilter::getProgram %d", __program);
	//glUniform1f(__radius, 0.4f);
	//CCLOG("GOGOG %d", __radius);
	return __program;
}

void CCBlurFilter::draw()
{
	CCGLProgram* __program = CCShaderCache::sharedShaderCache()->programForKey(shaderName);
	int __radius = __program->getUniformLocationForName("u_radius");
	CCLOG("CCShaderFilter::getProgram %d", __program);
	__program->setUniformLocationWith1f(__radius, 0.02f);
	//glUniform1f(__radius, 0.02f);
	CCLOG("GOGOG %d", __radius);
}

CCGLProgram* CCBlurFilter::loadShader()
{
	return NULL;
}

void CCBlurFilter::setAttributes(CCGLProgram* $cgp)
{
}

void CCBlurFilter::setUniforms(CCGLProgram* $cgp)
{
}

CCBlurFilter::~CCBlurFilter()
{
}