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
    static cocos2d::CCScene* scene();
    
    FilterSample();
    ~FilterSample();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void restartCallback(CCObject* pSender);
    void nextCallback(CCObject* pSender);
    void backCallback(CCObject* pSender);
    void clearSpriteBack(CCObject* pSender);
    
    CCSprite* getFilteredSprite(int index);
    
    CREATE_FUNC(FilterSample);
    
    virtual void update(float delta);
    
private:
    CCArray* _pFilters;
    CCSprite* _pSprite;
    
    void initFilters();
    void showSprite(int index);
    
    CCSprite* testFilter(cocos2d::extension::CCFilter* $filter, ccLocation $location = CENTER, int $order = 0, const char* $path = "helloworld.png");
    CCSprite* testFilter(CCArray* $filters, ccLocation $location = CENTER, int $order = 0, const char* $path = "helloworld.png");
    CCSprite* testFilterFromFrame(cocos2d::extension::CCFilter* $filter, ccLocation $location = CENTER, int $order = 0, const char* $path = "helloworld1.png");
    CCSprite* testFilterFromFrame(CCArray* $filters, ccLocation $location = CENTER, int $order = 0, const char* $path = "helloworld1.png");
    CCPoint getLocation(ccLocation $location);
    
private:
    CCGLProgram* getEmboss();
    cocos2d::CCGLProgram* getEmbossMov();
    cocos2d::CCGLProgram* getColorRamp();
    cocos2d::CCGLProgram* getGrass();
    
    int _timeUniformLocation;
    float _totalTime = 0.0f;
};

#endif // __FILTER_SAMPLE_H__