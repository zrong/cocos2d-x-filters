#include "CCMaskFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== MaskFilter

MaskFilter* MaskFilter::create()
{
	MaskFilter* filter = new MaskFilter();
	filter->autorelease();
	return filter;
}

MaskFilter* MaskFilter::create(std::string* maskImage)
{
	MaskFilter* filter = MaskFilter::create();
	filter->setParameter(maskImage);
	filter->setIsSpriteFrame(false);
	return filter;
}

MaskFilter* MaskFilter::createWithSpriteFrameName(std::string* maskImage)
{
	MaskFilter* filter = MaskFilter::create();
	filter->setParameter(maskImage);
	filter->setIsSpriteFrame(true);
	return filter;
}

MaskFilter::MaskFilter()
: _param(NULL)
, _isSpriteFrame(false)
{
	this->shaderName = NULL;
}

void MaskFilter::initProgram()
{
	//Do nothing in MaskFilter
	//CCLOG("MaskFilter initProgram");
}

void MaskFilter::initSprite(FilteredSprite* sprite)
{
	//CCLOG("MaskFilter initSprite maskImage:%s", _param->c_str());
	BlendFunc maskBF = { GL_ONE, GL_ZERO };
	BlendFunc imgBF = { GL_DST_ALPHA, GL_ZERO };

	Sprite* pMask = _isSpriteFrame ?
		Sprite::create(_param->c_str()):
		Sprite::createWithSpriteFrameName(_param->c_str());
	pMask->setAnchorPoint(Vec2(0, 0));
	pMask->setPosition(Vec2(0, 0));

	Sprite* pImg = Sprite::createWithSpriteFrameName("helloworld.png");
	pImg->setAnchorPoint(Vec2(0, 0));
	pImg->setPosition(Vec2(0, 0));

	pMask->setBlendFunc(maskBF);
	pImg->setBlendFunc(imgBF);

	Size size = pImg->getContentSize();
	RenderTexture* pRender = RenderTexture::create(size.width, size.height);
	pRender->begin();
	pMask->visit();
	pImg->visit();
	pRender->end();

	Texture2D* pTex = new Texture2D();
	pTex->initWithImage(pRender->newImage(true));
	pTex->autorelease();
	sprite->setTexture(pTex);
}

void MaskFilter::setParameter(std::string* maskImage)
{
	_param = maskImage;
}

NS_CC_EXT_END