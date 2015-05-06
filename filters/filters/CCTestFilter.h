
#ifndef CCTEST_FILTER
#define CCTEST_FILTER

#include "CCFilter.h"

NS_CC_EXT_BEGIN


//================== TestFilter

class TestFilter : public Filter
{

public:
	static TestFilter* create();
	static TestFilter* create(float resolation);

	TestFilter();

	void setParameter(float resolation);
	virtual void initSprite(FilteredSprite* sprite);
protected:
	virtual GLProgram* loadShader();
	virtual void setAttributes(GLProgram* glp);
	virtual void setUniforms(GLProgram* glp);
	float _textureWidth;
	float _textureHeight;
};

NS_CC_EXT_END

#endif //CCTEST_FILTER
