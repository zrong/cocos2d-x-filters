#include "CCHazeFilter.h"

NS_CC_EXT_BEGIN

//================== HazeFilter

HazeFilter* HazeFilter::create()
{
	HazeFilter* filter = new HazeFilter();
	filter->autorelease();
	return filter;
}

HazeFilter* HazeFilter::create(float hazeDistance, float slope)
{
	HazeFilter* filter = HazeFilter::create();
	filter->setParameter(hazeDistance, slope);
	return filter;
}

HazeFilter::HazeFilter()
: _hazeDistance(0.f)
, _slope(0.f)
{
	this->shaderName = kCCFilterShader_haze;
}

GLProgram* HazeFilter::loadShader()
{
    GLProgram* p = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, ccFilterShader_haze_frag);
    
//	GLProgram* p = new GLProgram();
//	p->initWithByteArrays(ccPositionTexture_vert, ccFilterShader_haze_frag);
	return p;
}

void HazeFilter::setParameter(float hazeDistance, float slope)
{
	_hazeDistance = MIN(0.5f, MAX(hazeDistance, -0.5f));
	_slope = MIN(0.5f, MAX(slope, -0.5f));
	initProgram();
}

void HazeFilter::setAttributes(GLProgram* cgp)
{
	//CCLOG("HazeFilter::setAttributes");
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
}

void HazeFilter::setUniforms(GLProgram* cgp)
{
//	int hazeDistance = cgp->getUniformLocationForName("u_hazeDistance");
//	int slope = cgp->getUniformLocationForName("u_slope");
//	cgp->setUniformLocationWith1f(hazeDistance, _hazeDistance);
//	cgp->setUniformLocationWith1f(slope, _slope);
    
    _pProgramState->setUniformFloat("u_hazeDistance", _hazeDistance);
    _pProgramState->setUniformFloat("u_slope", _slope);
}
NS_CC_EXT_END
