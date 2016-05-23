//
//  ShootItem.cpp
//  AlephBet
//
//  Created by Fredric on 1/26/16.
//
//

#include "ShootItem.hpp"
#include "Const.h"
#include "CharacterLayer.hpp"
#include "SoundEffects.hpp"
#include "Global.hpp"

bool ShootItem::init()
{
    if (!CCSprite::init()) {
        return false;
    }
    options = GameOptions::getInstance();
    item_no = options->getItem();
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile(getResPath("images/gameScene/throwingitem_animation.plist"));
    stop();
    return true;
}

void ShootItem::flying(CCPoint pos, bool success)
{
    CCMoveTo* moveAction = CCMoveTo::create(1, pos);
    CCEaseSineInOut* easeMoveAction = CCEaseSineInOut::create(moveAction);
    CCScaleBy* scalebyAction = CCScaleBy::create(1, 0.7);
    CCFadeOut* fade_action = CCFadeOut::create(0.5);
    
    this->stopAllActions();
    CCRotateBy* rotation = CCRotateBy::create(1, -270);
    CCSpawn* spawn;
    
    float dx = this->getPositionX() - pos.x;
    float dy = this->getPositionY() - pos.y;
    float angleRads = atanf(dx / dy);
    float angleDegs = CC_RADIANS_TO_DEGREES(angleRads);
    
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCArray* aniframes = CCArray::create();
    CCAnimation* successAnimation;
    CCAnimate* ani;
    CCRepeat* repeatAction;
    char filename[30];
    
    switch (item_no) {
        case item_Pencil:
            spawn = CCSpawn::create(easeMoveAction, scalebyAction, NULL);
            this->setRotation(angleDegs);
            this->setAnchorPoint(ccp(0.5, 1));
            break;
        case item_Fish:
            for (int index = 1; index <= 5; index++) {
                sprintf(filename, "fish_wiggle_%d.png", index);
                CCSpriteFrame* frame = cache->spriteFrameByName(filename);
                aniframes->addObject(frame);
            }
            successAnimation = CCAnimation::createWithSpriteFrames(aniframes, 0.1);
            ani = CCAnimate::create(successAnimation);
            repeatAction = CCRepeat::create(ani, 2);
            spawn = CCSpawn::create(easeMoveAction, scalebyAction, repeatAction, NULL);
            this->setRotation(angleDegs);
            this->setAnchorPoint(ccp(0.5, 1));
            break;
        case item_Egg:
            spawn = CCSpawn::create(easeMoveAction, rotation, scalebyAction, NULL);
            break;
        case item_Balloon:
            spawn = CCSpawn::create(easeMoveAction, rotation, scalebyAction, NULL);
            break;
        case item_Airplane:
            for (int index = 1; index <= 4; index++) {
                sprintf(filename, "airplane_fly_%d.png", index);
                CCSpriteFrame* frame = cache->spriteFrameByName(filename);
                aniframes->addObject(frame);
            }
            successAnimation = CCAnimation::createWithSpriteFrames(aniframes, 0.25);
            ani = CCAnimate::create(successAnimation);
            spawn = CCSpawn::create(easeMoveAction,ani, NULL);
            this->setRotation(angleDegs);
            this->setAnchorPoint(ccp(0.5, 1));
            break;
        case item_LightBulb:
            spawn = CCSpawn::create(easeMoveAction, rotation, scalebyAction, NULL);
            break;
        default:
            break;
    }
    
    CCCallFunc* result_func;
    if (success) {
        result_func = CCCallFunc::create(this, callfunc_selector(ShootItem::shooted));
    }else
    {
        result_func = CCCallFunc::create(this, callfunc_selector(ShootItem::failed));
    }
    CCCallFunc* init_action = CCCallFunc::create(this, callfunc_selector(ShootItem::gotoInitState));
    
    CCSequence* action_seq = CCSequence::create(spawn,
                                                result_func,
                                                CCDelayTime::create(1),
                                                fade_action,
                                                init_action,
                                                NULL);
    this->runAction(action_seq);
}

void ShootItem::shooted()
{
//    CCRotateBy* rotate_action = CCRotateBy::create(0.5, -360);
//    this->runAction(rotate_action);
    
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCArray* aniframes = CCArray::create();
    CCAnimation* successAnimation;
    CCAnimate* ani;
    CCRepeat* repeatAction;
    
    char filename[30];
    
    switch (item_no) {
        case item_Pencil:
            break;
        case item_Fish:
            for (int index = 1; index <= 5; index++) {
                sprintf(filename, "fish_wiggle_%d.png", index);
                CCSpriteFrame* frame = cache->spriteFrameByName(filename);
                aniframes->addObject(frame);
            }
            successAnimation = CCAnimation::createWithSpriteFrames(aniframes, 0.1);
            ani = CCAnimate::create(successAnimation);
            repeatAction = CCRepeat::create(ani, 2);
            this->runAction(ani);
            break;
        case item_Balloon:
            break;
        case item_LightBulb:
            this->setRotation(0);
            this->setAnchorPoint(ccp(0.5, 0.5));
            for (int index = 1; index <= 5 ; index++) {
                sprintf(filename, "bulb_light_%d.png", index);
                CCSpriteFrame* frame = cache->spriteFrameByName(filename);
                aniframes->addObject(frame);
            }
            successAnimation = CCAnimation::createWithSpriteFrames(aniframes, 0.2);
            ani = CCAnimate::create(successAnimation);
            this->runAction(ani);
            break;
        case item_Egg:
            break;
        case item_Airplane:
            break;
        default:
            break;
    }
    SoundEffects::getInstance()->playTargetHit(item_no, true);
}

void ShootItem::failed()
{
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCArray* aniframes = CCArray::create();
    CCAnimation* flyingAnimation;
    CCAnimate* ani;
    CCMoveBy* move;
    CCSpawn* action_spawn;
    CCRotateBy* rotate_action;
    CCEaseIn* sliedmove;
    
    char filename[30];
    switch (item_no) {
        case item_Pencil:
            move = CCMoveBy::create(0.5, ccp(0, -300 * SCALEY));
            rotate_action = CCRotateBy::create(0.5, -360);
            action_spawn = CCSpawn::create(move, rotate_action, NULL);
            this->runAction(action_spawn);
            break;
        case item_Fish:
            move = CCMoveBy::create(1, ccp(0, -300 * SCALEY));
            sliedmove = CCEaseIn::create(move, 3);
            this->runAction(sliedmove);
            break;
        case item_Balloon:
            for (int index = 1; index < 4; index++) {
                sprintf(filename, "balloon_break_%d.png", index);
                CCSpriteFrame* frame = cache->spriteFrameByName(filename);
                aniframes->addObject(frame);
            }
            flyingAnimation = CCAnimation::createWithSpriteFrames(aniframes, 0.05);
            ani = CCAnimate::create(flyingAnimation);
            action_spawn = CCSpawn::create(ani, NULL);
            this->setAnchorPoint(ccp(0.5, 0.7));
            this->setRotation(0);
            this->runAction(action_spawn);
            break;
        case item_LightBulb:
            for (int index = 1; index < 6; index++) {
                sprintf(filename, "bulb_break_%d.png", index);
                CCSpriteFrame* frame = cache->spriteFrameByName(filename);
                aniframes->addObject(frame);
            }
            flyingAnimation = CCAnimation::createWithSpriteFrames(aniframes, 0.05);
            ani = CCAnimate::create(flyingAnimation);
            move = CCMoveBy::create(0.5, ccp(0, -300 * SCALEY));
            action_spawn = CCSpawn::create(ani, move, NULL);
            this->setAnchorPoint(ccp(0.5, 0.5));
            this->setRotation(0);
            this->runAction(action_spawn);
            break;
        case item_Egg:
            for (int index = 1; index < 4; index++) {
                sprintf(filename, "egg_break_%d.png", index);
                CCSpriteFrame* frame = cache->spriteFrameByName(filename);
                aniframes->addObject(frame);
            }
            flyingAnimation = CCAnimation::createWithSpriteFrames(aniframes, 0.05);
            ani = CCAnimate::create(flyingAnimation);
            action_spawn = CCSpawn::create(ani, NULL);
            this->setAnchorPoint(ccp(0.5, 0.6));
            this->setRotation(0);
            this->runAction(action_spawn);
            break;
        case item_Airplane:
            rotate_action = CCRotateBy::create(0.5, -360);
            move = CCMoveBy::create(0.5, ccp(0, -300 * SCALEY));
            sliedmove = CCEaseIn::create(move, 3);
            action_spawn = CCSpawn::create(rotate_action, sliedmove, NULL);
            this->setAnchorPoint(ccp(0.5, 0.5));
            this->setRotation(0);
            this->runAction(action_spawn);
            break;
        default:
            break;
    }
    SoundEffects::getInstance()->playTargetHit(item_no, false);
}

void ShootItem::stop()
{
    switch (item_no) {
        case item_Pencil:
            this->initWithSpriteFrameName("pencil.png");
            this->setScale(SCALE);
            this->setAnchorPoint(ccp(0.2, 0.5));
            break;
        case item_Fish:
            this->initWithSpriteFrameName("fish_wiggle_1.png");
            this->setScale(SCALE);
            this->setAnchorPoint(ccp(0.2, 0.5));
            this->setRotation(45);
            break;
        case item_Balloon:
            this->initWithSpriteFrameName("balloon.png");
            this->setScale(SCALE);
            break;
        case item_LightBulb:
            this->initWithSpriteFrameName("bulb_break_1.png");
            this->setScale(SCALE);
            this->setAnchorPoint(ccp(0.2, 0.5));
            this->setRotation(45);
            break;
        case item_Egg:
            this->initWithSpriteFrameName("egg.png");
            this->setScale(SCALE * 1.2);
            break;
        case item_Airplane:
            this->initWithSpriteFrameName("airplane_fly_1.png");
            this->setScale(SCALE);
            this->setAnchorPoint(ccp(0.2, 0.5));
            this->setRotation(45);
            break;
        default:
            break;
    }
    
}

void ShootItem::gotoInitState()
{
    ((CharacterLayer*)this->getParent())->stop();
}

void ShootItem::playEffect(ThrowThings item, bool wasGoodHit)
{
    SoundEffects::getInstance()->playTargetHit(item, wasGoodHit);
}
