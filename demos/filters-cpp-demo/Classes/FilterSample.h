#ifndef __FILTER_SAMPLE_H__
#define __FILTER_SAMPLE_H__

#include "cocos2d.h"
#include "extensions/ExtensionMacros.h"
#include "VisibleRect.h"
#include "filters/cocos2dFilters.h"

USING_NS_CC_EXT;

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
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool,
    // instead of returning 'id' in cocos2d-iphone
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
    Filters _filters;
    std::vector<Filters> _multiFilters;
    int _filtersNum = 0;
    Sprite* _pSprite;
    
    void initFilters();
    void showSprite(int index);
    
    Sprite* testFilter(Filter* filter, ccLocation location = CENTER,
                       int order = 0, const char* path = "res/helloworld.png");
    Sprite* testFilter(Filters filters, ccLocation location = CENTER,
                       int order = 0, const char* path = "res/helloworld.png");
    Sprite* testFilterFromFrame(Filter* filter, ccLocation location = CENTER,
                                int order = 0, const char* path = "res/helloworld1.png");
    Sprite* testFilterFromFrame(Filters filters, ccLocation location = CENTER,
                                int order = 0, const char* path = "res/helloworld1.png");
    Point getLocation(ccLocation location);
    
private:
    GLProgram* getEmboss();
    cocos2d::GLProgram* getEmbossMov();
    cocos2d::GLProgram* getColorRamp();
    cocos2d::GLProgram* getGrass();
    
    int _timeUniformLocation;
    float _totalTime = 0.0f;
};

#endif // __FILTER_SAMPLE_H__