//
//  GameScene.cpp
//  AlephBet
//
//  Created by Fredric on 12/25/15.
//
//

#include "GameScene.hpp"
#include "Const.h"

#include "MainMenuScene.hpp"
#include "LetterBag.hpp"
#include "AlphaBetUtils.hpp"
#include "SoundEffects.hpp"
#include "GameResultScene.hpp"
#include "Global.hpp"
#include "HighScoreScene.hpp"


enum
{
    TAG_LAYER_ANNOUNCE = 0,
    TAG_LAYER_MENU,
    TAG_LAYER_TARGET,
    TAG_LAYER_CLOCK,
    TAG_LAYER_BACKGROUND,
    TAG_LEVELNUMBER,
    
    NUM_TAG_LAYERS
};

CCScene* GameScene::scene()
{
    CCScene* scene = CCScene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    options = GameOptions::getInstance();
    
    initVariables();
    createUI();
    
    SoundEffects::getInstance()->playLevelBackgroundMusic();
    
    startScene();
    return true;
}

void GameScene::initVariables()
{
    
    //Init current game score
    gameScore = 0;
    
    isPause = true;
    
    // Init TargetCount
    int level = options->getCurrentLevel();
    
    switch (level) {
        case 1:
        case 2:
            targetCount = 3;
            break;
        case 3:
        case 4:
            targetCount = 4;
            break;
        case 5:
        case 6:
            targetCount = 5;
            break;
        case 7:
        case 8:
            targetCount = 6;
            break;
        case 9:
        case 10:
            targetCount = 7;
            break;
        case 11:
        case 12:
            targetCount = 8;
            break;
        default:
            targetCount = 3;
            break;
    }
}

void GameScene::createUI()
{
    // Add Background Image
    CCSprite* background = CCSprite::create(getResPath(GAMESCENE_BACKROUND_IMG));
    background->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    background->setScaleX(SCALEX);
    background->setScaleY(SCALEY);
    this->addChild(background, -100, TAG_LAYER_BACKGROUND);
    
    createMenu();
    
    targetLayer = TargetLayer::create();
    announceLayer = AnnounceLayer::create();
    clockLayer = ClockLayer::create();
    characterLayer = CharacterLayer::create();
    
    // Clock
    int level = options->getCurrentLevel();
    int time_second = options->getTime(level);
    int min = time_second / 60;
    int sec = time_second % 60;
    clockLayer->setTimer(min, sec);
//------------------------------------------------------------------------//
//    clockLayer->setTimer(0, 12);         // For Test
//------------------------------------------------------------------------//
    this->addChild(targetLayer, TARGET_Z, TAG_LAYER_TARGET);
    this->addChild(announceLayer, ANNOUNCE_Z, TAG_LAYER_ANNOUNCE);
    this->addChild(clockLayer, CLOCK_Z, TAG_LAYER_CLOCK);
    this->addChild(characterLayer, CHARACTER_Z);
    
    // Show the Score
    CCLabelTTF* lbl_score = CCLabelTTF::create("SCORE:", FONT_COMMON_STD, GAME_INFO_FONT_SIZE * SCALE);
    lbl_score->setAnchorPoint(ccp(1, 0.5));
    lbl_score->setPosition(ccp(winSize.width - 100 * SCALEX, winSize.height - 45 * SCALEY));
    this->addChild(lbl_score);
    
    CCLabelTTF* lbl_scoreValue = CCLabelTTF::create("", FONT_COMMON_STD, GAME_INFO_FONT_SIZE * SCALE);
    lbl_scoreValue->setAnchorPoint(ccp(0, 0.5));
    lbl_scoreValue->setPosition(ccp(lbl_score->getPositionX() , winSize.height - 45 * SCALEY));
    lbl_scoreValue->setTag(TAG_LEVELNUMBER);
    this->addChild(lbl_scoreValue);
    
    // Show Level
    char lbl_levelString[20];
    sprintf(lbl_levelString, "Level %d", options->getCurrentLevel() + 1);
    CCLabelTTF* lbl_level = CCLabelTTF::create(lbl_levelString, FONT_COMMON_STD, 45 * SCALE);
    lbl_level->setPosition(ccp(winSize.width * 0.5 - 50 * SCALEX, winSize.height - 45 * SCALEY));
    this->addChild(lbl_level);
}

void GameScene::startScene()
{
    lastWasHit = true;
    if (options->getDifficulty() == 0) {
        this->changeGameState(GAME_COUNTDOWN);
    }else
    {
        this->changeGameState(GAME_SHOWHINT);
    }
    this->updateCurrentScore(gameScore);    
}

void GameScene::updateCurrentScore(int value)
{
    char score_str[10];
    sprintf(score_str, "%d", value);
    CCLabelTTF* levelNumber = (CCLabelTTF*)this->getChildByTag(TAG_LEVELNUMBER);
    levelNumber->setString(score_str);
}

void GameScene::createMenu()
{
    CCMenuItem* quitItem = CCMenuItemImage::create(getResPath(GAME_BTN_QUIT_IMAGE_NOR), getResPath(GAME_BTN_QUIT_IMAGE_PRS), this, menu_selector(GameScene::quitHandler));
    quitItem->setScale(SCALE);
    quitItem->setPosition(ccp(180 * SCALEX, 45 * SCALEY));
    
    CCMenuItemImage* pauseItem = CCMenuItemImage::create(getResPath(GAME_BTN_PAUSE_IMAGE_NOR), getResPath(GAME_BTN_PAUSE_IMAGE_PRS));
    CCMenuItemImage* countinue_item = CCMenuItemImage::create(getResPath(GAME_BTN_CONTINUE_IMAGE_NOR), getResPath(GAME_BTN_CONTINUE_IMAGE_PRS));
    CCMenuItemToggle* btn_pause = CCMenuItemToggle::createWithTarget(this, menu_selector(GameScene::pauseHandler), pauseItem, countinue_item, NULL);
    btn_pause->setScale(SCALE);
    btn_pause->setPosition(ccp(462 * SCALEX, 45 * SCALEY));
    
    CCMenu* menu = CCMenu::create(quitItem, btn_pause, NULL);
    menu->setPosition(ccp(0, 0));
    
    this->addChild(menu);
}

void GameScene::startNewLetter()
{
    // Remove any old target layer
    targetLayer->removeArrowSprite();
    
    // If the last letter was a hit, get a new one. Otherwise repeat.
    int targetLetter;
//    if (lastWasHit) {
        // Pick the new target letter
        targetLetter = LetterBag::getInstance()->getRandomLetterFormBagLimitRepeats();
        
        // Store the target letter for later
        lastTargetLetter = targetLetter;
//    }else
//    {
//        targetLetter = lastTargetLetter;
//    }
    
    CCInteger* targetLetterObj = CCInteger::create(targetLetter);
    
    CCLog("Target letter index: %d", targetLetter);
    
    // Get the "miss" target letters
    CCArray* otherLetters = LetterBag::getInstance()->getRandomLettersFromAlephBet(targetCount - 1, targetLetter);
    otherLetters->addObject(targetLetterObj);
    
    // Randomize the last letter
    randomizeLastElement(otherLetters);
    
    // Announce the letter
    announceLayer->announceLetter(targetLetter);
    SoundEffects::getInstance()->playLetterSound(targetLetter);
    
    // Make new targets
    targetLayer->makeTargets(targetCount, otherLetters);
    
}

void GameScene::randomizeLastElement(cocos2d::CCArray *array)
{
    int numLetters = array->count();
    
    // Get a random index into the array
    int index = random() % numLetters;
    
    // Swap the last object with a randome one
    array->exchangeObjectAtIndex(numLetters - 1, index);
}

void GameScene::quitHandler(cocos2d::CCNode *sender)
{
    CCLog("GameScene:: Quit");
    CCDirector::sharedDirector()->resume();
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    SoundEffects::getInstance()->playButtonEffect();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, MainMenuScene::scene()));
}

void GameScene::pauseHandler(cocos2d::CCNode *sender)
{
    CCLog("GameScene:: Pause");
    if (isPause) {
        clockLayer->stopTimer();
        SoundEffects::getInstance()->pauseEffects();
        targetLayer->disableTouches();
        CCDirector::sharedDirector()->pause();
    }else
    {
        clockLayer->startTimer();
        SoundEffects::getInstance()->resumeEffects();
        targetLayer->enableTouches();
        CCDirector::sharedDirector()->resume();
    }
    isPause = !isPause;
    SoundEffects::getInstance()->playButtonEffect();
}


void GameScene::changeGameState(GameState newGameState)
{
    gameState = newGameState;
    
    switch (newGameState) {
        case GAME_IDLE:
            // Do nothing: not really a state
            break;
        case GAME_COUNTDOWN:
            this->doCountdown();
            break;
        case GAME_START_GAME:
            this->startGameAction();
            break;
        case GAME_ANNOUNCE_LETTER:
            this->doStateAnnounceLetter();
            break;
        case GAME_SHOOTING:
            // Do nothing
//            hero_boy->shoot();
            break;
        case GAME_HIT:
            this->doStateHit(true);
            break;
        case GAME_MISS:
            this->doStateHit(false);
            break;
        case GAME_END_ANNOUNCE_HIT:
            this->doEndAnnounceHit(true);
            break;
        case GAME_END_ANNOUNCE_MISS:
            this->doEndAnnounceHit(false);
            break;
        case GAME_ANNOUNCE_LEVEL:
            this->doStateAnnounceLevel();
            break;
        case GAME_END_ANNOUNCE_LEVEL:
            this->doStateEndAnnounceLevel();
            break;
        case GAME_END_GAME:
            this->doGameEnd();
            break;
        case GAME_EXIT:
            this->exitScene();
            break;
        case GAME_SHOWING:
//            clockLayer->stopTimer();// Stop Clock when letters are showing
            this->startDiffcultGame();
            break;
        case GAME_HIDE:
            clockLayer->startTimer(); // Resume Clock when letters are hiding
            break;
        case GAME_SHOWHINT:
            this->showHints();
            break;
        default:
            break;
    }
}

void GameScene::doCountdown()
{
    // Start the countdown
    announceLayer->startCountDown();
}

void GameScene::showHints()
{
    // Show Start Difficult Hint
    announceLayer->startShowHints();
}

void GameScene::startGameAction()
{
    int isDifficult = options->getDifficulty();
    if (isDifficult == 0) {
        // mode is easy mode
        this->changeGameState(GAME_ANNOUNCE_LETTER);
    }else
    {   // mode is difficult mode
        this->changeGameState(GAME_SHOWING);
    }
}

void GameScene::doStateAnnounceLetter()
{
    // Show initial stats
    // this->updateStats();
    
    this->startNewLetter();
    
    // Start the timer
    clockLayer->stopTimer();
    clockLayer->startTimer();
}

void GameScene::startDiffcultGame()
{
    this->startNewLetter();    
    CCCallFunc* func = CCCallFunc::create(this, callfunc_selector(GameScene::changeStateToHide));
    CCSequence* seq = CCSequence::create(CCDelayTime::create(2.0), func, NULL);
    this->runAction(seq);
}

void GameScene::doStateHit(bool goodhit)
{
    // Tell the scene about the miss
    this->shotResult(goodhit);
}

void GameScene::doEndAnnounceHit(bool goodhit)
{
    // Check if we announce new level
    int isDifficult = options->getDifficulty();
    if (isDifficult == 0) {
        this->changeGameState(GAME_ANNOUNCE_LETTER);
    }else
    {
        this->changeGameState(GAME_SHOWING);
    }
}

void GameScene::doStateAnnounceLevel()
{
    
}

void GameScene::doStateEndAnnounceLevel()
{
    
}

void GameScene::doGameEnd()
{    
    CCLOG("Game Ended");
    CCLOG("Current Score is %d", gameScore);
    
    options->setCurrentScore(gameScore);

    CCCallFunc* gotoNext = CCCallFunc::create(this, callfunc_selector(GameScene::gotoNextScene));
    CCSequence* seq = CCSequence::create(CCDelayTime::create(2.5), gotoNext, NULL);
    this->runAction(seq);
}

void GameScene::exitScene()
{
    
}

void GameScene::changeStateToHide()
{
    targetLayer->hideLetters();
    this->changeGameState(GAME_HIDE);
}

void GameScene::timerUpdate(int newMinutes, int newSeconds)
{
    if (newMinutes == 0 && newSeconds == 0) {
        if (gameState != GAME_END_GAME && gameState != GAME_EXIT) {
            this->changeGameState(GAME_END_GAME);
        }
    }
}

void GameScene::shotResult(bool hit)
{
    // Score the shot
    
    // Play the hit or miss sound
    if (hit) {
        // Sound Effect SOUND_EFFECT_HIT
        
        gameScore += SUCCESS_SCORE;
        
    }else
    {
        // Sound Effect SOUND_EFFECT_MISS
        
        gameScore -= MISS_SCORE;
    }
    
    // Update the Current Game Score
    updateCurrentScore(gameScore);
    
    // Announce the hit/miss then start a new letter
    announceLayer->announceHit(hit);
    
    // Track the last hit
    lastWasHit = hit;
}

void GameScene::doShoot(int aimedLetter, CCPoint dest)
{
    bool wasgoodHit = false;
    string selectedLetter = AlphaBetUtils::getInstance()->getLetterName(aimedLetter - TAG_TARGET);
    string rightLetter = AlphaBetUtils::getInstance()->getLetterName(lastTargetLetter);
    if (selectedLetter.compare(rightLetter) == 0) {
        wasgoodHit = true;
    }else
    {
        LetterBag::getInstance()->addMissedLetter(lastTargetLetter);
    }
    CCLog("Result is %s", wasgoodHit?"true":"false");
    characterLayer->shoot(dest, wasgoodHit);
}

void GameScene::gotoNextScene()
{
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    int currentLevel = options->getCurrentLevel();
    int currentScore = options->getCurrentScore();
    int targetScore = options->getTargetScore(currentLevel);
    if (currentLevel == 11 && (currentScore >= targetScore)) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, HighScoreScene::scene()));
    }else
    {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, GameResultScene::scene()));
    }
}