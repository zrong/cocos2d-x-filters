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
    void onClose(Ref* pSender);
    
    void onRestart(Ref* pSender);
    void onNext(Ref* pSender);
    void onBack(Ref* pSender);
    void onClearFilter(Ref* pSender);
    
    Sprite* getFilteredSprite(int index);
    
    CREATE_FUNC(FilterSample);
    
    virtual void update(float delta);
    
private:
    Filters _filters;
    std::vector<Filters> _multiFilters;
    int _filtersNum = 0;
    Node* _pNode;
    
    void initFilters();
    void showFilteredDisplay(int index);
    
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