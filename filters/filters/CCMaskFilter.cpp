/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2014      Jacky Tsang (zengrong.net)

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

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