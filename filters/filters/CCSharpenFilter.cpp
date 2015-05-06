#include "CCSharpenFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== SharpenFilter

SharpenFilter* SharpenFilter::create()
{
	SharpenFilter* filter = new SharpenFilter();
	filter->autorelease();
	return filter;
}

SharpenFilter* SharpenFilter::create(float sharpness, float widthFactor, float heightFactor)
{
	SharpenFilter* filter = SharpenFilter::create();
	filter->setParameter(sharpness, widthFactor, heightFactor);
	return filter;
}

SharpenFilter* SharpenFilter::create(float sharpness, int amount)
{
	SharpenFilter* filter = SharpenFilter::create();
	filter->setParameter(sharpness, amount);
	return filter;
}

SharpenFilter::SharpenFilter()
: _sharpness(0.f)
, _widthFactor(0.f)
, _heightFactor(0.f)
, _amount(0)
{
	this->shaderName = kCCFilterShader_sharpen;
}

GLProgram* SharpenFilter::loadShader()
{
    GLProgram* p = GLProgram::createWithByteArrays(ccFilterShader_sharpen_vert, ccFilterShader_sharpen_frag);
    
//	GLProgram* p = new GLProgram();
//	p->initWithByteArrays(ccFilterShader_sharpen_vert, ccFilterShader_sharpen_frag);
	return p;
}

void SharpenFilter::setParameter(float sharpness, float widthFactor, float heightFactor)
{
	_sharpness = sharpness;
	_widthFactor = widthFactor;
	_heightFactor = heightFactor;
	//The initProgram() will perform in initSprite()
}

void SharpenFilter::setParameter(float sharpness, int amount)
{
	_sharpness = sharpness;
	_amount = amount;
	//The initProgram() will perform in initSprite()
}

void SharpenFilter::initSprite(FilteredSprite* sprite)
{
	// If _amount is not 0, then calculate the value of the widthFactor and the heightFactor.
	if (_amount != 0)
	{
		Size size = sprite->getContentSize();
		_widthFactor = 1.0f / size.width * _amount;
		_heightFactor = 1.0f / size.height * _amount;
	}
	initProgram();
    
    Filter::initSprite(nullptr);
}

void SharpenFilter::setAttributes(GLProgram* cgp)
{
	//CCLOG("SharpenFilter::setAttributes");
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	cgp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
}

void SharpenFilter::setUniforms(GLProgram* cgp)
{
//	int u_sharpness = cgp->getUniformLocationForName("u_sharpness");
//	int u_widthFactor = cgp->getUniformLocationForName("u_widthFactor");
//	int u_heightFactor = cgp->getUniformLocationForName("u_heightFactor");
//	cgp->setUniformLocationWith1f(u_sharpness, _sharpness);
//	cgp->setUniformLocationWith1f(u_widthFactor, _widthFactor);
//	cgp->setUniformLocationWith1f(u_heightFactor, _heightFactor);
    
    _pProgramState->setUniformFloat("u_sharpness", _sharpness);
    _pProgramState->setUniformFloat("u_widthFactor", _widthFactor);
    _pProgramState->setUniformFloat("u_heightFactor", _heightFactor);
}

NS_CC_EXT_END