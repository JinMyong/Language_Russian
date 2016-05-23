//
//  IntroScene.cpp
//  AlephBet
//
//  Created by Fredric on 12/15/15.
//
//

#include "IntroScene.hpp"
#include "Const.h"
#include "MainMenuScene.hpp"
#include "GameScene.hpp"
#include "SoundEffects.hpp"

CCScene* IntroScene::scene()
{
    CCScene* scene = CCScene::create();
    IntroScene* layer = IntroScene::create();
    scene->addChild(layer);
    return scene;
}

bool IntroScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    winSize = CCDirector::sharedDirector()->getWinSize();
    createUI();
    return true;
}

void IntroScene::createUI()
{
    // Add background image
    CCSprite* bg_spt = CCSprite::create(getResPath(INTRO_BACKGROUND_IMGAE));
    bg_spt->setScaleX(SCALEX);
    bg_spt->setScaleY(SCALEY);
    bg_spt->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    this->addChild(bg_spt);
    
    // Add description bg
    CCSprite* des_bg = CCSprite::create(getResPath(INTRO_DESCRIPTION_BG_IMG));
    des_bg->setScaleX(SCALEX);
    des_bg->setScaleY(SCALEY * 0.5);
    des_bg->setPosition(ccp(winSize.width * 0.5, 798 * SCALEY));
    this->addChild(des_bg);
    
    // Add description text
    CCSprite* des = CCSprite::create(getResPath(INTRO_DESCRIPTION_IMG));
    des->setScale(MIN(SCALEX, SCALEY));
    des->setPosition(ccp(winSize.width * 0.5, 800 * SCALEY));
    this->addChild(des);
    
    // Add character
    CCSprite* character = CCSprite::create(getResPath(INTRO_CHARACTER_IMG));
    character->setScale(SCALE * 0.9);
    character->setPosition(ccp(167 * SCALEX, 385 * SCALEY));
    this->addChild(character);
    
    // Add blue and yellow chair
    CCSprite* bl_chair = CCSprite::create(getResPath(CHAIR_BLUE_IMG));
    bl_chair->setScale(SCALE * 0.9);
    bl_chair->setPosition(ccp(140 * SCALEX, 243 * SCALEY));
    this->addChild(bl_chair);
    
    CCSprite* yl_chair = CCSprite::create(getResPath(CHAIR_YELLOW_IMG));
    yl_chair->setScale(SCALE * 0.9);
    yl_chair->setPosition(ccp(506 * SCALEX, 243 * SCALEY));
    this->addChild(yl_chair);
    
    // Add play, mainmenu buttons
    CCMenuItem* playItem = CCMenuItemImage::create(getResPath(INTRO_PLAY_BUTTON_IMAGE_NOR), getResPath(INTRO_PLAY_BUTTON_IMAGE_PRS), this, menu_selector(IntroScene::gotoplay));
    playItem->setScale(MIN(SCALEX, SCALEY));
    playItem->setPosition(175 * SCALEX, 50 * SCALEY);
    
    CCMenuItem* mainmenuItem = CCMenuItemImage::create(getResPath(INTRO_MAINMENU_BUTTON_IMAGE_NOR), getResPath(INTRO_MAINMENU_BUTTON_IMAGE_PRS), this, menu_selector(IntroScene::gotoMainMenu));
    mainmenuItem->setScale(MIN(SCALEX, SCALEY));
    mainmenuItem->setPosition(467 * SCALEX, 50 * SCALEY);
    
    CCMenu* menu = CCMenu::create(playItem, mainmenuItem, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}

void IntroScene::gotoplay(cocos2d::CCNode *sender)
{
    CCLog("IntroScene:: go to play");
    SoundEffects::getInstance()->playButtonEffect();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, GameScene::scene()));
}

void IntroScene::gotoMainMenu(cocos2d::CCNode *sender)
{
    CCLog("IntroScene:: go to MainMenu");
    SoundEffects::getInstance()->playButtonEffect();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, MainMenuScene::scene()));
}