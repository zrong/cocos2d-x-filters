/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2014      Jacky Tsang (zengrong.net)

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef CCSHADER_FILTER_H
#define CCSHADER_FILTER_H

#include "cocos2d.h"
#include "extensions/ExtensionMacros.h"
#include "platform/CCGL.h"
#include "filters/shaders/ccFilterShaders.h"

USING_NS_CC;

NS_CC_EXT_BEGIN

class FilteredSprite;

//================== Filter

class Filter : public Ref
{
public:
	Filter();
	~Filter();

	virtual void initSprite(FilteredSprite* sprite);
	virtual void draw();
	GLProgram* getProgram();
    GLProgramState* getGLProgramState();

	const char* shaderName;
protected:
    GLProgramState* _pProgramState;
	void initProgram();
	virtual GLProgram* loadShader();
	virtual void setAttributes(GLProgram* glp);
	virtual void setUniforms(GLProgram* glp);
};

class SingleFloatParamFilter : public Filter
{
public:
	SingleFloatParamFilter();

	virtual void setParameter(float param);
protected:
	float _param;
};

typedef Vector<Filter*> Filters;

NS_CC_EXT_END

#endif /* CCSHADER_FILTER_H */
