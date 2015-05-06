#include "CCExposureFilter.h"

NS_CC_EXT_BEGIN

//================== ExposureFilter

ExposureFilter* ExposureFilter::create()
{
	ExposureFilter* filter = new ExposureFilter();
	filter->autorelease();
	return filter;
}

ExposureFilter* ExposureFilter::create(float brightness)
{
	ExposureFilter* filter = ExposureFilter::create();
	filter->setParameter(brightness);
	return filter;
}

ExposureFilter::ExposureFilter()
{
	this->shaderName = kCCFilterShader_exposure;
	_param = 0.f;
}

GLProgram* ExposureFilter::loadShader()
{
    GLProgram* p = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_exposure_frag);
    
//	GLProgram* p = new GLProgram();
//	p->initWithByteArrays(ccPositionTexture_vert, ccFilterShader_exposure_frag);
	return p;
}

void ExposureFilter::setParameter(float param)
{
	_param = MIN(10.f, MAX(param, -10.f));
	initProgram();
}

void ExposureFilter::setAttributes(GLProgram* cgp)
{
	//CCLOG("ExposureFilter::setAttributes");
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
}

void ExposureFilter::setUniforms(GLProgram* cgp)
{
//	int param = cgp->getUniformLocationForName("u_exposure");
//	cgp->setUniformLocationWith1f(param, _param);
    
    _pProgramState->setUniformFloat("u_exposure", _param);
}

NS_CC_EXT_END