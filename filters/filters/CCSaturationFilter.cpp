#include "CCSaturationFilter.h"

NS_CC_EXT_BEGIN

//================== SaturationFilter

SaturationFilter* SaturationFilter::create()
{
	SaturationFilter* filter = new SaturationFilter();
	filter->autorelease();
	return filter;
}

SaturationFilter* SaturationFilter::create(float brightness)
{
	SaturationFilter* filter = SaturationFilter::create();
	filter->setParameter(brightness);
	return filter;
}

SaturationFilter::SaturationFilter()
{
	this->shaderName = kCCFilterShader_saturation;
	_param = 1.f;
}

GLProgram* SaturationFilter::loadShader()
{
    GLProgram* p = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_saturation_frag);
    
//	GLProgram* p = new GLProgram();
//	p->initWithByteArrays(ccPositionTexture_vert, ccFilterShader_saturation_frag);
	return p;
}

void SaturationFilter::setParameter(float param)
{
	_param = MIN(2.f, MAX(param, 0.f));
	initProgram();
}

void SaturationFilter::setAttributes(GLProgram* cgp)
{
	//CCLOG("SaturationFilter::setAttributes");
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
}

void SaturationFilter::setUniforms(GLProgram* cgp)
{
//	int param = cgp->getUniformLocationForName("u_saturation");
//	cgp->setUniformLocationWith1f(param, _param);
    
    _pProgramState->setUniformFloat("u_saturation", _param);
}


NS_CC_EXT_END
