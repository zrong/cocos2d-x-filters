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
    clearFilter();
    _filter = filter;
    for(size_t i=0; i < _slotList.size(); ++i)
    {
        auto *slot = _slotList[i];
        if(slot)
        {
            auto &displayList = slot->getDisplayList();
            for(size_t j=0; j<displayList.size(); ++j)
            {
                if(displayList[j].second == dragonBones::DisplayType::DT_ARMATURE)
                {
                    DBCCFilterArmature *childArmature = static_cast<DBCCFilterArmature*>(displayList[j].first);
                    if(childArmature)
                    {
                        childArmature->setFilter(_filter);
                    }
                }
                else if(displayList[j].second == dragonBones::DisplayType::DT_IMAGE)
                {
                    FilteredSprite *display = static_cast<FilteredSprite*>(displayList[j].first);
                    if(display)
                    {
                        display->setFilter(_filter);
                    }
                }
            }
        }
    }
}

void DBCCFilterArmature::clearFilter()
{
    for(size_t i=0; i < _slotList.size(); ++i)
    {
        auto *slot = _slotList[i];
        if(slot)
        {
            auto &displayList = slot->getDisplayList();
            for(size_t j=0; j<displayList.size(); ++j)
            {
                if(displayList[j].second == dragonBones::DisplayType::DT_ARMATURE)
                {
                    DBCCFilterArmature *childArmature = static_cast<DBCCFilterArmature*>(displayList[j].first);
                    if(childArmature)
                    {
                        childArmature->clearFilter();
                    }
                }
                else if(displayList[j].second == dragonBones::DisplayType::DT_IMAGE)
                {
                    FilteredSprite *display = static_cast<FilteredSprite*>(displayList[j].first);
                    if(display)
                    {
                        display->clearFilter();
                    }
                }
            }
        }
    }
}

NS_CC_EXT_END