#include "CCFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

//================== Filter

Filter::Filter()
: shaderName(NULL)
, _pProgramState(NULL)
{
}

Filter::~Filter()
{
	CC_SAFE_RELEASE_NULL(_pProgramState);
}

GLProgram* Filter::getProgram()
{
	return _pProgramState->getGLProgram();
}

GLProgramState* Filter::getGLProgramState() {
    return _pProgramState;
}

void Filter::initProgram()
{
    if (nullptr != _pProgramState) {
        return;
    }
    
    GLProgram* pProgram = nullptr;
    if (nullptr != shaderName) {
        pProgram = GLProgramCache::getInstance()->getGLProgram(shaderName);
    }
	//CCLOG("CCFilter::initProgram %s, program:%d", shaderName, pProgram);
	if (nullptr == pProgram)
	{
		pProgram = loadShader();

        if (nullptr != shaderName) {
            GLProgramCache::getInstance()->addGLProgram(pProgram, this->shaderName);
        }
	}

    _pProgramState = GLProgramState::getOrCreateWithGLProgram(pProgram);
    _pProgramState->retain();
}

void Filter::initSprite(FilteredSprite* sprite)
{
    setUniforms(nullptr);
}

void Filter::draw()
{
	//setUniforms(getProgram());
}

GLProgram* Filter::loadShader()
{
	//CCLOG("Filter::loadShader");
	return nullptr;
}

void Filter::setAttributes(GLProgram* glp)
{
}

void Filter::setUniforms(GLProgram* glp)
{
}

//================== SingleFloatParamFilter

SingleFloatParamFilter::SingleFloatParamFilter()
: _param(0.f)
{
}


void SingleFloatParamFilter::setParameter(float param)
{
	_param = param;
	initProgram();
}

NS_CC_EXT_END