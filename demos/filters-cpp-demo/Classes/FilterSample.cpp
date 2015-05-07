/**********************************************
 * Author: zrong(zengrong.net)
 * Creation: 2014-03-24
 * Last Modification: 2015-05-06
 **********************************************/

#include "FilterSample.h"

static int filterIndex = 0;

FilterSample::FilterSample()
: _pNode(nullptr)
, _pArmature(nullptr)
, _nameLabel(nullptr)
{
}

FilterSample::~FilterSample()
{
    _filters.clear();
}

Scene* FilterSample::scene()
{
    Scene *scene = Scene::create();
    FilterSample *layer = FilterSample::create();
    scene->addChild(layer);
    return scene;
}

bool FilterSample::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    MenuItemImage *item1 = MenuItemImage::create("res/b1.png",
                                                 "res/b2.png",
                                                 CC_CALLBACK_1(FilterSample::onBack, this));
    MenuItemImage *item2 = MenuItemImage::create("res/r1.png",
                                                 "res/r2.png",
                                                 CC_CALLBACK_1(FilterSample::onRestart, this));
    MenuItemImage *item3 = MenuItemImage::create("res/f1.png",
                                                 "res/f2.png",
                                                 CC_CALLBACK_1(FilterSample::onNext, this));
    MenuItemImage *pCloseItem = MenuItemImage::create("res/CloseNormal.png",
                                                      "res/CloseSelected.png",
                                                      CC_CALLBACK_1(FilterSample::onClose, this));
    MenuItemFont *pClearItem = MenuItemFont::create("Clear Filter",
                                                    CC_CALLBACK_1(FilterSample::onClearFilter, this));
    MenuItemFont *pArmatureItem = MenuItemFont::create("For Armature",
                                                       CC_CALLBACK_1(FilterSample::onArmatureFilter, this));
    MenuItemFont *pSpriteItem = MenuItemFont::create("For Sprite",
                                                    CC_CALLBACK_1(FilterSample::onSpriteFilter, this));
    
    pCloseItem->setPosition(VisibleRect::rightBottom(-20,20));
    
    Menu* pMenu = Menu::create(item1, item2, item3, pClearItem, pArmatureItem, pSpriteItem, pCloseItem, NULL);
    pMenu->setPosition(cocos2d::Point(0,0));
    Size item2Size = item2->getContentSize();
    item1->setPosition(VisibleRect::bottom(-item2Size.width * 2, item2Size.height / 2));
    item2->setPosition(VisibleRect::bottom(0, item2Size.height / 2));
    item3->setPosition(VisibleRect::bottom(item2Size.width * 2, item2Size.height / 2));
    pClearItem->setPosition(VisibleRect::bottom(0, 100));
    pArmatureItem->setPosition(VisibleRect::top(-100, -120));
    pSpriteItem->setPosition(VisibleRect::top(100, -120));
    pCloseItem->setPosition(VisibleRect::rightBottom(-item2Size.width / 2, item2Size.height / 2));
    
    this->addChild(pMenu, 1);
    
    _nameLabel = Label::createWithSystemFont("Filter Name", "Arial", 28);
    _nameLabel->setPosition(VisibleRect::top(0, -50));
    this->addChild(_nameLabel, 10);
    
    this->initFilters();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/test2.plist", "res/test2.png");
    Sprite* bg = Sprite::create("res/bg.jpg");
    bg->setPosition(VisibleRect::center());
    this->addChild(bg, -10);
    
    DBCCFilterFactory* factory = DBCCFilterFactory::getInstance();
    factory->loadDragonBonesData("res/dragon/skeleton.xml", "Dragon");
    factory->loadTextureAtlas("res/dragon/texture.xml", "Dragon");
    
    this->showFilteredDisplay(filterIndex);
    
    return true;
}

void FilterSample::initFilters()
{
    //colors
    _filters.pushBack(GrayFilter::create(0.2f, 0.3f, 0.5f, 0.1f));
    _filters.pushBack(RGBFilter::create(1, 0.5, 0.3));
    _filters.pushBack(HueFilter::create(90));
    _filters.pushBack(BrightnessFilter::create(0.3));
    _filters.pushBack(SaturationFilter::create(0));
    _filters.pushBack(ExposureFilter::create(2));
    _filters.pushBack(GammaFilter::create(2));
    
    
    _filterNames.push_back("GrayFilter(0.2, 0.3, 0.5, 0.1)");
    _filterNames.push_back("RGBFilter(1, 0.5, 0.3)");
    _filterNames.push_back("HueFilter(90)");
    _filterNames.push_back("BrightnessFilter(0.3)");
    _filterNames.push_back("SaturationFilter(0)");
    _filterNames.push_back("ExposureFilter(2)");
    _filterNames.push_back("GammaFilter(2)");
    
    //blurs
    _filters.pushBack(GaussianVBlurFilter::create(7));
    _filters.pushBack(GaussianHBlurFilter::create(7));
    _filters.pushBack(ZoomBlurFilter::create(4, 0.7, 0.7));
    _filters.pushBack(MotionBlurFilter::create(5, 135));
    
    _filterNames.push_back("GaussianVBlurFilter(7)");
    _filterNames.push_back("GaussianHBlurFilter(7)");
    _filterNames.push_back("ZoomBlurFilter(4, 0.7, 0.7)");
    _filterNames.push_back("MotionBlurFilter(5, 135)");
    
    //others
    _filters.pushBack(SharpenFilter::create(1,1));
    _filterNames.push_back("SharpenFilter(1,1)");
    
    //multi
    Filters one;
    one.pushBack(GrayFilter::create());
    one.pushBack(GaussianVBlurFilter::create(10));
    one.pushBack(GaussianHBlurFilter::create(10));
    _multiFilters.push_back(one);
    _multiFilterNames.push_back("GrayFilter()\nGaussianVBlurFilter(10)\nGaussianHBlurFilter(10)");
    
    Filters two;
    two.pushBack(BrightnessFilter::create(0.1));
    two.pushBack(ContrastFilter::create(4));
    _multiFilters.push_back(two);
    _multiFilterNames.push_back("BrightnessFilter(0.1)\nContrastFilter(4)");
    
    Filters three;
    three.pushBack(HueFilter::create(240));
    three.pushBack(SaturationFilter::create(1.5));
    three.pushBack(BrightnessFilter::create(-0.4));
    _multiFilters.push_back(three);
    _multiFilterNames.push_back("HueFilter(240)\nSaturationFilter(1.5)\nBrightnessFilter(-0.4)");
    
    _filtersNum = _filters.size()+_multiFilters.size();
}

void FilterSample::onRestart(Ref* pSender)
{
    showFilteredDisplay(filterIndex);
}

void FilterSample::onNext(Ref* pSender)
{
    filterIndex++;
    filterIndex = filterIndex%_filtersNum;
    showFilteredDisplay(filterIndex);
}

void FilterSample::onBack(Ref* pSender)
{
    filterIndex--;
    if (filterIndex < 0)
        filterIndex += _filtersNum;
    showFilteredDisplay(filterIndex);
}

void FilterSample::onClearFilter(Ref* pSender)
{
    if(_showArmature)
    {
        _pArmature->clearFilter();
    }
    else
    {
        FilteredSprite* sprite = dynamic_cast<FilteredSprite*>(_pNode);
        if (sprite) sprite->clearFilter();
    }
}

void FilterSample::onArmatureFilter(Ref* pSender)
{
    _showArmature = true;
    _filtersNum = _filters.size();
    if(filterIndex >= _filtersNum)
    {
        filterIndex = 0;
    }
    this->showFilteredDisplay(filterIndex);
    this->scheduleUpdate();
}

void FilterSample::onSpriteFilter(Ref* pSender)
{
    _showArmature = false;
    _filtersNum = _filters.size()+_multiFilters.size();
    this->showFilteredDisplay(filterIndex);
    this->unscheduleUpdate();
}

void FilterSample::onClose(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

Sprite* FilterSample::getFilteredSprite(int index)
{
    if(index >= _filters.size())
    {
        index = index - _filters.size();
        Filters filters = _multiFilters.at(index);
        _nameLabel->setString(_multiFilterNames.at(index));
        return testFilter(filters);
    }
    Filter* filter = _filters.at(index);
    _nameLabel->setString(_filterNames.at(index));
    return testFilter(filter);
}

Node* FilterSample::getFilteredArmatureDisplay(int index)
{
    Filter* filter = _filters.at(index);
    _nameLabel->setString(_filterNames.at(index));
    if(_pArmature)
    {
        _pArmature->dispose();
        CC_SAFE_DELETE(_pArmature);
    }
    _pArmature = DBCCFilterFactory::getInstance()->buildArmature("Dragon", "", "Dragon", "Dragon", "Dragon");
    _pArmature->setFilter(filter);
    //_pArmature = DBCCFilterFactory::getInstance()->buildArmature("1010", "", "1010", "1010", "1010", filter);
    //return dragonBones::DBCCFactory::getInstance()->buildArmatureNode("Dragon");
    return _pArmature->getCCDisplay();
}

void FilterSample::showFilteredDisplay(int index)
{
    if (_pNode) _pNode->removeFromParentAndCleanup(true);
    if(_showArmature)
    {
        _pNode = getFilteredArmatureDisplay(index);
        _pNode->setPosition(VisibleRect::center(0, -170));
        addChild(_pNode);
        _pArmature->getAnimation()->gotoAndPlay("stand");
    }
    else
    {
        _pNode = getFilteredSprite(index);
    }
}

Point FilterSample::getLocation(ccLocation $location)
{
    if ($location == LEFT_TOP)
    {
        return VisibleRect::leftTop(240, -160);
    }
    else if ($location == RIGHT_TOP)
    {
        return VisibleRect::rightTop(-240, -160);
    }
    else if ($location == LEFT_BOTTOM)
    {
        return VisibleRect::leftBottom(240, 160);
    }
    else if ($location == RIGHT_BOTTOM)
    {
        return VisibleRect::rightBottom(-240, 160);
    }
    return VisibleRect::center();
}

Sprite* FilterSample::testFilter(Filter* filter, ccLocation location, int order, const char* path)
{
    FilteredSprite* sprite = FilteredSpriteWithOne::create(path);
    sprite->setFilter(filter);
    sprite->setPosition(getLocation(location));
    this->addChild(sprite, order);
    return sprite;
}

Sprite* FilterSample::testFilter(Filters filters, ccLocation location, int order, const char* path)
{
    FilteredSprite* sprite = FilteredSpriteWithMulti::create(path);
    sprite->setFilters(filters);
    sprite->setPosition(getLocation(location));
    this->addChild(sprite, order);
    return sprite;
}

Sprite* FilterSample::testFilterFromFrame(Filter* filter, ccLocation location, int order, const char* path)
{
    FilteredSprite* sprite = FilteredSpriteWithOne::createWithSpriteFrameName(path);
    sprite->setFilter(filter);
    sprite->setPosition(getLocation(location));
    this->addChild(sprite, order);
    return sprite;
}


Sprite* FilterSample::testFilterFromFrame(Filters filters, ccLocation location, int order, const char* path)
{
    FilteredSprite* sprite = FilteredSpriteWithMulti::createWithSpriteFrameName(path);
    sprite->setFilters(filters);
    sprite->setPosition(getLocation(location));
    this->addChild(sprite, order);
    return sprite;
}

cocos2d::GLProgram* FilterSample::getGrass()
{
    cocos2d::GLProgram* pProg = new GLProgram();
    //pProg->initWithByteArray(ccPositionTextureA8Color_vert, ccShader_grass);
    
    pProg->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    pProg->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
    pProg->link();
    pProg->updateUniforms();
    
    _timeUniformLocation = glGetUniformLocation(pProg->getProgram(), "u_time");
    this->scheduleUpdate();
    
    pProg->use();
    
    return pProg;
}

cocos2d::GLProgram* FilterSample::getEmbossMov()
{
    cocos2d::GLProgram* pProg = new GLProgram();
    //pProg->initWithByteArray(ccPositionTextureA8Color_vert, ccShader_emboss );
    
    pProg->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    pProg->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
    pProg->link();
    pProg->updateUniforms();
    
    _timeUniformLocation = glGetUniformLocation(pProg->getProgram(), "u_time");
    this->scheduleUpdate();
    
    pProg->use();
    
    return pProg;
}

void FilterSample::update(float dt)
{
    if(_showArmature)
    {
        _pArmature->advanceTime(dt);
    }
    else
    {
        _totalTime += dt;
        //CCLOG("show %f, dt %f", _totalTime, $dt);
        _pNode->getGLProgram()->use();
        glUniform1f(_timeUniformLocation, _totalTime);
    }
}

cocos2d::GLProgram* FilterSample::getEmboss()
{
    cocos2d::GLProgram* pProg = new GLProgram();
    pProg->initWithByteArrays(ccPositionTextureA8Color_vert, ccFilterShader_emboss_frag);
    
    
    pProg->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    pProg->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
    pProg->link();
    pProg->updateUniforms();
    return pProg;
}

cocos2d::GLProgram* FilterSample::getColorRamp()
{
    cocos2d::GLProgram* pProg = new GLProgram();
    //pProg->initWithByteArray(ccPositionTextureA8Color_vert,ccShader_colorramp);
    
    pProg->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    pProg->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
    pProg->link();
    pProg->updateUniforms();
    
    glUniform1i(glGetUniformLocation(pProg->getProgram(), "u_colorRampTexture"), 1);
    
    Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("colorRamp.png");
    texture->setAntiAliasTexParameters();
    
    pProg->use();
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture->getName());
    glActiveTexture(GL_TEXTURE0);
    
    return pProg;
}