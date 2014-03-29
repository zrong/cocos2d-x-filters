#ifndef __CCFILTERED_SPRITE_H__
#define __CCFILTERED_SPRITE_H__

#include "cocos2d.h"
#include "filters/CCFilter.h"

USING_NS_CC;

NS_CC_EXT_BEGIN

class CCFilteredSprite : public CCSprite
{
public:
	CCFilteredSprite();
	~CCFilteredSprite();

	static CCFilteredSprite* create();
	static CCFilteredSprite* create(const char* $pszFileName);
	static CCFilteredSprite* create(const char* $pszFileName, const CCRect& $rect);

	static CCFilteredSprite* createWithTexture(CCTexture2D* $pTexture);
	static CCFilteredSprite* createWithTexture(CCTexture2D* $pTexture, const CCRect& rect);

	static CCFilteredSprite* createWithSpriteFrame(CCSpriteFrame* $pSpriteFrame);
	static CCFilteredSprite* createWithSpriteFrameName(const char* $pszSpriteFrameName);

	static CCFilteredSprite* create(const char* $pszFileName, CCFilter* $pFilter);
	static CCFilteredSprite* create(const char* $pszFileName, CCFilter* $pFilter, 
		const CCRect& $rect);

	static CCFilteredSprite* createWithTexture(CCTexture2D* $pTexture, CCFilter* $pFilter);
	static CCFilteredSprite* createWithTexture(CCTexture2D* $pTexture, CCFilter* $pFilter,
		const CCRect& rect);

	static CCFilteredSprite* createWithSpriteFrame(CCSpriteFrame* $pSpriteFrame,
		CCFilter* $pFilter);
	static CCFilteredSprite* createWithSpriteFrameName(const char* $pszSpriteFrameName,
		CCFilter* $pFilter);
	
	static CCFilteredSprite* create(const char* $pszFileName, CCArray* $pFilters);
	static CCFilteredSprite* create(const char* $pszFileName, CCArray* $pFilters,
		const CCRect& $rect);
	
	static CCFilteredSprite* createWithTexture(CCTexture2D* $pTexture, CCArray* $pFilters);
	static CCFilteredSprite* createWithTexture(CCTexture2D* $pTexture, CCArray* $pFilters,
		const CCRect& rect);

	static CCFilteredSprite* createWithSpriteFrame(CCSpriteFrame* $pSpriteFrame,
		CCArray* $pFilters);
	static CCFilteredSprite* createWithSpriteFrameName(const char* $pszSpriteFrameName,
		CCArray* $pFilters);
public:
	virtual void draw(void);
	void setFilter(CCFilter* $pFilter);
	void setFilters(CCArray* $pFilters);

private:
	bool updateFilters();
	void drawMultiFilters();
	CCArray* _pFilters;
};

NS_CC_EXT_END

#endif /* __CCFILTERED_SPRITE_H__ */