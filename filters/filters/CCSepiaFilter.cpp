#include "CCSepiaFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN
//================== SepiaFilter

SepiaFilter* SepiaFilter::create()
{
	SepiaFilter* filter = new SepiaFilter();
	filter->autorelease();
	return filter;
}

SepiaFilter* SepiaFilter::create(float resolation)
{
	SepiaFilter* filter = SepiaFilter::create();
	filter->setParameter();
	return filter;
}

SepiaFilter::SepiaFilter()
{
	this->shaderName = kCCFilterShader_sepia;
}

GLProgram* SepiaFilter::loadShader()
{
    GLProgram* p = GLProgram::createWithByteArrays(ccPositionTextureColor_vert, ccFilterShader_sepia_frag);
    
//	GLProgram* p = new GLProgram();
//	p->initWithByteArrays(ccPositionTextureColor_vert,
//		ccFilterShader_sepia_frag);
	return p;
}

void SepiaFilter::setParameter()
{
	initProgram();
}

void SepiaFilter::setAttributes(GLProgram* cgp)
{
	//CCLOG("SepiaFilter::setAttributes");
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
}

void SepiaFilter::setUniforms(GLProgram* cgp)
{

}

NS_CC_EXT_END
