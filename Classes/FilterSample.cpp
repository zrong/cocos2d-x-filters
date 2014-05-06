#include "FilterSample.h"

USING_NS_CC_EXT;

static int filterIndex = 0;

FilterSample::FilterSample()
: _pFilters(NULL)
, _pSprite(NULL)
{
}

FilterSample::~FilterSample()
{
    CC_SAFE_RELEASE(_pFilters);
}

CCScene* FilterSample::scene()
{
    CCScene *scene = CCScene::create();
    FilterSample *layer = FilterSample::create();
    scene->addChild(layer);
    return scene;
}

bool FilterSample::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCMenuItemImage *item1 = CCMenuItemImage::create("b1.png", "b2.png", this, menu_selector(FilterSample::backCallback));
    CCMenuItemImage *item2 = CCMenuItemImage::create("r1.png", "r2.png", this, menu_selector(FilterSample::restartCallback));
    CCMenuItemImage *item3 = CCMenuItemImage::create("f1.png", "f2.png", this, menu_selector(FilterSample::nextCallback));
    CCMenuItemFont *pClearItem = CCMenuItemFont::create("ClearFilter", this, menu_selector(FilterSample::clearSpriteBack));

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(FilterSample::menuCloseCallback));
    
	pCloseItem->setPosition(VisibleRect::rightBottom(-20,20));

    CCMenu* pMenu = CCMenu::create(item1, item2, item3, pClearItem, pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    CCSize item2Size = item2->getContentSize();
    item1->setPosition(VisibleRect::bottom(-item2Size.width * 2, item2Size.height / 2));
    item2->setPosition(VisibleRect::bottom(0, item2Size.height / 2));
    item3->setPosition(VisibleRect::bottom(item2Size.width * 2, item2Size.height / 2));
    pClearItem->setPosition(VisibleRect::bottom(0, 100));
    pCloseItem->setPosition(VisibleRect::rightBottom(-item2Size.width / 2, item2Size.height / 2));

    this->addChild(pMenu, 1);

    this->initFilters();

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("test2.plist", "test2.png");
	CCSprite* __bg = CCSprite::create("bg.jpg");
	__bg->setPosition(VisibleRect::center());
	this->addChild(__bg, -10);

	this->showSprite(filterIndex);
    
    return true;
}

void FilterSample::initFilters()
{
    _pFilters = CCArray::create(
        //colors
        CCGrayFilter::create(0.2f, 0.3f, 0.5f, 0.1f),
        CCRGBFilter::create(1, 0.5, 0.3),
        CCHueFilter::create(90),
        CCBrightnessFilter::create(0.3),
        CCSaturationFilter::create(0),
        CCExposureFilter::create(2),
        CCGammaFilter::create(2),
        //blurs
        CCGaussianVBlurFilter::create(7),
        CCGaussianHBlurFilter::create(7),
        CCZoomBlurFilter::create(4, 0.7, 0.7),
        CCMotionBlurFilter::create(5, 135),
        //others
        CCSharpenFilter::create(1,1),
        CCArray::create(CCGrayFilter::create(), CCGaussianVBlurFilter::create(10), CCGaussianHBlurFilter::create(10), NULL),
        CCArray::create(CCBrightnessFilter::create(0.1), CCContrastFilter::create(4), NULL),
        CCArray::create(CCHueFilter::create(240), CCSaturationFilter::create(1.5), CCBrightnessFilter::create(-0.4), NULL),
        NULL
     );
    _pFilters->retain();
}

void FilterSample::restartCallback(CCObject* pSender)
{
    showSprite(filterIndex);
}

void FilterSample::nextCallback(CCObject* pSender)
{
    filterIndex++;
    filterIndex = filterIndex%_pFilters->count();
    showSprite(filterIndex);
}

void FilterSample::backCallback(CCObject* pSender)
{
    filterIndex--;
    if (filterIndex < 0)
        filterIndex += _pFilters->count();
    showSprite(filterIndex);
}

void FilterSample::clearSpriteBack(CCObject* pSender)
{
    CCFilteredSprite* sprite = dynamic_cast<CCFilteredSprite*>(_pSprite);
    if (sprite) sprite->clearFilter();
}

void FilterSample::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

CCSprite* FilterSample::getFilteredSprite(int index)
{
    CCObject* item = _pFilters->objectAtIndex(index);
    CCFilter* filter = dynamic_cast<CCFilter*>(item);
    if (filter)
    {
        return testFilter(filter);
    }
    else if (CCArray* filters = dynamic_cast<CCArray*>(item))
    {
        return testFilter(filters);
    }
    return NULL;
}

void FilterSample::showSprite(int index)
{
    if (_pSprite) _pSprite->removeFromParentAndCleanup(true);
    _pSprite = getFilteredSprite(index);
}

CCPoint FilterSample::getLocation(ccLocation $location)
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

CCSprite* FilterSample::testFilter(CCFilter* $filter, ccLocation $location, int $order, const char* $path)
{
	CCFilteredSprite* __sprite = CCFilteredSpriteWithOne::create($path);
	__sprite->setFilter($filter);
	__sprite->setPosition(getLocation($location));
	this->addChild(__sprite, $order);
	return __sprite;
}

CCSprite* FilterSample::testFilter(CCArray* $filters, ccLocation $location, int $order, const char* $path)
{
	CCFilteredSprite* __sprite = CCFilteredSpriteWithMulti::create($path);
	__sprite->setFilters($filters);
	__sprite->setPosition(getLocation($location));
	this->addChild(__sprite, $order);
	return __sprite;
}

CCSprite* FilterSample::testFilterFromFrame(CCFilter* $filter, ccLocation $location, int $order, const char* $path)
{
	CCFilteredSprite* __sprite = CCFilteredSpriteWithOne::createWithSpriteFrameName($path);
	__sprite->setFilter($filter);
	__sprite->setPosition(getLocation($location));
	this->addChild(__sprite, $order);
	return __sprite;
}


CCSprite* FilterSample::testFilterFromFrame(CCArray* $filters, ccLocation $location, int $order, const char* $path)
{
	CCFilteredSprite* __sprite = CCFilteredSpriteWithMulti::createWithSpriteFrameName($path);
	__sprite->setFilters($filters);
	__sprite->setPosition(getLocation($location));
	this->addChild(__sprite, $order);
	return __sprite;
}

cocos2d::CCGLProgram* FilterSample::getGrass()
{
	cocos2d::CCGLProgram* __pProg = new CCGLProgram();
	//__pProg->initWithVertexShaderByteArray(ccPositionTextureA8Color_vert, ccShader_grass);

	__pProg->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	__pProg->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	__pProg->link();
	__pProg->updateUniforms();

	_timeUniformLocation = glGetUniformLocation(__pProg->getProgram(), "u_time");
	this->scheduleUpdate();

	__pProg->use();

	return __pProg;
}

cocos2d::CCGLProgram* FilterSample::getEmbossMov()
{
	cocos2d::CCGLProgram* __pProg = new CCGLProgram();
	//__pProg->initWithVertexShaderByteArray(ccPositionTextureA8Color_vert, ccShader_emboss );

	__pProg->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	__pProg->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	__pProg->link();
	__pProg->updateUniforms();

	_timeUniformLocation = glGetUniformLocation(__pProg->getProgram(), "u_time");
	this->scheduleUpdate();

	__pProg->use();

	return __pProg;
}

void FilterSample::update(float $dt)
{
	_totalTime += $dt;
	//CCLOG("show %f, dt %f", _totalTime, $dt);
	_pSprite->getShaderProgram()->use();
	glUniform1f(_timeUniformLocation, _totalTime);
}

cocos2d::CCGLProgram* FilterSample::getEmboss()
{
	cocos2d::CCGLProgram* __pProg = new CCGLProgram();
	__pProg->initWithVertexShaderByteArray(ccPositionTextureA8Color_vert, ccFilterShader_emboss_frag);

	__pProg->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	__pProg->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	__pProg->link();
	__pProg->updateUniforms();
	return __pProg;
}

cocos2d::CCGLProgram* FilterSample::getColorRamp()
{
	cocos2d::CCGLProgram* __pProg = new CCGLProgram();
	//__pProg->initWithVertexShaderByteArray(ccPositionTextureA8Color_vert,ccShader_colorramp);

	__pProg->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	__pProg->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	__pProg->link();
	__pProg->updateUniforms();

	glUniform1i(glGetUniformLocation(__pProg->getProgram(), "u_colorRampTexture"), 1);

	CCTexture2D* __texture = CCTextureCache::sharedTextureCache()->addImage("colorRamp.png");
	__texture->setAntiAliasTexParameters();
	
	__pProg->use();
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, __texture->getName());
	glActiveTexture(GL_TEXTURE0);

	return __pProg;
}