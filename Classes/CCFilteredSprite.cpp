#include "CCFilteredSprite.h"

CCFilteredSprite::CCFilteredSprite()
:_pFilter(NULL)
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

CCFilteredSprite* CCFilteredSprite::create(const char *pszFileName)
{
	CCFilteredSprite *pobSprite = new CCFilteredSprite();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCFilteredSprite* CCFilteredSprite::create(const char *pszFileName, CCShaderFilter* pFilter)
{
	CCFilteredSprite *pobSprite = create(pszFileName);
	CC_SHADER_SET_FILTER(pobSprite, pFilter);
	return NULL;
}

CCFilteredSprite* CCFilteredSprite::create(const char *pszFileName, const CCRect& rect)
{
	CCFilteredSprite *pobSprite = new CCFilteredSprite();
	if (pobSprite && pobSprite->initWithFile(pszFileName, rect))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCFilteredSprite* CCFilteredSprite::create(const char *pszFileName, CCShaderFilter* pFilter, const CCRect& rect)
{
	CCFilteredSprite *pobSprite = CCFilteredSprite::create(pszFileName, rect);
	CC_SHADER_SET_FILTER(pobSprite, pFilter);
	return NULL;
}

CCFilteredSprite* CCFilteredSprite::createWithTexture(CCTexture2D *pTexture)
{
	CCFilteredSprite *pobSprite = new CCFilteredSprite();
	if (pobSprite && pobSprite->initWithTexture(pTexture, CCRectZero, false))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCFilteredSprite* CCFilteredSprite::createWithTexture(CCTexture2D *pTexture, CCShaderFilter* pFilter)
{
	CCFilteredSprite *pobSprite = createWithTexture(pTexture);
	CC_SHADER_SET_FILTER(pobSprite, pFilter);
	return NULL;
}

CCFilteredSprite* CCFilteredSprite::createWithTexture(CCTexture2D *pTexture, const CCRect& rect)
{
	CCFilteredSprite *pobSprite = new CCFilteredSprite();
	if (pobSprite && pobSprite->initWithTexture(pTexture, rect, false))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCFilteredSprite* CCFilteredSprite::createWithTexture(CCTexture2D *pTexture, CCShaderFilter* pFilter,const CCRect& rect)
{
	CCFilteredSprite *pobSprite = createWithTexture(pTexture, rect);
	CC_SHADER_SET_FILTER(pobSprite, pFilter);
	return NULL;
}


CCFilteredSprite* CCFilteredSprite::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
	CCFilteredSprite *pobSprite = new CCFilteredSprite();
	if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCFilteredSprite* CCFilteredSprite::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame, CCShaderFilter* pFilter)
{
	CCFilteredSprite *pobSprite = createWithSpriteFrame(pSpriteFrame);
	CC_SHADER_SET_FILTER(pobSprite, pFilter);
	return NULL;
}

CCFilteredSprite* CCFilteredSprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
	CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);

#if COCOS2D_DEBUG > 0
	char msg[256] = { 0 };
	sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
	CCAssert(pFrame != NULL, msg);
#endif

	return createWithSpriteFrame(pFrame);
}

CCFilteredSprite* CCFilteredSprite::createWithSpriteFrameName(const char *pszSpriteFrameName, CCShaderFilter* pFilter)
{
	CCFilteredSprite *pobSprite = createWithSpriteFrameName(pszSpriteFrameName);
	CC_SHADER_SET_FILTER(pobSprite, pFilter);
	return NULL;
}

void CCFilteredSprite::draw()
{
	ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);
	ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);

	this->getShaderProgram()->use();
	this->getShaderProgram()->setUniformsForBuiltins();

	ccGLBindTexture2D(this->getTexture()->getName());

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
	if (_pFilter)
	{
		_pFilter->draw();
	}

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	CC_INCREMENT_GL_DRAWS(1);
}

void CCFilteredSprite::setFilter(CCShaderFilter* pFilter)
{
	_pFilter = pFilter;
	_pFilter->retain();
	updateFilter();
}

CCShaderFilter* CCFilteredSprite::getFilter()
{
	return _pFilter;
}

bool CCFilteredSprite::updateFilter()
{
	CCAssert(_pFilter, "Invalid CCShaderFilter!");
	do
	{
		CCGLProgram* __program = _pFilter->getProgram();
		
		setShaderProgram(__program);
		CHECK_GL_ERROR_DEBUG();

		return true;
	} while (0);

	return false;
}