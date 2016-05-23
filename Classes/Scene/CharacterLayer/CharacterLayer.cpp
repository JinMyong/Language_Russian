//
//  CharacterLayer.cpp
//  AlephBet
//
//  Created by Fredric on 1/26/16.
//
//

#include "CharacterLayer.hpp"
#include "GameScene.hpp"


#define POS_PENCIL      ccp(395 * SCALEX, 425 * SCALEY)
#define POS_FISH        ccp(400 * SCALEX, 430 * SCALEY)
#define POS_BULB        ccp(400 * SCALEX, 430 * SCALEY)
#define POS_EGG         ccp(400 * SCALEX, 430 * SCALEY)
#define POS_AIRPLANE    ccp(400 * SCALEX, 430 * SCALEY)
#define POS_BALLOON     ccp(400 * SCALEX, 430 * SCALEY)

bool CharacterLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    winSize = CCDirector::sharedDirector()->getWinSize();
    options = GameOptions::getInstance();
    createObjects();
    stop();
    return true;
}

void CharacterLayer::createObjects()
{
    hero = Hero::create();
    hero->setScale(SCALE);
    hero->setPosition(ccp(winSize.width * 0.5 - 30 * SCALEX, 354 * SCALEY));
    this->addChild(hero, 1);
    
    shootItem = ShootItem::create();
    ThrowThings item = options->getItem();
    switch (item) {
        case item_Pencil:
            shootItem->setPosition(POS_PENCIL);
            break;
        case item_Fish:
            shootItem->setPosition(POS_FISH);
            break;
        case item_Balloon:
            shootItem->setPosition(POS_BALLOON);
            break;
        case item_Egg:
            shootItem->setPosition(POS_EGG);
            break;
        case item_LightBulb:
            shootItem->setPosition(POS_BULB);
            break;
        case item_Airplane:
            shootItem->setPosition(POS_AIRPLANE);
            break;
        default:
            break;
    }
    
    shootItem->setScale(SCALE);
    this->addChild(shootItem, 0);
}

void CharacterLayer::shoot(CCPoint dest, bool wasGoodHit)
{
    target_pos = dest;
    goodHit = wasGoodHit;
    CCCallFunc* shoot_func = CCCallFunc::create(this, callfunc_selector(CharacterLayer::doShoot));
    CCCallFunc* end_func;
    if (wasGoodHit) {
        end_func = CCCallFunc::create(this, callfunc_selector(CharacterLayer::endHitShot));
    }else
    {
        end_func = CCCallFunc::create(this, callfunc_selector(CharacterLayer::endMissShot));
    }
    CCSequence* action_seq = CCSequence::create(shoot_func,
                                                CCDelayTime::create(1.5),
                                                end_func, NULL);
    this->runAction(action_seq);
}

void CharacterLayer::stop()
{
    hero->stop();
    shootItem->stop();
    shootItem->setOpacity(0xff);
    ThrowThings item = options->getItem();
    switch (item) {
        case item_Pencil:
            shootItem->setPosition(POS_PENCIL);
            break;
        case item_Fish:
            shootItem->setPosition(POS_FISH);
            break;
        case item_Balloon:
            shootItem->setPosition(POS_BALLOON);
            break;
        case item_Egg:
            shootItem->setPosition(POS_EGG);
            break;
        case item_LightBulb:
            shootItem->setPosition(POS_BULB);
            break;
        case item_Airplane:
            shootItem->setPosition(POS_AIRPLANE);
            break;
        default:
            break;
    }
    shootItem->setVisible(false);
}

void CharacterLayer::doShoot()
{
    hero->shoot();
    shootItem->setVisible(true);
    shootItem->setOpacity(0xff);
    shootItem->flying(target_pos, goodHit);
}

void CharacterLayer::endHitShot()
{
    CCLog("TargetLayer::endHitShot");
    // Set the game state to "hit"
    ((GameScene*)this->getParent())->changeGameState(GAME_HIT);
}

void CharacterLayer::endMissShot()
{
    CCLog("TargetLayer::endMissedShot");
    // Set the game state to missed
    ((GameScene*)this->getParent())->changeGameState(GAME_MISS);
}