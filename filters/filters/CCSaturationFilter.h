#ifndef CCSATURATION_FILTER
#define CCSATURATION_FILTER

#include "CCFilter.h"

NS_CC_EXT_BEGIN


//================== SaturationFilter

class SaturationFilter : public SingleFloatParamFilter
{

public:
	static SaturationFilter* create();
	static SaturationFilter* create(float param);

	SaturationFilter();

	virtual void setParameter(float param);
protected:
	virtual GLProgram* loadShader();
	virtual void setAttributes(GLProgram* glp);
	virtual void setUniforms(GLProgram* glp);
};


NS_CC_EXT_END

#endif //CCSATURATION_FILTER
