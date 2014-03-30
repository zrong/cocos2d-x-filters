#ifndef __FILTER_SAMPLE_H__
#define __FILTER_SAMPLE_H__

#include "cocos2d.h"
#include "filters/cocos2dFilters.h"
#include "VisibleRect.h"

typedef enum {
	LEFT_TOP,
	RIGHT_TOP,
	LEFT_BOTTOM,
	RIGHT_BOTTOM,
	CENTER,
} ccLocation;

class FilterSample : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(FilterSample);

	virtual void update(float delta);
private:
	void showSprite();
	CCGLProgram* getEmboss();
	cocos2d::CCGLProgram* getEmbossMov();
	cocos2d::CCGLProgram* getColorRamp();
	cocos2d::CCGLProgram* getGrass();
	int _timeUniformLocation;
	float _totalTime = 0.0f;
	cocos2d::CCSprite* _pSprite;
	CCSprite* testFilter(cocos2d::extension::CCFilter* $filter, ccLocation $location = CENTER, int $order = 0, 
		const char* $path="HelloWorld.png");
	CCSprite* testFilter(CCArray* $filters, ccLocation $location = CENTER, int $order = 0, 
		const char* $path = "HelloWorld.png");
	CCSprite* testFilterFromFrame(cocos2d::extension::CCFilter* $filter, 
		ccLocation $location = CENTER, int $order = 0, const char* $path = "helloworld.png");
	CCSprite* testFilterFromFrame(CCArray* $filters, 
		ccLocation $location = CENTER, int $order = 0, const char* $path = "helloworld.png");
	CCPoint getLocation(ccLocation $location);
};

#endif // __FILTER_SAMPLE_H__
