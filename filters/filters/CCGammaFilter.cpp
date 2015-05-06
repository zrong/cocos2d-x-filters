#include "CCGammaFilter.h"

NS_CC_EXT_BEGIN

//================== GammaFilter

GammaFilter* GammaFilter::create()
{
	GammaFilter* filter = new GammaFilter();
	filter->autorelease();
	return filter;
}

GammaFilter* GammaFilter::create(float brightness)
{
	GammaFilter* filter = GammaFilter::create();
	filter->setParameter(brightness);
	return filter;
}

GammaFilter::GammaFilter()
{
	this->shaderName = kCCFilterShader_gamma;
	_param = 1.f;
}

GLProgram* GammaFilter::loadShader()
{
    GLProgram* p = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_gamma_frag);
    
//	GLProgram* p = new GLProgram();
//	p->initWithByteArrays(ccPositionTexture_vert, ccFilterShader_gamma_frag);
	return p;
}

void GammaFilter::setParameter(float param)
{
	_param = MIN(3.f, MAX(param, 0.f));
	initProgram();
}

void GammaFilter::setAttributes(GLProgram* cgp)
{
	//CCLOG("GammaFilter::setAttributes");
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
}

void GammaFilter::setUniforms(GLProgram* cgp)
{
//	int param = cgp->getUniformLocationForName("u_gamma");
//	cgp->setUniformLocationWith1f(param, _param);
    
    _pProgramState->setUniformFloat("u_gamma", _param);
}

NS_CC_EXT_END
