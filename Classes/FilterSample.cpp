#include "FilterSample.h"

USING_NS_CC_EXT;

CCScene* FilterSample::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    FilterSample *layer = FilterSample::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool FilterSample::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(FilterSample::menuCloseCallback));
    
	pCloseItem->setPosition(VisibleRect::rightBottom(-20,20));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("test2.plist", "test2.png");
	CCSprite* __bg = CCSprite::create("bg.jpg");
	__bg->setPosition(VisibleRect::center());
	this->addChild(__bg, -10);
	this->showSprite();
    
    return true;
}

void FilterSample::showSprite()
{

	//ccnode* __pnode = ccnode::create();
	//CCSprite* __sp1 = CCSprite::create("HelloWorld.png");
	//addChild(__sp1);
	//__sp1->setShaderProgram(getEmboss());
	//__sp1->setPosition(VisibleRect::center());
	//ccsprite* __sp2 = ccsprite::create("grass.png");
	//__pnode->addchild(__sp1);
	//__pnode->addchild(__sp2);
	//__pnode->setposition(VisibleRect::center()));
	//__pnode->setshaderprogram(this->getcolorramp());
	//this->addchild(__pnode, 0);

	//_pSprite = CCSprite::create("grass.png");

	//_pSprite = CCFilteredSprite::create("grass5.png", __grayFilter);
	////_pSprite->setShaderProgram(this->getGrass());
	//_pSprite->setPosition(ccp($size->width / 2 + $origin->x, $size->height / 2 + $origin->y));
	//this->addChild(_pSprite, 0);

	//CCGrayFilter* __grayFilter = CCGrayFilter::create(ccc4f(0.2f, 0.3f, 0.4f, 0.0f));
	//CCSprite* __graySprite = CCFilteredSprite::create("FilterSample.png", __grayFilter);
	//__graySprite->setPosition(VisibleRect::leftTop(240, -160));
	//this->addChild(__graySprite, 10);

	//CCHBlurFilter* __hblurFilter = CCHBlurFilter::create(0.02f);
	//CCBlurBaseFilter* __vblurFilter = CCVBlurFilter::create(0.02f);
	//testFilter(CCArray::create(__hblurFilter, __vblurFilter, NULL), LEFT_TOP);

	//testFilter(CCMaskFilter::create(CCString::create("mask.png")), RIGHT_TOP);
	//testFilter(CCSharpenFilter::create(9.0f, 2), LEFT_BOTTOM);

	//__sp->setPosition(ccp(200, 200));

	//testFilter(CCBrightnessFilter::create(0.5f), RIGHT_BOTTOM);
	//testFilter(CCRGBFilter::create(0.5f, 0.7f, 0.3f), RIGHT_BOTTOM);
	//testFilter(CCExposureFilter::create(1.5f));
	//testFilter(CCContrastFilter::create(5.5f));
	//testFilter(CCSaturationFilter::create(0.f));
	//testFilter(CCGammaFilter::create(0.2f));
	//testFilter(CCHueFilter::create(90.5f));
	//testFilter(CCHazeFilter::create(0.3, 0));
	//testFilter(CCHBlurFilter::create(0.3));
	//CCSprite* __sprite = testFilter(CCZoomBlurFilter::create(-1.f, 9, 9));
	//__sprite->setTextureRect(CCRectMake(-20,0, 420	, 236));

	//testFilter(CCMotionBlurFilter::create(2.0f, 180));
	//testFilterFromFrame(CCMotionBlurFilter::create(2.0f, 180));

	//This will throw ad CCAssert
	//testFilterFromFrame(CCArray::create(
	//	CCHBlurFilter::create(2.0f),
	//	CCVBlurFilter::create(2.0f), 
	//	NULL), CENTER, 0, "colors2.png");

	//CCSprite* __sp2 = CCSprite::create("HelloWorld2.png");
	//addChild(__sp2, 10);
	//__sp2->setPosition(VisibleRect::center(0, 200));
	//__sp2->setColor(ccBLACK);

	/*CCSprite* __sp1 = testFilter(CCArray::create(CCHBlurFilter::create(0.02), CCVBlurFilter::create(0.02), NULL),
		CENTER, 0, "HelloWorld3.png");*/
	//__sp1->setTextureRect(CCRect(-50, -50, 500, 500));
	//CCLOG("width: %.5f", __sp1->getContentSize().width);

	//testFilter(
	//	CCArray::create(
	//		CCHBlurFilter::create(0.02), CCVBlurFilter::create(0.02),
	//		CCDropShadowFilter::create(0.1), NULL), 
	//	CENTER, 0, "HelloWorld.png");
	//testFilter(CCSepiaFilter::create(0.f));
	//testFilter(CCTestFilter::create(0.f), CENTER, 0, "HelloWorld.png");
	//testFilter(
	//	CCArray::create(
	//	CCHBlurFilter::create(0.1f),
	//	CCVBlurFilter::create(0.3f),
	//	NULL)
	//	);
	//testFilter(CCGrayFilter::create(ccc4f(0.299f, 0.587f, 0.114f, 0.0f)), LEFT_BOTTOM);
	//testFilter(CCGrayFilter::create(ccc4f(0.555, 0.587f, 0.114f, 0.5f)), RIGHT_BOTTOM);
	//testFilter(
	//	CCArray::create(
	//		CCGaussianHBlurFilter::create(3.f),
	//		CCGaussianVBlurFilter::create(3.f), 
	//		NULL),
	//		LEFT_BOTTOM
	//	);
	testFilter(CCGrayFilter::create());

	testFilter(
		CCArray::create(
		CCGaussianHBlurFilter::create(1.f),
		CCGaussianVBlurFilter::create(1.f),
		NULL),
		RIGHT_BOTTOM
		);

	//testFilterFromFrame(CCGrayFilter::create(ccc4f(0.299f, 0.587f, 0.114f, 0.0f)),
	//	LEFT_TOP, 0, "dirt.png");
	testFilterFromFrame(
		CCArray::create(
		CCGaussianHBlurFilter::create(6.f),
		CCGaussianVBlurFilter::create(3.f),
		NULL),
		LEFT_TOP
		);
	testFilterFromFrame(
		CCArray::create(
		CCGrayFilter::create(),
		CCGaussianHBlurFilter::create(1.f),
		CCGaussianVBlurFilter::create(1.f),
		NULL),
		RIGHT_TOP
		);
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
	CCFilteredSprite* __sprite = CCFilteredSpriteWithMulti::create($path);
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


void FilterSample::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
