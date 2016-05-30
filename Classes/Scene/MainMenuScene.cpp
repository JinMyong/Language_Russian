//
//  MainMenuScene.cpp
//  AlephBet
//
//  Created by Fredric on 12/15/15.
//
//

#include "MainMenuScene.hpp"
#include "Const.h"
#include "IntroScene.hpp"
#include "ChooseLetterScene.hpp"
#include "GameScene.hpp"
#include "GameOptionScene.hpp"
#include "HighScoreScene.hpp"
#include "AboutScene.hpp"
#include "StoreScene.hpp"
#include "SoundEffects.hpp"
#include "GameOptions.hpp"
#include "CCAlertView.h"

#include "GameResultScene.hpp"




CCScene* MainMenuScene::scene()
{
    CCScene* scene = CCScene::create();
    MainMenuScene* layer = MainMenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenuScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    winSize = CCDirector::sharedDirector()->getWinSize();
    options = GameOptions::getInstance();
    bag = LetterBag::getInstance();
    createUI();
    bool isMusic = CCUserDefault::sharedUserDefault()->getBoolForKey(kMusic, true);
    if (isMusic) {
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
    }else
    {
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
    }
    
    bool isEffect = CCUserDefault::sharedUserDefault()->getBoolForKey(kEffect, true);
    if (isEffect) {
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(1);
    }else
    {
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
    }
    
    SoundEffects::getInstance()->playThemeBackgroundMusic();

    return true;
}

void MainMenuScene::createUI()
{
    // Add Background Image
    CCSprite* bg_spt = CCSprite::create(getResPath(MAINMENU_BACKGROUND_IMAGE));
    bg_spt->setScaleX(SCALEX);
    bg_spt->setScaleY(SCALEY);
    bg_spt->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    this->addChild(bg_spt, 0);
    
    // Add Character Image
    CCSprite* character_spt = CCSprite::create(getResPath(MAINMENU_CHARACTER_BOY_IMG));
    character_spt->setScale(SCALE);
    character_spt->setPosition(ccp(168 * SCALEX, 424 * SCALEY));
    this->addChild(character_spt);
    
    // Add Chairs(blue and yellow)
    CCSprite* chair_blue = CCSprite::create(getResPath(CHAIR_BLUE_IMG));
    chair_blue->setScale(SCALE);
    chair_blue->setPosition(ccp(141 * SCALEX, 277 * SCALEY));
    this->addChild(chair_blue);
    
    CCSprite* chair_yellow = CCSprite::create(getResPath(CHAIR_YELLOW_IMG));
    chair_yellow->setScale(SCALE);
    chair_yellow->setPosition(ccp(507 * SCALEX, 277 * SCALEY));
    this->addChild(chair_yellow);
    
    // Add Top title ("Ready,Set,")
    CCLabelTTF* top_title = CCLabelTTF::create(TXT_MAIN_TOPTITLE, FONT_TITLE, 60 * SCALE);
    top_title->setPosition(ccp(winSize.width * 0.5, 1090 * SCALEY));
    top_title->setColor(COLOR_TITLE_TOP);
    this->addChild(top_title);
    
    // Add Bottom title (GAME NAME)
    CCLabelTTF* bottom_title = CCLabelTTF::create(TXT_MAIN_BOTTOMTITLE, FONT_TITLE, 50 * SCALE);
    bottom_title->setPosition(ccp(winSize.width * 0.5, 45 * SCALEY));
    bottom_title->setColor(COLOR_TITLE_BOTTOM);
    this->addChild(bottom_title);
    
    // Add Buttons(play, choose, options, high score, about)
    CCMenuItem* play_item = CCMenuItemImage::create(getResPath(MAINMENU_PLAY_BTN_IMG_NOR), getResPath(MAINMENU_PLAY_BTN_IMG_PRS), this, menu_selector(MainMenuScene::gotoPlay));
    play_item->setScale(SCALE);
    
    CCMenuItem* choose_letter_item = CCMenuItemImage::create(getResPath(MAINMENU_CHOOSE_BTN_IMG_NOR), getResPath(MAINMENU_CHOOSE_BTN_IMG_PRS), this, menu_selector(MainMenuScene::gotochooseLetter));
    choose_letter_item->setScale(SCALE);
    
    CCMenuItem* option_item = CCMenuItemImage::create(getResPath(MAINMENU_OPTION_BTN_IMG_NOR), getResPath(MAINMENU_OPTION_BTN_IMG_PRS), this, menu_selector(MainMenuScene::gotoOption));
    option_item->setScale(SCALE);
    
    CCMenuItem* high_score_item = CCMenuItemImage::create(getResPath(MAINMENU_HSCORE_BTN_IMG_NOR), getResPath(MAINMENU_HSCORE_BTN_IMG_PRS), this, menu_selector(MainMenuScene::gotoHighScore));
    high_score_item->setScale(SCALE);
    
    CCMenuItem* store_item = CCMenuItemImage::create(getResPath(MAINMENU_BTN_STORE_IMG_NOR), getResPath(MAINMENU_BTN_STORE_IMG_PRS), this, menu_selector(MainMenuScene::gotoStore));
    store_item->setScale(SCALE);
    
    CCMenuItem* about_item = CCMenuItemImage::create(getResPath(MAINMENU_ABOUT_BTN_IMG_NOR), getResPath(MAINMENU_ABOUT_BTN_IMG_PRS), this, menu_selector(MainMenuScene::gotoAbout));
    about_item->setScale(SCALE);
    
    CCMenuItem* reset_item = CCMenuItemImage::create(getResPath(MAINMENU_BTN_RESET_IMG_NOR), getResPath(MAINMENU_BTN_RESET_IMG_PRS), this, menu_selector(MainMenuScene::resetHandler));
    reset_item->setScale(SCALE);
    
    CCMenu* menu = CCMenu::create(play_item,
                                  choose_letter_item,
                                  option_item,
//                                  high_score_item,
                                  store_item,
                                  about_item,
                                  reset_item,
                                  NULL);
    menu->setPosition(449 * SCALEX, 708 * SCALEY);
    menu->alignItemsVerticallyWithPadding(20 * SCALEY);
    menu->setTag(100);
    this->addChild(menu);
}

void MainMenuScene::gotoPlay(cocos2d::CCObject *sender)
{
    CCLog("Play Button Pressed");
    bool enoughLetter = bag->verifyLetterCount();
    SoundEffects::getInstance()->playButtonEffect();
    if (enoughLetter) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, IntroScene::scene()));
    }else
    {
        options->setGotoPlayScene(true);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, ChooseLetterScene::scene()));
    }
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, GameResultScene::scene()));
}

void MainMenuScene::gotochooseLetter(cocos2d::CCObject *sender)
{
    CCLog("Choose Letter Button Pressed");
    SoundEffects::getInstance()->playButtonEffect();
    options->setGotoPlayScene(false);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5,ChooseLetterScene::scene()));
}

void MainMenuScene::gotoOption(cocos2d::CCObject *sender)
{
    CCLog("Option Button Pressed");
    SoundEffects::getInstance()->playButtonEffect();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5,GameOptionsScene::scene()));
}

void MainMenuScene::gotoHighScore(cocos2d::CCObject *sender)
{
    CCLog("High Score Button Pressed");
    SoundEffects::getInstance()->playButtonEffect();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HighScoreScene::scene()));
}

void MainMenuScene::gotoAbout(cocos2d::CCObject *sender)
{
    CCLog("About Button Pressed");
    SoundEffects::getInstance()->playButtonEffect();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, AboutScene::scene()));
}

void MainMenuScene::gotoStore(cocos2d::CCObject *sender)
{
    CCLog("The Shuk Button Pressed");
    SoundEffects::getInstance()->playButtonEffect();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, StoreScene::scene()));
}

void MainMenuScene::resetHandler(cocos2d::CCObject *sender)
{
    CCLog("The Reset Button Pressed");
    SoundEffects::getInstance()->playButtonEffect();
    CCMenu* menu = (CCMenu*)this->getChildByTag(100);
    menu->setEnabled(false);
    CCAlertView* alert = CCAlertView::create("Warning", "You are about to reset this game so that the the level goes back to Level 1 and the coins collected reset.", "", "", this, callfuncO_selector(MainMenuScene::alertOKHandler), callfuncO_selector(MainMenuScene::alertCancelHandler));
    this->addChild(alert, 100);
}

void MainMenuScene::alertOKHandler(cocos2d::CCObject *sender)
{
    SoundEffects::getInstance()->playButtonEffect();
    GameOptions* options = GameOptions::getInstance();
    options->setCoins(0);
    options->setCurrentLevel(0);
    CCMenu* menu = (CCMenu*)this->getChildByTag(100);
    menu->setEnabled(true);
}

void MainMenuScene::alertCancelHandler(cocos2d::CCObject *sender)
{
    SoundEffects::getInstance()->playButtonEffect();
    CCMenu* menu = (CCMenu*)this->getChildByTag(100);
    menu->setEnabled(true);
    return;
}