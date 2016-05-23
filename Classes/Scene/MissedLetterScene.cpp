//
//  MissedLetterScene.cpp
//  AlephBet
//
//  Created by Fredric on 2/11/16.
//
//

#include "MissedLetterScene.hpp"
#include "AlphaBetUtils.hpp"
#include "LetterBag.hpp"
#include "Global.hpp"
#include "GameResultScene.hpp"
#include "MainMenuScene.hpp"
#include "Const.h"
#include "SoundEffects.hpp"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    #include "SocialGame.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "platform/android/jni/JniHelper.h"
#endif


CCScene* MissedLetterScene::scene()
{
    CCScene* scene = CCScene::create();
    MissedLetterScene* layer = MissedLetterScene::create();
    scene->addChild(layer);
    return scene;
}

bool MissedLetterScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    createUI();
    return true;
}

void MissedLetterScene::createUI()
{
    // Add background
    CCSprite* background = CCSprite::create(getResPath(CHOOSE_LETTERSCENE_BACKROUND_IMG));
    background->setScaleX(SCALEX);
    background->setScaleY(SCALEY);
    background->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    this->addChild(background);
    
    // Add letterboard background image
    CCSprite* letterboard_bg = CCSprite::create(getResPath(CHOOSE_LETTERBOARD_BG_IMG));
    letterboard_bg->setScaleX(SCALEX);
    letterboard_bg->setScaleY(SCALEY);
    letterboard_bg->setPosition(ccp(winSize.width * 0.5, 592 * SCALEY));
    this->addChild(letterboard_bg);
    
    // Add title
    CCLabelTTF* title = CCLabelTTF::create("Missed Letters", FONT_COMMON_STD, 50 * SCALE);
    title->setPosition(ccp(winSize.width * 0.5, winSize.height - 45 * SCALEY));
    this->addChild(title);
    
    showLetters();
    
    // Add Back Button
    CCMenuItem* btn_back = CCMenuItemImage::create(getResPath(MISSEDLETTER_BTN_BACK_NOR), getResPath( MISSEDLETTER_BTN_BACK_PRS), this, menu_selector(MissedLetterScene::backHandle));
    btn_back->setScale(SCALE);
    btn_back->setPosition(ccp(winSize.width * 0.5, 350 * SCALEY));
    
    // Add email to teacher Button
    CCMenuItemImage* btn_email = CCMenuItemImage::create(getResPath(GAMERESULT_BTN_SENDEMAIL_IMG_NOR), getResPath(GAMERESULT_BTN_SENDEMAIL_IMG_PRS), this, menu_selector(MissedLetterScene::emailHandle));
    btn_email->setScale(SCALE);
    btn_email->setPosition(ccp(winSize.width * 0.5, 250 * SCALEY));
    
    // Add MainMenu Button
    CCMenuItemImage* btn_mainmenu = CCMenuItemImage::create(getResPath(MISSEDLETTER_BTN_MENU_NOR), getResPath(MISSEDLETTER_BTN_MENU_PRS), this, menu_selector(MissedLetterScene::mainMenuHandle));
    btn_mainmenu->setScale(SCALE);
    btn_mainmenu->setPosition(ccp(winSize.width * 0.5, 150 * SCALEY));
    
    CCMenu* menu = CCMenu::create(btn_back, btn_email, btn_mainmenu, NULL);
//    menu->alignItemsVerticallyWithPadding(20 * SCALEY);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}

void MissedLetterScene::showLetters()
{
    AlphaBetUtils* AlphaBetUtils = AlphaBetUtils::getInstance();
    LetterBag* letterbag = LetterBag::getInstance();
    
    CCArray* missedArray = letterbag->getMissedLetters();
    int lettersCounts = missedArray->count();
    if (lettersCounts <= 0) {
        return;
    }
    
    int fontSize = 60 * SCALE;
    
    CCLog("Scale is %f", SCALE);
    
    // Make 6 wide by 7 high grid
    
    int yIndex = -1;    // start with -1. It will get increment the first pass through
    int xIndex = 0;
    
    float factor = 1.0;     // For letter row space
    
    string fontName;
    bool fontType = GameOptions::getInstance()->getFontType();
    if (fontType) {
        fontName = FONT_LETTER_NOR;
        factor = 1.2;
    }else
    {
        fontName = FONT_LETTER_CUR;
        factor = 1.5;
    }
    
    for (int index = 0; index < lettersCounts; index++) {
        if (xIndex % NUM_COLUMNS == 0) {
            yIndex++;
            xIndex = 0;
        }
        int missedLetterIndex = ((CCInteger*)missedArray->objectAtIndex(index))->getValue();
        string letterString = AlphaBetUtils->getKeyMapFont(missedLetterIndex);
        
        CCLabelTTF* letterSprite = CCLabelTTF::create(letterString.c_str(), fontName.c_str(), fontSize);
        letterSprite->setColor(ccRED);
        letterSprite->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
        letterSprite->setHorizontalAlignment(kCCTextAlignmentCenter);
        letterSprite->setDimensions(CCSize(fontSize * 1.1, fontSize * 1.5));
        
        CCSize targetSize = letterSprite->getContentSize();
        targetSize.height *= 0.75;
        
        int colSpace = (winSize.width - (2 * LETTER_BOARD_OFFSET_X * MIN(SCALEX, SCALEY))) / (NUM_COLUMNS);
        int xPos = winSize.width - LETTER_BOARD_OFFSET_X  * MIN(SCALEX, SCALEY) - (xIndex * colSpace) - (colSpace * 0.5);
        int yPos = winSize.height - LETTER_BOARD_OFFSET_Y * MIN(SCALEX, SCALEY) - (yIndex * targetSize.height * factor) - (targetSize.height * 0.5) - (94 * MIN(SCALEX, SCALEY));
     
        
        letterSprite->setPosition(ccp(xPos, yPos));
        this->addChild(letterSprite, 2, index);
        xIndex++;
    }
}

void MissedLetterScene::backHandle(cocos2d::CCObject *sender)
{
    CCUserDefault::sharedUserDefault()->setBoolForKey(KEY_PLAY_COMPLETE, false);
    SoundEffects::getInstance()->playButtonEffect();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, GameResultScene::scene()));
}

void MissedLetterScene::mainMenuHandle(cocos2d::CCObject *sender)
{
    SoundEffects::getInstance()->playButtonEffect();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, MainMenuScene::scene()));
}

void MissedLetterScene::emailHandle(cocos2d::CCObject *sender)
{
    SoundEffects::getInstance()->playButtonEffect();
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
    SocialGame::sendemailWithScreenShot(imagePath.c_str(), EMAIL_TEXT_MISSED);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t
                                       , "com/bullseye/alifbatabullseye/AlifBaTaBullseye"
                                       , "sendemailWithScreenShot"
                                       , "(Ljava/lang/String;Ljava/lang/String;)V"))
    {
        jstring stringFile = t.env->NewStringUTF(imagePath.c_str());
        jstring stringBody = t.env->NewStringUTF(EMAIL_TEXT_SOCRE);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, stringFile, stringBody);
    }
#endif
}