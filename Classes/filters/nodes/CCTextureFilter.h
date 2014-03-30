#ifndef __CCTEXTURE_FILTER_H__
#define __CCTEXTURE_FILTER_H__

#include "cocos2d.h"
#include "CCArmature\external_tool\CCTexture2DMutable.h"

USING_NS_CC;

//================== CCTextureFilter

class CCTextureFilter : public CCObject
{
public:
	CCTextureFilter();
	~CCTextureFilter();

	void blurInput(void* $input, void* $output,
		CCTexture2DPixelFormat $format,	int width, int height,
		CCSize $contentSize, int $radius, CCRect $rect);
	CCTexture2DMutable* blur(CCTexture2DMutable* $texture, int $radius, CCRect $rect);
	CCTexture2DMutable* blur(CCTexture2DMutable* $texture, int $radius);
};

#endif __CCTEXTURE_FILTER_H__