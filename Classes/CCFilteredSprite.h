#ifndef _FILTERED_SPRITE_H_
#define _FILTERED_SPRITE_H_

#include "cocos2d.h"
#include "filters/CCShaderFilter.h"

USING_NS_CC;

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

	static CCFilteredSprite* create(const char* $pszFileName, CCShaderFilter* $pFilter);
	static CCFilteredSprite* create(const char* $pszFileName, CCShaderFilter* $pFilter, 
		const CCRect& $rect);

	static CCFilteredSprite* createWithTexture(CCTexture2D* $pTexture, CCShaderFilter* $pFilter);
	static CCFilteredSprite* createWithTexture(CCTexture2D* $pTexture, CCShaderFilter* $pFilter,
		const CCRect& rect);

	static CCFilteredSprite* createWithSpriteFrame(CCSpriteFrame* $pSpriteFrame,
		CCShaderFilter* $pFilter);
	static CCFilteredSprite* createWithSpriteFrameName(const char* $pszSpriteFrameName,
		CCShaderFilter* $pFilter);
	
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
	void setFilter(CCShaderFilter* $pFilter);
	void setFilters(CCArray* $pFilters);

private:
	bool updateFilters();
	void drawMultiFilters();
	CCArray* _pFilters;
};

#endif