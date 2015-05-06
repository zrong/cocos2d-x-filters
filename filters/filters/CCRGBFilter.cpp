#include "CCRGBFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== RGBFilter

RGBFilter* RGBFilter::create()
{
	RGBFilter* filter = new RGBFilter();
	filter->autorelease();
	return filter;
}

RGBFilter* RGBFilter::create(float readAdj, float greenAdj, float blueAdj)
{
	RGBFilter* filter = RGBFilter::create();
	filter->setParameter(readAdj, greenAdj, blueAdj);
	return filter;
}

RGBFilter::RGBFilter()
: _redAdj(1.f)
, _greenAdj(1.f)
, _blueAdj(1.f)
{
	this->shaderName = kCCFilterShader_rgb;
}

GLProgram* RGBFilter::loadShader()
{
    GLProgram* p = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_rgb_frag);
    
//	GLProgram* p = new GLProgram();
//	p->initWithByteArrays(ccPositionTexture_vert, ccFilterShader_rgb_frag);
	return p;
}

void RGBFilter::setParameter(float redAdj, float greenAdj, float blueAdj)
{
	_redAdj = redAdj;
	_greenAdj = greenAdj;
	_blueAdj = blueAdj;
	initProgram();
}

void RGBFilter::setAttributes(GLProgram* cgp)
{
	//CCLOG("RGBFilter::setAttributes");
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
}

void RGBFilter::setUniforms(GLProgram* cgp)
{
//	int redAdj = cgp->getUniformLocationForName("u_redAdj");
//	int greenAdj = cgp->getUniformLocationForName("u_greenAdj");
//	int blueAdj = cgp->getUniformLocationForName("u_blueAdj");
//	cgp->setUniformLocationWith1f(redAdj, _redAdj);
//	cgp->setUniformLocationWith1f(greenAdj, _greenAdj);
//	cgp->setUniformLocationWith1f(blueAdj, _blueAdj);
    
    _pProgramState->setUniformFloat("u_redAdj", _redAdj);
    _pProgramState->setUniformFloat("u_greenAdj", _greenAdj);
    _pProgramState->setUniformFloat("u_blueAdj", _blueAdj);
}

NS_CC_EXT_END