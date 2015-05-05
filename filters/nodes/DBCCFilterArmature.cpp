#include "DBCCFilterArmature.h"

NS_CC_EXT_BEGIN

DBCCFilterArmature::DBCCFilterArmature(dragonBones::ArmatureData *armatureData,
                                       dragonBones::Animation *animation,
                                       dragonBones::IEventDispatcher *eventDispatcher,
                                       cocos2d::Node *display)
: dragonBones::DBCCArmature(armatureData, animation, eventDispatcher, display)
, _filter(nullptr)
{
}

DBCCFilterArmature::~DBCCFilterArmature()
{
    dispose();
}

Filter* DBCCFilterArmature::getFilter()
{
    return _filter;
}

void DBCCFilterArmature::setFilter(Filter *filter)
{
    _filter = filter;
}

NS_CC_EXT_END