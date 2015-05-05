#include "DBCCFilterArmature.h"

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

cocos2d::extension::Filter* DBCCFilterArmature::getFilter()
{
    return _filter;
}

void DBCCFilterArmature::setFilter(cocos2d::extension::Filter *filter)
{
    _filter = filter;
}