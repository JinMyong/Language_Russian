//
//  Hero.cpp
//  AlephBet
//
//  Created by Fredric on 1/25/16.
//
//

#include "Hero.hpp"
#include "SoundEffects.hpp"
#include "Global.hpp"

bool Hero::init()
{
    if (!CCSprite::init()) {
        return false;
    }
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile(getResPath("images/gameScene/character_animation.plist"));
    options = GameOptions::getInstance();
    stop();
//    shoot();
    return true;
}

void Hero::stop()
{
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCArray* animFrames = CCArray::create();
    CCSpriteFrame* frame;
    char str[20] = {0};
    int item_no = options->getItem();
    switch (item_no) {
        case item_Pencil:
                frame = cache->spriteFrameByName("char_pencil.png");
                animFrames->addObject(frame);
            break;
        case item_Fish:
            for (int i = 1; i <= 5; i++) {
                sprintf(str, "char_fish_%d.png",i);
                CCSpriteFrame* frame = cache->spriteFrameByName(str);
                animFrames->addObject(frame);
            }
            break;
        case item_Balloon:
            frame = cache->spriteFrameByName("char_balloon.png");
            animFrames->addObject(frame);
            break;
        case item_LightBulb:
            frame = cache->spriteFrameByName("char_bulb.png");
            animFrames->addObject(frame);
            break;
        case item_Egg:
            frame = cache->spriteFrameByName("char_egg.png");
            animFrames->addObject(frame);
            break;
        case item_Airplane:
            frame = cache->spriteFrameByName("char_airplane.png");
            animFrames->addObject(frame);
            break;
        default:
            break;
    }
    
    CCAnimation* stopanimation= CCAnimation::createWithSpriteFrames(animFrames, 0.2f);
    CCAnimate* ani = CCAnimate::create(stopanimation);
    CCRepeatForever* runani = CCRepeatForever::create(ani);
    this->stopAllActions();
    this->runAction(runani);
}

void Hero::shoot()
{
    // Play Shoot Sound Effect
    SoundEffects::getInstance()->playThrowItem();
    
    CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    CCArray* animFrames = CCArray::create();
    char str[20];
    for (int i = 1; i < 5; i++) {
        sprintf(str, "char_%d.png", i);
        CCSpriteFrame* frame = cache->spriteFrameByName(str);
        animFrames->addObject(frame);
    }
    CCAnimation* shootAnimation = CCAnimation::createWithSpriteFrames(animFrames, 0.05f);
    CCAnimate* shootAnim = CCAnimate::create(shootAnimation);
    
    this->stopAllActions();
    this->runAction(shootAnim);
}