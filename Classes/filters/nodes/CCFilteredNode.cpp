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

#include "CCFilteredNode.h"

NS_CC_EXT_BEGIN

//================== CCFilteredNode

CCFilteredNode::CCFilteredNode()
: _pFilters(NULL)
{

}


CCFilteredNode::~CCFilteredNode()
{
	CC_SAFE_RELEASE(_pFilters);
}

CCFilteredNode* CCFilteredNode::create()
{
	CCFilteredNode * __fNode = new CCFilteredNode();
	if (__fNode && __fNode->init())
	{
		__fNode->autorelease();
		return __fNode;
	}
	CC_SAFE_DELETE(__fNode);
	return NULL;
}

CCFilteredNode* CCFilteredNode::create(CCFilter* $pFilter)
{
	CCFilteredNode * __fNode = CCFilteredNode::create();
	__fNode->setFilter($pFilter);
	return __fNode;
}

CCFilteredNode* CCFilteredNode::create(CCArray* $pFilters)
{
	CCFilteredNode * __fNode = CCFilteredNode::create();
	__fNode->setFilters($pFilters);
	return __fNode;
}

CCFilter* CCFilteredNode::getFilter(unsigned int $index)
{
	if (!_pFilters || _pFilters->count() == 0 || $index >= _pFilters->count())
	{
		return NULL;
	}
	return static_cast<CCFilter*>(_pFilters->objectAtIndex($index));
}

void CCFilteredNode::setFilter(CCFilter* $pFilter)
{
	CCArray* __pFilters = CCArray::create($pFilter, NULL);
	CCFilteredNode::setFilters(__pFilters);
}

CCArray* CCFilteredNode::getFilters()
{
	return _pFilters;
}

void CCFilteredNode::setFilters(CCArray* $pFilters)
{
	CC_SAFE_RETAIN($pFilters);
	CC_SAFE_RELEASE(_pFilters);
	_pFilters = $pFilters;
	//updateFilters();
}

NS_CC_EXT_END