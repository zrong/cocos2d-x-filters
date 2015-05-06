#ifndef CCBRIGHTNESS_FILTER
#define CCBRIGHTNESS_FILTER

#include "CCFilter.h"

NS_CC_EXT_BEGIN
//================== BrightnessFilter

class BrightnessFilter : public SingleFloatParamFilter
{

public:
	static BrightnessFilter* create();
	static BrightnessFilter* create(float brightness);

	BrightnessFilter();

	virtual void setParameter(float brightness);
protected:
	virtual GLProgram* loadShader();
	virtual void setAttributes(GLProgram* glp);
	virtual void setUniforms(GLProgram* glp);
};

NS_CC_EXT_END

#endif //CCBRIGHTNESS_FILTER