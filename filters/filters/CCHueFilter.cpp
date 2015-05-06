#include "CCHueFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== HueFilter

HueFilter* HueFilter::create()
{
	HueFilter* filter = new HueFilter();
	filter->autorelease();
	return filter;
}

HueFilter* HueFilter::create(float brightness)
{
	HueFilter* filter = HueFilter::create();
	filter->setParameter(brightness);
	return filter;
}

HueFilter::HueFilter()
{
	this->shaderName = kCCFilterShader_hue;
	_param = 0.f;
}

GLProgram* HueFilter::loadShader()
{
    GLProgram* p = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_hue_frag);
    
//	GLProgram* p = new GLProgram();
//	p->initWithByteArrays(ccPositionTexture_vert, ccFilterShader_hue_frag);
	return p;
}

void HueFilter::setParameter(float param)
{
	_param = fmodf(param, 360.f)*M_PI / 180;
	initProgram();
}

void HueFilter::setAttributes(GLProgram* cgp)
{
	//CCLOG("HueFilter::setAttributes");
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
}

void HueFilter::setUniforms(GLProgram* cgp)
{
//	int u_hueAdjust = cgp->getUniformLocationForName("u_hueAdjust");
//	cgp->setUniformLocationWith1f(u_hueAdjust, _param);
    
    _pProgramState->setUniformFloat("u_hueAdjust", _param);
}

NS_CC_EXT_END
