#ifndef CCCONTRAST_FILTER
#define CCCONTRAST_FILTER

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== ContrastFilter

class ContrastFilter : public SingleFloatParamFilter
{

public:
	static ContrastFilter* create();
	static ContrastFilter* create(float param);

	ContrastFilter();

	virtual void setParameter(float param);
protected:
	virtual GLProgram* loadShader();
	virtual void setAttributes(GLProgram* glp);
	virtual void setUniforms(GLProgram* glp);
};

NS_CC_EXT_END

#endif //CCCONTRAST_FILTER