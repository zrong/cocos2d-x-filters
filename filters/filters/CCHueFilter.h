
#ifndef CCHUE_FILTER
#define CCHUE_FILTER

#include "CCFilter.h"

NS_CC_EXT_BEGIN


//================== HueFilter

class HueFilter : public SingleFloatParamFilter
{

public:
	static HueFilter* create();
	static HueFilter* create(float param);

	HueFilter();

	void setParameter(float param);
protected:
	virtual GLProgram* loadShader();
	virtual void setAttributes(GLProgram* glp);
	virtual void setUniforms(GLProgram* glp);
};

NS_CC_EXT_END

#endif //CCHUE_FILTER
