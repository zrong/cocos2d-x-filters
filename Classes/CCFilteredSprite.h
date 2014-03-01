#ifndef _FILTERED_SPRITE_H_
#define _FILTERED_SPRITE_H_

#include "cocos2d.h"
#include "filters/CCShaderFilter.h"

USING_NS_CC;

#define CC_SHADER_SET_FILTER(p, f)   if(p) { (p)->setFilter(f); return (p);}

class CCFilteredSprite : public CCSprite
{
public:
	CCFilteredSprite();
	~CCFilteredSprite();

	static CCFilteredSprite* create();
	static CCFilteredSprite* create(const char *pszFileName);
	static CCFilteredSprite* create(const char *pszFileName, CCShaderFilter* pFilter);
	static CCFilteredSprite* create(const char *pszFileName, const CCRect& rect);
	static CCFilteredSprite* create(const char *pszFileName, CCShaderFilter* pFilter, const CCRect& rect);
	static CCFilteredSprite* createWithTexture(CCTexture2D *pTexture);
	static CCFilteredSprite* createWithTexture(CCTexture2D *pTexture, CCShaderFilter* pFilter);
	static CCFilteredSprite* createWithTexture(CCTexture2D *pTexture, const CCRect& rect);
	static CCFilteredSprite* createWithTexture(CCTexture2D *pTexture, CCShaderFilter* pFilter, const CCRect& rect);
	static CCFilteredSprite* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame);
	static CCFilteredSprite* createWithSpriteFrame(CCSpriteFrame *pSpriteFrame, CCShaderFilter* pFilter);
	static CCFilteredSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
	static CCFilteredSprite* createWithSpriteFrameName(const char *pszSpriteFrameName, CCShaderFilter* pFilter);
public:
	virtual void draw(void);
	void setFilter(CCShaderFilter* pFilter);
	CCShaderFilter* getFilter();
private:
	bool updateFilter();
private:
	CCShaderFilter* _pFilter;
};

#endif