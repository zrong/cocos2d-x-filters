
#ifndef CCHAZE_FILTER
#define CCHAZE_FILTER

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== HazeFilter

class HazeFilter : public Filter
{

public:
	static HazeFilter* create();
	static HazeFilter* create(float hazeDistance, float slope);

	HazeFilter();

	void setParameter(float hazeDistance, float slope);
protected:
	virtual GLProgram* loadShader();
	virtual void setAttributes(GLProgram* glp);
	virtual void setUniforms(GLProgram* glp);
	float _hazeDistance;
	float _slope;
};

NS_CC_EXT_END

#endif //CCHAZE_FILTER
