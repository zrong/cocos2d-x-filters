#include "CCContrastFilter.h"

NS_CC_EXT_BEGIN
//================== ContrastFilter

ContrastFilter* ContrastFilter::create()
{
	ContrastFilter* filter = new ContrastFilter();
	filter->autorelease();
	return filter;
}

ContrastFilter* ContrastFilter::create(float brightness)
{
	ContrastFilter* filter = ContrastFilter::create();
	filter->setParameter(brightness);
	return filter;
}

ContrastFilter::ContrastFilter()
{
	this->shaderName = kCCFilterShader_contrast;
	_param = 1.f;
}

GLProgram* ContrastFilter::loadShader()
{
    GLProgram* p = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_contrast_frag);
    
//	GLProgram* p = new GLProgram();
//	p->initWithByteArrays(ccPositionTexture_vert, ccFilterShader_contrast_frag);
	return p;
}

void ContrastFilter::setParameter(float param)
{
	_param = MIN(4.f, MAX(param, 0.f));
	initProgram();
}

void ContrastFilter::setAttributes(GLProgram* cgp)
{
	//CCLOG("ContrastFilter::setAttributes");
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
}

void ContrastFilter::setUniforms(GLProgram* cgp)
{
//	int u_contrast = cgp->getUniformLocationForName("u_contrast");
//	cgp->setUniformLocationWith1f(u_contrast, _param);
    
    _pProgramState->setUniformFloat("u_contrast", _param);
}

NS_CC_EXT_END