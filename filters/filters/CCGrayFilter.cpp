#include "CCGrayFilter.h"

NS_CC_EXT_BEGIN

//================== GrayFilter

GrayFilter* GrayFilter::create()
{
	GrayFilter* filter = new GrayFilter();
	filter->autorelease();
	filter->initProgram();
	return filter;
}

GrayFilter* GrayFilter::create(Color4F param)
{
	GrayFilter* filter = GrayFilter::create();
	filter->setParameter(param);
	return filter;
}

GrayFilter* GrayFilter::create(float r, float g, float b, float a)
{
	GrayFilter* filter = GrayFilter::create();
	filter->setParameter(r, a, b, a);
	return filter;
}


GrayFilter::GrayFilter()
: _param(Color4F(0.299f, 0.587f, 0.114f, 0.0f))
{
	this->shaderName = kCCFilterShader_gray;
}

void GrayFilter::setParameter(Color4F param)
{
	_param = param;
	initProgram();
}

void GrayFilter::setParameter(float r, float g, float b, float a)
{
	setParameter(Color4F(r, g, b, a));
}

GLProgram* GrayFilter::loadShader()
{
    GLProgram* p = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_gray_frag);
//	GLProgram* p = new GLProgram();
//	p->initWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_gray_frag);
	return p;
}

void GrayFilter::setAttributes(GLProgram* cgp)
{
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
}

void GrayFilter::setUniforms(GLProgram* cgp)
{
	//int grayParam = cgp->getUniformLocationForName("u_grayParam");
	//CCLOG("GrayFilter::setUniforms, u_grayParam:%d", grayParam);
	//cgp->setUniformLocationWith4f(grayParam, _param.r, _param.g, _param.b, _param.a);
    _pProgramState->setUniformVec4("u_grayParam", Vec4(_param.r, _param.g, _param.b, _param.a));
}

NS_CC_EXT_END