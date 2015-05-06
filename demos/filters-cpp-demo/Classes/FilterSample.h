/**********************************************
 * Author: zrong(zengrong.net)
 * Creation: 2014-03-24
 * Last Modification: 2015-05-06
 **********************************************/

#ifndef FILTER_SAMPLE_H
#define FILTER_SAMPLE_H

#include "cocos2d.h"
#include "extensions/ExtensionMacros.h"
#include "VisibleRect.h"
#include "filters/cocos2dFilters.h"
#include "filters/nodes/DBCCFilterArmature.h"
#include "filters/nodes/DBCCFilterFactory.h"
#include "renderer/DBCCArmatureNode.h"
#include "renderer/DBCCFactory.h"

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
    
    void onSpriteFilter(Ref* pSender);
    void onArmatureFilter(Ref* pSender);
    void onRestart(Ref* pSender);
    void onNext(Ref* pSender);
    void onBack(Ref* pSender);
    void onClearFilter(Ref* pSender);
    
    CREATE_FUNC(FilterSample);
    
    virtual void update(float delta);
    
private:
    Label* _nameLabel;
    Filters _filters;
    std::vector<std::string> _filterNames;
    std::vector<Filters> _multiFilters;
    std::vector<std::string> _multiFilterNames;
    int _filtersNum = 0;
    bool _showArmature = false;
    Node* _pNode;
    DBCCFilterArmature* _pArmature;
    
    void initFilters();
    void showFilteredDisplay(int index);
    
    Sprite* getFilteredSprite(int index);
    Node* getFilteredArmatureDisplay(int index);
    
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

#endif // FILTER_SAMPLE_H