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

#ifndef CCBLUR_FILTER
#define CCBLUR_FILTER

#include "CCFilter.h"

NS_CC_EXT_BEGIN

//================== CCBlurFilter

class BlurBaseFilter : public SingleFloatParamFilter
{

public:
	BlurBaseFilter();
	virtual void setParameter(float param);
protected:
	virtual void setAttributes(GLProgram* glp);
	virtual void setUniforms(GLProgram* glp);
	float _param;
};

class HBlurFilter : public BlurBaseFilter
{
public:
	static HBlurFilter* create();
	static HBlurFilter* create(float param);

	HBlurFilter();
protected:
	virtual GLProgram* loadShader();

};

class VBlurFilter : public BlurBaseFilter
{
public:
	static VBlurFilter* create();
	static VBlurFilter* create(float param);

	VBlurFilter();
protected:
	virtual GLProgram* loadShader();
};

class GaussianHBlurFilter : public BlurBaseFilter
{
public:
	static GaussianHBlurFilter* create();
	static GaussianHBlurFilter* create(float param);

	GaussianHBlurFilter();
	virtual void initSprite(FilteredSprite* sprite);
protected:
	virtual GLProgram* loadShader();
	virtual void setUniforms(GLProgram* glp);
private:
	float _resolation;
};

class GaussianVBlurFilter : public BlurBaseFilter
{
public:
	static GaussianVBlurFilter* create();
	static GaussianVBlurFilter* create(float param);

	GaussianVBlurFilter();
	virtual void initSprite(FilteredSprite* sprite);
protected:
	virtual GLProgram* loadShader();
	virtual void setUniforms(GLProgram* glp);
private:
	float _resolation;
};

//================== ZoomBlurFilter

class ZoomBlurFilter : public Filter
{

public:
	static ZoomBlurFilter* create();
	static ZoomBlurFilter* create(float blurSize, float centerX, float centerY);

	ZoomBlurFilter();

	void setParameter(float blurSize, float centerX, float centerY);
protected:
	virtual GLProgram* loadShader();
	virtual void setAttributes(GLProgram* glp);
	virtual void setUniforms(GLProgram* glp);
	float _blurSize;
	float _centerX;
	float _centerY;
};

//================== MotionBlurFilter

class MotionBlurFilter : public Filter
{

public:
	static MotionBlurFilter* create();
	static MotionBlurFilter* create(float blurSize, float blurAngle);

	MotionBlurFilter();

	void setParameter(float blurSize, float blurAngle);
	virtual void initSprite(FilteredSprite* sprite);
protected:
	virtual GLProgram* loadShader();
	virtual void setAttributes(GLProgram* glp);
	virtual void setUniforms(GLProgram* glp);
	float _blurSize;
	float _blurAngle;
	float _texelOffsetX;
	float _texelOffsetY;
};

NS_CC_EXT_END
#endif //CCBLUR_FILTER