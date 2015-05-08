/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.
 Copyright (c) 2015      Jacky Tsang (zengrong.net)
 
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

#ifndef DBCCFILTERARMATURE_H
#define DBCCFILTERARMATURE_H

#include "DragonBonesHeaders.h"
#include "renderer/DBCCRenderHeaders.h"
#include "filters/filters/CCFilter.h"
#include "filters/nodes/CCFilteredSprite.h"

NS_CC_EXT_BEGIN

class DBCCFilterArmature : public :: dragonBones::DBCCArmature
{
public:
    DBCCFilterArmature(dragonBones::ArmatureData *armatureData,
                       dragonBones::Animation *animation,
                       dragonBones::IEventDispatcher *eventDispatcher,
                       cocos2d::Node *display);
    ~DBCCFilterArmature() override;
    Filter* getFilter();
    void setFilter(Filter* filter);
    void clearFilter();
private:
    Filter* _filter;
};

NS_CC_EXT_END

#endif /* defined(DBCCFILTERARMATURE_H) */
