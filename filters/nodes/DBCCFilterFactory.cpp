#include "DBCCFilterFactory.h"

NS_CC_EXT_BEGIN

DBCCFilterFactory* DBCCFilterFactory::_instance = nullptr;

DBCCFilterFactory* DBCCFilterFactory::getInstance()
{
    if (!_instance)
    {
        _instance = new DBCCFilterFactory();
    }
    return _instance;
}

void DBCCFilterFactory::destroyInstance()
{
    if (_instance)
    {
        CC_SAFE_DELETE(_instance);
    }
}

DBCCFilterFactory::DBCCFilterFactory() : _filter(nullptr){}
DBCCFilterFactory::~DBCCFilterFactory() {}

DBCCFilterArmature* DBCCFilterFactory::buildArmature(const std::string &armatureName, const std::string &skinName, const std::string &animationName, const std::string &dragonBonesName, const std::string &textureAtlasName, Filter* filter)
{
    _filter = filter;
    return (DBCCFilterArmature*) DBCCFactory::buildArmature(armatureName, skinName, animationName, dragonBonesName, textureAtlasName);
}

DBCCFilterArmature* DBCCFilterFactory::generateArmature(const dragonBones::ArmatureData *armatureData) const
{
    dragonBones::Animation *animation = new dragonBones::Animation();
    // sprite
    cocos2d::Node *display = cocos2d::Node::create();
    display->setCascadeColorEnabled(true);
    display->setCascadeOpacityEnabled(true);
    display->retain();
    // eventDispatcher
    dragonBones::DBCCEventDispatcher *eventDispatcher = new dragonBones::DBCCEventDispatcher();
    eventDispatcher->eventDispatcher = new cocos2d::EventDispatcher();
    eventDispatcher->eventDispatcher->setEnabled(true);
    // armature
    DBCCFilterArmature* armature = new DBCCFilterArmature((dragonBones::ArmatureData*)(armatureData), animation, eventDispatcher, display);
    armature->setFilter(_filter);
    return armature;
}

void* DBCCFilterFactory::generateDisplay(const dragonBones::ITextureAtlas *textureAtlas,
                                         const dragonBones::TextureData *textureData,
                                         const dragonBones::DisplayData *displayData) const
{
    dragonBones::DBCCTextureAtlas *dbccTextureAtlas = (dragonBones::DBCCTextureAtlas*)(textureAtlas);
    
    if (!dbccTextureAtlas || !textureData) return nullptr;
    
    auto texture = dbccTextureAtlas->getTexture();
    assert(texture);
    
    const float x = textureData->region.x;
    const float y = textureData->region.y;
    const bool rotated = textureData->rotated;
    const float width = rotated ? textureData->region.height : textureData->region.width;
    const float height = rotated ? textureData->region.width : textureData->region.height;
    cocos2d::Rect rect(x, y, width, height);
    cocos2d::Vec2 offset;
    cocos2d::Size originSize(width, height);
    
    cocos2d::Node *display = nullptr;
    
    if (textureData->frame)
    {
        float frameX = -textureData->frame->x;
        float frameY = -textureData->frame->y;
        originSize.width = textureData->frame->width;
        originSize.height = textureData->frame->height;
        // offset = trimed center - origin center
        // y use cocos2d coordinates
        offset.x = (width - originSize.width) * 0.5 + frameX;
        offset.y = (originSize.height - height)*0.5 - frameY;
        
        auto spriteFrame = cocos2d::SpriteFrame::createWithTexture(texture, rect, textureData->rotated, offset, originSize);
        //display = cocos2d::Sprite::createWithSpriteFrame(spriteFrame);
        display = FilteredSpriteWithOne::createWithSpriteFrame(spriteFrame);
        
    }
    else
    {
        //display = cocos2d::Sprite::createWithTexture(texture, rect, rotated);
        display = FilteredSpriteWithOne::createWithTexture(texture, rect);
    }
    // sprite
    
    display->setCascadeColorEnabled(true);
    display->setCascadeOpacityEnabled(true);
    display->retain();
    float pivotX = 0.f;
    float pivotY = 0.f;
    
    if (displayData)
    {
        pivotX = displayData->pivot.x;
        pivotY = displayData->pivot.y;
    }
    display->setAnchorPoint(cocos2d::Vec2(pivotX / originSize.width, 1.f - pivotY / originSize.height));
    display->setContentSize(originSize);
    return display;
}

NS_CC_EXT_END
