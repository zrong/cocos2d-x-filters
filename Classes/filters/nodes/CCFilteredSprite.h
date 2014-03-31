#ifndef __CCFILTERED_SPRITE_H__
#define __CCFILTERED_SPRITE_H__

#include "cocos2d.h"
#include "filters/filters/CCFilter.h"

USING_NS_CC;

NS_CC_EXT_BEGIN

class CCFilteredSprite : public CCSprite
{
public:

	CCFilteredSprite();
	~CCFilteredSprite();

	virtual CCFilter* getFilter(unsigned int $index = 0);
	virtual void setFilter(CCFilter* $pFilter)=0;

	virtual CCArray* getFilters();
	virtual void setFilters(CCArray* $pFilters);

	virtual void draw(void);

protected:
	virtual void drawFilter()=0;
	virtual bool updateFilters()=0;
	CCArray* _pFilters;
};

class CCFilteredSpriteWithOne : public CCFilteredSprite
{
public:
	static CCFilteredSpriteWithOne* create();
	static CCFilteredSpriteWithOne* create(const char* $pszFileName);
	static CCFilteredSpriteWithOne* create(const char* $pszFileName, const CCRect& $rect);

	static CCFilteredSpriteWithOne* createWithTexture(CCTexture2D* $pTexture);
	static CCFilteredSpriteWithOne* createWithTexture(CCTexture2D* $pTexture, const CCRect& rect);

	static CCFilteredSpriteWithOne* createWithSpriteFrame(CCSpriteFrame* $pSpriteFrame);

	static CCFilteredSpriteWithOne* createWithSpriteFrameName(const char* $pszSpriteFrameName);

	virtual CCFilter* getFilter(unsigned int $index = 0);
	virtual void setFilters(CCArray* $pFilters);
	virtual void setFilter(CCFilter* $pFilter);

protected:
	virtual void drawFilter();
	virtual bool updateFilters();
};

class CCFilteredSpriteWithMulti : public CCFilteredSprite
{
public:
	static CCFilteredSpriteWithMulti* create();
	static CCFilteredSpriteWithMulti* create(const char* $pszFileName);

	static CCFilteredSpriteWithMulti* createWithTexture(CCTexture2D* $pTexture);

	static CCFilteredSpriteWithMulti* createWithSpriteFrame(CCSpriteFrame* $pSpriteFrame);

	static CCFilteredSpriteWithMulti* createWithSpriteFrameName(const char* $pszSpriteFrameName);

	virtual void setFilter(CCFilter* $pFilter);


	CCFilteredSpriteWithMulti();
	~CCFilteredSpriteWithMulti();

	// ts = Temporary Storage
	CCSpriteFrame* getTSSpriteFrame();
	void setTSSpriteFrame(CCSpriteFrame* $spriteFrame);
	CCTexture2D* getTSTexture();
	void setTSTexture(CCTexture2D* $texture);

protected:
	virtual void drawFilter();
	virtual bool updateFilters();
private:
	CCSpriteFrame* _pFrame;
	CCTexture2D* _pTexture;
};

NS_CC_EXT_END

#endif /* __CCFILTERED_SPRITE_H__ */