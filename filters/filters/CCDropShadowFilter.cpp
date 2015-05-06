#include "CCDropShadowFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== DropShadowFilter

DropShadowFilter* DropShadowFilter::create()
{
	DropShadowFilter* filter = new DropShadowFilter();
	filter->autorelease();
	return filter;
}

DropShadowFilter* DropShadowFilter::create(float resolation)
{
	DropShadowFilter* filter = DropShadowFilter::create();
	filter->setParameter(resolation);
	return filter;
}

DropShadowFilter::DropShadowFilter()
{
	this->shaderName = kCCFilterShader_drop_shadow;
}

GLProgram* DropShadowFilter::loadShader()
{
    GLProgram* p = GLProgram::createWithByteArrays(ccFilterShader_drop_shadow_vert, ccFilterShader_drop_shadow_frag);
    
//	GLProgram* p = new GLProgram();
//	p->initWithByteArrays(ccFilterShader_drop_shadow_vert, 
//		ccFilterShader_drop_shadow_frag);
	return p;
}

void DropShadowFilter::setParameter(float resolation)
{
	//The initProgram() will perform in initSprite()
}

void DropShadowFilter::initSprite(FilteredSprite* sprite)
{
	float aspectRatio = 1.0f;
	Size size = sprite->getContentSize();
	/*_textureWidth = size.width;
	_textureHeight = size.height;*/
	_textureWidth = 480;
	_textureHeight = 320;
	initProgram();
}

void DropShadowFilter::setAttributes(GLProgram* cgp)
{
	//CCLOG("DropShadowFilter::setAttributes");
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
}

void DropShadowFilter::setUniforms(GLProgram* cgp)
{
//	int u_resolution = cgp->getUniformLocationForName("u_resolution");
//	cgp->setUniformLocationWith2f(u_resolution, _textureWidth, _textureHeight);
    
    _pProgramState->setUniformVec2("u_resolution", Vec2(_textureWidth, _textureHeight));
}

NS_CC_EXT_END
