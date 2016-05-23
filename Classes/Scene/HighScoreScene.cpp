//
//  HighScoreScene.cpp
//  AlephBet
//
//  Created by Fredric on 1/12/16.
//
//

#include "HighScoreScene.hpp"
#include "Const.h"
#include "MainMenuScene.hpp"
#include "Global.hpp"
#include "LetterBag.hpp"
#include "GameOptions.hpp"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    #include "SocialGame.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "platform/android/jni/JniHelper.h"
#endif
#include "SoundEffects.hpp"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

CCScene* HighScoreScene::scene()
{
    CCScene* scene = CCScene::create();
    HighScoreScene* layer = HighScoreScene::create();
    scene->addChild(layer);
    return scene;
}

bool HighScoreScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    highScore = GameOptions::getInstance()->getTotoalScore();
    createUI();
    GameOptions::getInstance()->setCurrentLevel(0);
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    SoundEffects::getInstance()->playLevelComplete(true);
    return true;
}

void HighScoreScene::createUI()
{
    // Add Background Image
    CCSprite* bg = CCSprite::create(getResPath(HSCORE_BG_IMG));
    bg->setScaleX(SCALEX);
    bg->setScaleY(SCALEY);
    bg->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    this->addChild(bg);

    // Add Letter Background
    CCSprite* letter_bg = CCSprite::create(getResPath(HSCORE_LETTER_BG_IMG));
    letter_bg->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5 + 20 * SCALEY));
    letter_bg->setScale(SCALE);
    this->addChild(letter_bg);
    
    // Add Character
    CCSprite* character = CCSprite::create(getResPath(HSCORE_CHARACTER_IMG));
    character->setScale(SCALE);
    character->setAnchorPoint(ccp(0, 0));
    character->setPosition(ccp(20 * SCALEX, 30 * SCALEY));
    this->addChild(character);
    
    // Add Coin Image
    CCSprite* spt_coin = CCSprite::create(getResPath(GAMERESULT_COIN_IMG));
    spt_coin->setScale(SCALE * 0.7);
    spt_coin->setPosition(ccp(500 * SCALEX, winSize.height - 45 * SCALEY));
    this->addChild(spt_coin);
    
    // Add coin count label
    char coin_str[10];
    int coins = (GameOptions::getInstance()->getCurrentScore() - GameOptions::getInstance()->getTargetScore(11)) / 10;
    if (coins < 0) {
        coins = 0;
    }
    int targetCoin = GameOptions::getInstance()->getCoins() + coins;
    GameOptions::getInstance()->setCoins(targetCoin);
    int current_coin = GameOptions::getInstance()->getCoins();
    sprintf(coin_str, "%d", current_coin);
    CCLabelTTF* lbl_coin = CCLabelTTF::create(coin_str, FONT_COMMON_STD, 40 * SCALE);
    lbl_coin->setHorizontalAlignment(kCCTextAlignmentRight);
    lbl_coin->setAnchorPoint(ccp(1, 0.5));
    lbl_coin->setPosition(ccp(winSize.width - 20 * SCALEX, winSize.height - 45 * SCALEY));
    this->addChild(lbl_coin);
    
    // Add title
    CCSprite* title_spt = CCSprite::create(getResPath(HSCORE_TITLE_TXT_IMG));
    title_spt->setScale(SCALE * 0.9);
    title_spt->setPosition(ccp(winSize.width * 0.5, 900 * SCALEY));
    this->addChild(title_spt);
    
    // Add HighScore Label
    CCLabelTTF* lbl_totalScore = CCLabelTTF::create("Total Score : ", FONT_COMMON_STD, 40 * SCALE);
    lbl_totalScore->setAnchorPoint(ccp(1, 0.5));
    lbl_totalScore->setPosition(ccp(420 * SCALEX, 776 * SCALEY));
    this->addChild(lbl_totalScore);
    
    char score[30];
    sprintf(score, "%d", highScore);
    CCLabelTTF* lbl_totalscore_value = CCLabelTTF::create(score, FONT_COMMON_STD, 40 * SCALE);
    lbl_totalscore_value->setAnchorPoint(ccp(0, 0.5));
    lbl_totalscore_value->setPosition(ccp(420 * SCALEX, lbl_totalScore->getPositionY()));
    this->addChild(lbl_totalscore_value);
    
    // Add Letters Label
    int letters = LetterBag::getInstance()->getLetterCountInBag();
    
    CCLabelTTF* lbl_lettercount = CCLabelTTF::create("Studied Letters : ", FONT_COMMON_STD, 40 * SCALE);
    lbl_lettercount->setAnchorPoint(ccp(1, 0.5));
    lbl_lettercount->setPosition(ccp(420 * SCALEX, 720 * SCALEY));
    this->addChild(lbl_lettercount);
    
    sprintf(score, "%d", letters);
    CCLabelTTF* lbl_letterscount_value = CCLabelTTF::create(score, FONT_COMMON_STD, 40 * SCALE);
    lbl_letterscount_value->setAnchorPoint(ccp(0, 0.5));
    lbl_letterscount_value->setPosition(ccp(420 * SCALEX, lbl_lettercount->getPositionY()));
    this->addChild(lbl_letterscount_value);
    
    int diff = GameOptions::getInstance()->getDifficulty();
    CCLabelTTF* lbl_difficualty = CCLabelTTF::create("Game Difficulty : ", FONT_COMMON_STD, 40 * SCALE);
    lbl_difficualty->setAnchorPoint(ccp(1, 0.5));
    lbl_difficualty->setPosition(ccp(420 * SCALEX, 670 * SCALEY));
    this->addChild(lbl_difficualty);
    if (diff == 0) {
        sprintf(score, "Normal");
    }else
    {
        sprintf(score, "Hard");
    }
    CCLabelTTF* lbl_difficulty_value = CCLabelTTF::create(score, FONT_COMMON_STD, 40 * SCALE);
    lbl_difficulty_value->setAnchorPoint(ccp(0, 0.5));
    lbl_difficulty_value->setPosition(ccp(420 * SCALEX, lbl_difficualty->getPositionY()));
    this->addChild(lbl_difficulty_value);
    
    // Add Mainmenu Button
    CCMenuItem* btn_sendMail = CCMenuItemImage::create(getResPath(HSCORE_BTN_SENDEMAIL_IMG_NOR), getResPath(HSCORE_BTN_SENDEMAIL_IMG_PRS), this, menu_selector(HighScoreScene::emailHandle));
    btn_sendMail->setPosition(ccp(420 * SCALEX, 336 * SCALEY));
    btn_sendMail->setScale(SCALE);
    
    CCMenuItem* btn_menu = CCMenuItemImage::create(getResPath(HSCORE_BTN_MAINMENU_IMG_NOR), getResPath(HSCORE_BTN_MAINMENU_IMG_PRS), this, menu_selector(HighScoreScene::mainmenuHandle));
    btn_menu->setScale(MIN(SCALEX, SCALEY));
    btn_menu->setPosition(ccp(420 * SCALE, 224 * SCALEY));
    
    CCMenu* menu = CCMenu::create(btn_menu,
                                  btn_sendMail,
                                  NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}

void HighScoreScene::mainmenuHandle(cocos2d::CCObject *sender)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0, MainMenuScene::scene()));
}

void HighScoreScene::emailHandle(cocos2d::CCObject *sender)
{
    CCRenderTexture* texture = CCRenderTexture::create((int)winSize.width, (int)winSize.height);
    texture->setPosition(ccp(winSize.width/2, winSize.height/2));
    texture->begin();
    CCDirector::sharedDirector()->getRunningScene()->visit();
    texture->end();
    string imagePath = CCFileUtils::sharedFileUtils()->getWritablePath().c_str();
    CCLog("%s", imagePath.c_str());
    
    bool result = texture->saveToFile("screenshot.png", kCCImageFormatPNG);
    if (result) {
        imagePath += "screenshot.png";
        CCLog("%s", imagePath.c_str());
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    SocialGame::sendemailWithScreenShot(imagePath.c_str(), EMAIL_TEXT_SOCRE);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
#endif
}