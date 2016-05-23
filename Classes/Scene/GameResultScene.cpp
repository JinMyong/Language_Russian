//
//  GameResultScene.cpp
//  AlephBet
//
//  Created by Fredric on 1/16/16.
//
//

#include "GameResultScene.hpp"
#include "MainMenuScene.hpp"
#include "Const.h"
#include "GameScene.hpp"
#include "LetterBag.hpp"
#include "SoundEffects.hpp"
#include "MissedLetterScene.hpp"
#include "Global.hpp"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    #include "SocialGame.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "platform/android/jni/JniHelper.h"
#endif


CCScene* GameResultScene::scene()
{
    CCScene* scene = CCScene::create();
    GameResultScene* layer = GameResultScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameResultScene::init()
{
    if (!CCLayer::create()) {
        return false;
    }
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    options = GameOptions::getInstance();
    
    int total_score = options->getTotoalScore() + current_score;
    current_level = options->getCurrentLevel();
    current_score = options->getCurrentScore();
    target_score = options->getTargetScore(current_level);
    current_coin = options->getCoins();
    temp_earn = 1;
    options->setTotalScore(total_score);
    
    createUI();
    return true;
}

void GameResultScene::createUI()
{
    
// Add Background Image
    CCSprite* bg = CCSprite::create(getResPath(GAMERESULT_BG_IMG));
    bg->setScaleX(SCALEX);
    bg->setScaleY(SCALEY);
    bg->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    this->addChild(bg);

// Add Text Background
    CCSprite* bg_txt = CCSprite::create(getResPath(GAMERESULT_BG_TXT_IMG));
    bg_txt->setScaleX(SCALEX);
    bg_txt->setScaleY(SCALEY);
    bg_txt->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5 + 20 * SCALEY));
    this->addChild(bg_txt);
    
// Add Coin Image
    CCSprite* spt_coin = CCSprite::create(getResPath(GAMERESULT_COIN_IMG));
    spt_coin->setScale(SCALE * 0.7);
    spt_coin->setPosition(ccp(500 * SCALEX, winSize.height - 45 * SCALEY));
    this->addChild(spt_coin);
    
// Add coin count label
    char coin_str[10];
    sprintf(coin_str, "%d", current_coin);
    CCLabelTTF* lbl_coin = CCLabelTTF::create(coin_str, FONT_COMMON_STD, 40 * SCALE);
    lbl_coin->setHorizontalAlignment(kCCTextAlignmentRight);
    lbl_coin->setAnchorPoint(ccp(1, 0.5));
    lbl_coin->setPosition(ccp(winSize.width - 20 * SCALEX, winSize.height - 45 * SCALEY));
    lbl_coin->setTag(TAG_COIN);
    this->addChild(lbl_coin);
    
// Add Character Image
    CCSprite* character_spt = CCSprite::create(getResPath(GAMERESULT_CHARACTER_BOY_IMG));
    character_spt->setScale(MIN(SCALEX, SCALEY));
    character_spt->setAnchorPoint(ccp(0, 0));
    character_spt->setPosition(ccp(10 * SCALEX, 50 * SCALEY));
    this->addChild(character_spt);
    
    showGameInfo();
    showButtons();
    
    bool playcomplete = CCUserDefault::sharedUserDefault()->getBoolForKey(KEY_PLAY_COMPLETE, true);
    CCUserDefault::sharedUserDefault()->setBoolForKey(KEY_PLAY_COMPLETE, true);
    if (playcomplete) {
        SimpleAudioEngine::sharedEngine()->stopAllEffects();
        SoundEffects::getInstance()->playLevelComplete(current_score >= target_score);
        getCoins();
    }
}

void GameResultScene::showGameInfo()
{
// Add Game Result Title
    CCString* title;
    if (current_score >= target_score) {
        title = CCString::createWithFormat("Level %d Success", current_level + 1);
    }else
    {
        title = CCString::createWithFormat("Level %d Failed", current_level + 1);
    }
    CCLabelTTF* lbl_title = CCLabelTTF::create(title->getCString(), FONT_COMMON_STD, 60 * SCALEX);
    lbl_title->setPosition(ccp(winSize.width * 0.5, 1000 * SCALEY));
    this->addChild(lbl_title);
    
// Show Target Score Level
    char target_value_str[20];
    sprintf(target_value_str, "%d", target_score);
    
    CCLabelTTF* lbl_target_text = CCLabelTTF::create("Target Score : ", FONT_COMMON_STD, GAME_RESULT_FNTSIZE * SCALE);
    lbl_target_text->setPosition(ccp(420 * SCALEX, 900 * SCALEY));
    lbl_target_text->setAnchorPoint(ccp(1, 0.5));
    this->addChild(lbl_target_text);
    
    CCLabelTTF* lbl_target_score = CCLabelTTF::create(target_value_str, FONT_COMMON_STD, GAME_RESULT_FNTSIZE * SCALE);
    lbl_target_score->setAnchorPoint(ccp(0, 0.5));
    lbl_target_score->setPosition(ccp(420 * SCALEX, lbl_target_text->getPositionY()));
    this->addChild(lbl_target_score);
    
// Show Current Score
    char current_value_str[20];
    sprintf(current_value_str, "%d", current_score);
    CCLabelTTF* lbl_Current = CCLabelTTF::create("Your Score : ", FONT_COMMON_STD, GAME_RESULT_FNTSIZE * SCALE);
    lbl_Current->setAnchorPoint(ccp(1, 0.5));
    lbl_Current->setPosition(ccp(420 * SCALEX, 850 * SCALEY));
    this->addChild(lbl_Current);
    
    CCLabelTTF* lbl_current_score = CCLabelTTF::create(current_value_str, FONT_COMMON_STD, GAME_RESULT_FNTSIZE * SCALE);
    lbl_current_score->setAnchorPoint(ccp(0, 0.5));
    lbl_current_score->setPosition(ccp(420 * SCALEX, lbl_Current->getPositionY()));
    this->addChild(lbl_current_score);
    
// Show Studied Letters Counts
    char temp_value[30];
    int letters = LetterBag::getInstance()->getLetterCountInBag();
    CCLabelTTF* lbl_lettercount = CCLabelTTF::create("Studied Letters : ", FONT_COMMON_STD, 40 * SCALE);
    lbl_lettercount->setAnchorPoint(ccp(1, 0.5));
    lbl_lettercount->setPosition(ccp(420 * SCALEX, 770 * SCALEY));
    this->addChild(lbl_lettercount);
    
    sprintf(temp_value, "%d", letters);
    CCLabelTTF* lbl_letterscount_value = CCLabelTTF::create(temp_value, FONT_COMMON_STD, 40 * SCALE);
    lbl_letterscount_value->setAnchorPoint(ccp(0, 0.5));
    lbl_letterscount_value->setPosition(ccp(420 * SCALEX, lbl_lettercount->getPositionY()));
    this->addChild(lbl_letterscount_value);
    
// Show Game difficulty
    int diff = GameOptions::getInstance()->getDifficulty();
    CCLabelTTF* lbl_difficualty = CCLabelTTF::create("Game Difficulty : ", FONT_COMMON_STD, 40 * SCALE);
    lbl_difficualty->setAnchorPoint(ccp(1, 0.5));
    lbl_difficualty->setPosition(ccp(420 * SCALEX, 720 * SCALEY));
    this->addChild(lbl_difficualty);
    if (diff == 0) {
        sprintf(temp_value, "Normal");
    }else
    {
        sprintf(temp_value, "Hard");
    }
    CCLabelTTF* lbl_difficulty_value = CCLabelTTF::create(temp_value, FONT_COMMON_STD, 40 * SCALE);
    lbl_difficulty_value->setAnchorPoint(ccp(0, 0.5));
    lbl_difficulty_value->setPosition(ccp(420 * SCALEX, lbl_difficualty->getPositionY()));
    this->addChild(lbl_difficulty_value);
    
// Show Earned Coins
    CCLabelTTF* lbl_earnedCoins = CCLabelTTF::create("Coins Earned : ", FONT_COMMON_STD, 40 * SCALE);
    lbl_earnedCoins->setAnchorPoint(ccp(1.0, 0.5));
    lbl_earnedCoins->setPosition(ccp(420 * SCALEX, 670 * SCALEY));
    this->addChild(lbl_earnedCoins);
    
    int coins = (current_score - target_score) / 10;
    if (coins < 0) {
        coins = 0;
    }
    sprintf(temp_value, "%d", coins);
    CCLabelTTF* lbl_coins_count = CCLabelTTF::create("0", FONT_COMMON_STD, 40 * SCALE);
    lbl_coins_count->setAnchorPoint(ccp(0, 0.5));
    lbl_coins_count->setPosition(ccp(420 * SCALEX, lbl_earnedCoins->getPositionY()));
    lbl_coins_count->setTag(TAG_EARNCOIN);
    this->addChild(lbl_coins_count);

// Show Shoot Item
    CCLabelTTF* lbl_shootitem = CCLabelTTF::create("Throwing Item", FONT_COMMON_STD, 40 * SCALE);
    lbl_shootitem->setAnchorPoint(ccp(1.0, 0.5));
    lbl_shootitem->setPosition(ccp(420 * SCALEX, 600 * SCALEY));
    this->addChild(lbl_shootitem);
    
    int item_no = options->getItem();
    CCSprite* item_image;
    switch (item_no) {
        case item_Pencil:
            item_image = CCSprite::create(getResPath(STORE_TABLE_PENCIL_OFF));
            break;
        case item_Fish:
            item_image = CCSprite::create(getResPath(STORE_TABLE_FISH_OFF));
            break;
        case item_Balloon:
            item_image = CCSprite::create(getResPath(STORE_TABLE_BALLOON_OFF));
            break;
        case item_LightBulb:
            item_image = CCSprite::create(getResPath(STORE_TABLE_BULB_OFF));
            break;
        case item_Egg:
            item_image = CCSprite::create(getResPath(STORE_TABLE_EGG_OFF));
            break;
        case item_Airplane:
            item_image = CCSprite::create(getResPath(STORE_TABLE_AIRPLANE_OFF));
            break;
        default:
            break;
    }
    item_image->setScale(SCALE);
    item_image->setPosition(ccp(500 * SCALEX, lbl_shootitem->getPositionY()));
    this->addChild(item_image);
    
}

void GameResultScene::showButtons()
{
// Add Mainmeun Button
    CCMenuItem* mainMenu = CCMenuItemImage::create(getResPath(GAMERESULT_BTN_MAINMENU_NOR), getResPath(GAMERESULT_BTN_MAINMENU_PRS), this, menu_selector(GameResultScene::mainMenuHandler));
    mainMenu->setScale(SCALE);
    mainMenu->setPosition(ccp(420 * SCALEX, 200 * SCALEY));
    
// Add Play Button
    CCMenuItem* btn_next;
    if (current_score >= target_score && current_level < MAX_LEVEL) {
        // Add the Continue Button if current score >= target socre of level
        btn_next = CCMenuItemImage::create(getResPath(GAMERESULT_BTN_CONTINUE_NOR), getResPath(GAMERESULT_BTN_CONTINUE_PRS), this, menu_selector(GameResultScene::gotoNextScene));
    }
    if (current_score < target_score && current_level <= MAX_LEVEL)
    {
        // Add the Restart Button if current score < target socre of level
        btn_next = CCMenuItemImage::create(getResPath(GAMERESULT_BTN_RESTART_NOR), getResPath(GAMERESULT_BTN_RESTART_PRS), this, menu_selector(GameResultScene::gotoNextScene));
    }
    
// Add Mainmenu Button
    CCMenuItem* btn_sendMail = CCMenuItemImage::create(getResPath(GAMERESULT_BTN_SENDEMAIL_IMG_NOR), getResPath(GAMERESULT_BTN_SENDEMAIL_IMG_PRS), this, menu_selector(GameResultScene::emailHandle));
    btn_sendMail->setPosition(ccp(420 * SCALEX, 300 * SCALEY));
    btn_sendMail->setScale(SCALE);
    
// Add Missed Letters Button
    CCMenuItemImage* btn_missed = CCMenuItemImage::create(getResPath(GAMERESULT_BTN_MISEED_IMG_NOR), getResPath(GAMERESULT_BTN_MISEED_IMG_PRS), this, menu_selector(GameResultScene::gotoMissedLetterScene));
    btn_missed->setScale(SCALE);
    btn_missed->setPosition(ccp(420 * SCALEX, 400 * SCALEY));
    
    int missCount = LetterBag::getInstance()->getMissedLetters()->count();
    
    CCMenu* menu;
    if (btn_next != NULL) {
        btn_next->setScale(SCALE);
        if (missCount == 0) {
            btn_next->setPosition(ccp(420 * SCALEX, 400 * SCALEY));
            menu = CCMenu::create(mainMenu, btn_sendMail, btn_next, NULL);
        }else
        {
            btn_next->setPosition(ccp(420 * SCALEX, 500 * SCALEY));
            menu = CCMenu::create(mainMenu, btn_sendMail, btn_next, btn_missed, NULL);
        }
    }
    
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}

void GameResultScene::mainMenuHandler(cocos2d::CCObject *sender)
{
    SoundEffects::getInstance()->playButtonEffect();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, MainMenuScene::scene()));
}

void GameResultScene::gotoNextScene(cocos2d::CCObject *sender)
{
    SoundEffects::getInstance()->playButtonEffect();
    int current_level = options->getCurrentLevel();
    int current_score = options->getCurrentScore();
    int target_score = options->getTargetScore(current_level);
    
    if (current_score >= target_score) {
        current_level++;
    }
    if (current_level > MAX_LEVEL) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, MainMenuScene::scene()));
    }else
    {
        options->setCurrentLevel(current_level);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, GameScene::scene()));
    }
    
}

void GameResultScene::getCoins()
{
    int current_level = options->getCurrentLevel();
    int current_score = options->getCurrentScore();
    int target_score = options->getTargetScore(current_level);
    
    if (current_score < target_score) {
        return;
    }
    
    int coins = (current_score - target_score) / 10;
    temp_coin = options->getCoins();
    targetCoin = temp_coin + coins;
    options->setCoins(targetCoin);
    CCArray* action_array = CCArray::create();
    action_array->addObject(CCDelayTime::create(0.5));
    for (int index = 0; index < coins; index++) {
        CCCallFunc* update_earnedcoinLabel = CCCallFunc::create(this, callfunc_selector(GameResultScene::updateCoinLabel));
        action_array->addObject(CCDelayTime::create(0.2));
        action_array->addObject(update_earnedcoinLabel);
    }
    action_array->addObject(CCDelayTime::create(0.2));
    for (int index = 0; index < coins; index++) {
        CCCallFunc* move_func = CCCallFunc::create(this, callfunc_selector(GameResultScene::moveCoin));
        CCCallFunc* inc_func = CCCallFunc::create(this, callfunc_selector(GameResultScene::incCoinCount));
        action_array->addObject(CCDelayTime::create(0.5));
        action_array->addObject(move_func);
        action_array->addObject(inc_func);
    }
    CCSequence* coin_seq = CCSequence::create(action_array);
    this->runAction(coin_seq);
}

void GameResultScene::updateCoinLabel()
{
    char newValue[5];
    sprintf(newValue, "%d", temp_earn++);
    ((CCLabelTTF*)this->getChildByTag(TAG_EARNCOIN))->setString(newValue);
}

void GameResultScene::emailHandle(cocos2d::CCObject *sender)
{
    SoundEffects::getInstance()->playButtonEffect();
    CCRenderTexture* texture = CCRenderTexture::create((int)winSize.width, (int)winSize.height);
    texture->setPosition(ccp(winSize.width/2, winSize.height/2));
    texture->begin();
    CCDirector::sharedDirector()->getRunningScene()->visit();
    texture->end();
    string imagePath = CCFileUtils::sharedFileUtils()->getWritablePath().c_str();

    bool result = texture->saveToFile("screenshot.png", kCCImageFormatPNG);
    if (result) {
        imagePath += "screenshot.png";
        CCLog("%s", imagePath.c_str());
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    SocialGame::sendemailWithScreenShot(imagePath.c_str(), EMAIL_TEXT_SOCRE);
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

void GameResultScene::moveCoin()
{
    CCSprite* act_coin = CCSprite::create(getResPath(GAMERESULT_COIN_IMG));
    act_coin->setScale(SCALE * 0.7);
    act_coin->setPosition(ccp(420 * SCALEX, 670 * SCALEY));
    act_coin->setTag(TAG_ACTCOIN);
    this->addChild(act_coin);
    ccBezierConfig bezier;
    bezier.endPosition = ccp(500 * SCALEX, winSize.height - 45 * SCALEY);
    bezier.controlPoint_1 = ccp(640 * SCALEX, 900 * SCALEY);
    bezier.controlPoint_2 = ccp(690 * SCALEX, 1000 * SCALEY);
//    act_coin->runAction(CCMoveTo::create(0.2, ccp(500 * SCALEX, winSize.height - 45 * SCALEY)));
    act_coin->runAction(CCBezierTo::create(0.5, bezier));
}

void GameResultScene::incCoinCount()
{
    SoundEffects::getInstance()->playGetCoin();
//    this->removeChildByTag(TAG_ACTCOIN, true);
    char newValue[5];
//    temp_coin++;
    sprintf(newValue, "%d", ++temp_coin);
    ((CCLabelTTF*)this->getChildByTag(TAG_COIN))->setString(newValue);
}

void GameResultScene::gotoMissedLetterScene(cocos2d::CCObject *sender)
{
    SoundEffects::getInstance()->playButtonEffect();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, MissedLetterScene::scene()));
}

