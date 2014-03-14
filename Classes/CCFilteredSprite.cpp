#include "CCFilteredSprite.h"

CCFilteredSprite::CCFilteredSprite()
:_pFilters(NULL)
{

}


CCFilteredSprite::~CCFilteredSprite()
{
}


CCFilteredSprite* CCFilteredSprite::create()
{
	CCFilteredSprite *pSprite = new CCFilteredSprite();
	if (pSprite && pSprite->init())
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

CCFilteredSprite* CCFilteredSprite::create(const char* $pszFileName)
{
	CCFilteredSprite *pobSprite = new CCFilteredSprite();
	if (pobSprite && pobSprite->initWithFile($pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCFilteredSprite* CCFilteredSprite::create(const char* $pszFileName, const CCRect& $rect)
{
	CCFilteredSprite *pobSprite = new CCFilteredSprite();
	if (pobSprite && pobSprite->initWithFile($pszFileName, $rect))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCFilteredSprite* CCFilteredSprite::createWithTexture(CCTexture2D* $pTexture)
{
	CCFilteredSprite *pobSprite = new CCFilteredSprite();
	if (pobSprite && pobSprite->initWithTexture($pTexture))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCFilteredSprite* CCFilteredSprite::createWithTexture(CCTexture2D* $pTexture, const CCRect& $rect)
{
	CCFilteredSprite *pobSprite = new CCFilteredSprite();
	if (pobSprite && pobSprite->initWithTexture($pTexture, $rect))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCFilteredSprite* CCFilteredSprite::createWithSpriteFrame(CCSpriteFrame* $pSpriteFrame)
{
	CCFilteredSprite *pobSprite = new CCFilteredSprite();
	if ($pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame($pSpriteFrame))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCFilteredSprite* CCFilteredSprite::createWithSpriteFrameName(const char* $pszSpriteFrameName)
{
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName($pszSpriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = { 0 };
	sprintf(msg, "Invalid spriteFrameName: %s", $pszSpriteFrameName);
	CCAssert(pFrame != NULL, msg);
#endif

	return createWithSpriteFrame(pFrame);
}

CCFilteredSprite* CCFilteredSprite::create(const char* $pszFileName, CCShaderFilter* $pFilter)
{
	CCFilteredSprite *pobSprite = create($pszFileName);
	pobSprite->setFilter($pFilter);
	return pobSprite;
}

CCFilteredSprite* CCFilteredSprite::create(const char* $pszFileName, CCShaderFilter* $pFilter, 
	const CCRect& rect)
{
	CCFilteredSprite *pobSprite = CCFilteredSprite::create($pszFileName, rect);
	pobSprite->setFilter($pFilter);
	return pobSprite;
}

CCFilteredSprite* CCFilteredSprite::createWithTexture(CCTexture2D* $pTexture, CCShaderFilter* $pFilter)
{
	CCFilteredSprite *pobSprite = createWithTexture($pTexture);
	pobSprite->setFilter($pFilter);
	return pobSprite;
}

CCFilteredSprite* CCFilteredSprite::createWithTexture(CCTexture2D* $pTexture, CCShaderFilter* $pFilter,
	const CCRect& $rect)
{
	CCFilteredSprite *pobSprite = createWithTexture($pTexture, $rect);
	pobSprite->setFilter($pFilter);
	return pobSprite;
}

CCFilteredSprite* CCFilteredSprite::createWithSpriteFrame(CCSpriteFrame* $pSpriteFrame, 
	CCShaderFilter* $pFilter)
{
	CCFilteredSprite *pobSprite = createWithSpriteFrame($pSpriteFrame);
	pobSprite->setFilter($pFilter);
	return pobSprite;
}

CCFilteredSprite* CCFilteredSprite::createWithSpriteFrameName(const char* $pszSpriteFrameName, 
	CCShaderFilter* $pFilter)
{
	CCFilteredSprite *pobSprite = createWithSpriteFrameName($pszSpriteFrameName);
	pobSprite->setFilter($pFilter);
	return pobSprite;
}

CCFilteredSprite* CCFilteredSprite::create(const char* $pszFileName, CCArray* $pFilters)
{
	CCFilteredSprite *pobSprite = CCFilteredSprite::create($pszFileName);
	pobSprite->setFilters($pFilters);
	return pobSprite;
}

CCFilteredSprite* create(const char* $pszFileName, CCArray* $pFilters,
	const CCRect& $rect)
{
	CCFilteredSprite *pobSprite = CCFilteredSprite::create($pszFileName, $rect);
	pobSprite->setFilters($pFilters);
	return pobSprite;
}

CCFilteredSprite* createWithTexture(CCTexture2D* $pTexture, CCArray* $pFilters)
{
	CCFilteredSprite *pobSprite = CCFilteredSprite::createWithTexture($pTexture);
	pobSprite->setFilters($pFilters);
	return pobSprite;
}

CCFilteredSprite* createWithTexture(CCTexture2D* $pTexture, CCArray* $pFilters,
	const CCRect& rect)
{
	CCFilteredSprite *pobSprite = CCFilteredSprite::createWithTexture($pTexture, rect);
	pobSprite->setFilters($pFilters);
	return pobSprite;
}

CCFilteredSprite* createWithSpriteFrame(CCSpriteFrame* $pSpriteFrame,
	CCArray* $pFilters)
{
	CCFilteredSprite *pobSprite = CCFilteredSprite::createWithSpriteFrame($pSpriteFrame);
	pobSprite->setFilters($pFilters);
	return pobSprite;
}

CCFilteredSprite* createWithSpriteFrameName(const char* $pszSpriteFrameName,
	CCArray* $pFilters)
{
	CCFilteredSprite *pobSprite = CCFilteredSprite::createWithSpriteFrameName($pszSpriteFrameName);
	pobSprite->setFilters($pFilters);
	return pobSprite;
}

void CCFilteredSprite::draw()
{
	CC_NODE_DRAW_SETUP();
	
	ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);

	ccGLBindTexture2D(this->getTexture()->getName());
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);

#define kQuadSize sizeof(m_sQuad.bl)
	long offset = (long)&m_sQuad;

	// vertex
	int diff = offsetof(ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// texCoods
	diff = offsetof(ccV3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// color
	diff = offsetof(ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));

	// show custom filter
	if (_pFilters && _pFilters->count()==1)
	{
		static_cast<CCShaderFilter*>(_pFilters->objectAtIndex(0))->draw();
	}

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	CC_INCREMENT_GL_DRAWS(1);
}

void CCFilteredSprite::setFilter(CCShaderFilter* $pFilter)
{
	CCArray* __pFilters = CCArray::create($pFilter, NULL);
	setFilters(__pFilters);
}

void CCFilteredSprite::setFilters(CCArray* $pFilters)
{
	CC_SAFE_RETAIN($pFilters);
	CC_SAFE_RELEASE(_pFilters);
	_pFilters = $pFilters;
	CCLOG("setFilters:%d", _pFilters->count());
	updateFilters();
}

bool CCFilteredSprite::updateFilters()
{
	CCAssert(_pFilters, "Invalid CCShaderFilter!");
	do
	{	
		unsigned int __count = _pFilters->count();
		CC_BREAK_IF(__count == 0);
		CCShaderFilter* __shader = NULL;
		if (__count == 1)
		{
			__shader = static_cast<CCShaderFilter*>(_pFilters->objectAtIndex(0));
			__shader->initSprite(this);
			if (__shader->getProgram())
			{
				setShaderProgram(__shader->getProgram());
			}
		}
		else
		{
			CCFilteredSprite* __sp = NULL;
			CCTexture2D* __oldTex = this->getTexture();
			CCSize __size = this->getContentSize();
			CCRenderTexture* __canva = CCRenderTexture::create(__size.width, __size.height);
			for (size_t i = 0; i < __count; i++)
			{
				__canva->begin();
				__shader = static_cast<CCShaderFilter*>(_pFilters->objectAtIndex(i));
				__sp = CCFilteredSprite::createWithTexture(__oldTex, __shader);
				__sp->setAnchorPoint(ccp(0,0));
				__sp->visit();
				__canva->end();
				__oldTex = new CCTexture2D();
				__oldTex->initWithImage(__canva->newCCImage(true));
				__oldTex->autorelease();
			}
			this->setTexture(__oldTex);
		}
		CHECK_GL_ERROR_DEBUG();
		CCLOG("updateFilters:%d", _pFilters->count());
		return true;
	} while (0);

	return false;
}

void CCFilteredSprite::drawMultiFilters()
{
}