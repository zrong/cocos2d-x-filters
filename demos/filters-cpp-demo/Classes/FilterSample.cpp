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

class FilterSample : public cocos2d::Layer
{
public:
    static cocos2d::Scene* scene();
    
    FilterSample();
    ~FilterSample();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
    
    void restartCallback(Ref* pSender);
    void nextCallback(Ref* pSender);
    void backCallback(Ref* pSender);
    void clearSpriteBack(Ref* pSender);
    
    Sprite* getFilteredSprite(int index);
    
    CREATE_FUNC(FilterSample);
    
    virtual void update(float delta);
    
private:
    CCArray* _pFilters;
    Sprite* _pSprite;
    
    void initFilters();
    void showSprite(int index);
    
    Sprite* testFilter(cocos2d::extension::CCFilter* $filter, ccLocation $location = CENTER, int $order = 0, const char* $path = "helloworld.png");
    Sprite* testFilter(CCArray* $filters, ccLocation $location = CENTER, int $order = 0, const char* $path = "helloworld.png");
    Sprite* testFilterFromFrame(cocos2d::extension::CCFilter* $filter, ccLocation $location = CENTER, int $order = 0, const char* $path = "helloworld1.png");
    Sprite* testFilterFromFrame(CCArray* $filters, ccLocation $location = CENTER, int $order = 0, const char* $path = "helloworld1.png");
    Point getLocation(ccLocation $location);
    
private:
    GLProgram* getEmboss();
    GLProgram* getEmbossMov();
    GLProgram* getColorRamp();
    GLProgram* getGrass();
    
    int _timeUniformLocation;
    float _totalTime = 0.0f;
};

#endif // __FILTER_SAMPLE_H__