//
//  AnnounceLayer.cpp
//  AlephBet
//
//  Created by Fredric on 12/28/15.
//
//

#include "AnnounceLayer.hpp"
#include "AlphaBetUtils.hpp"
#include "GameScene.hpp"
#include "Const.h"
#include "Global.hpp"

bool AnnounceLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    
    return true;
}

void AnnounceLayer::startCountDown()
{
    countdown = 3;
    this->doNextCountDown();
}

void stringToUpper(string &s)
{
    for(unsigned int l = 0; l < s.length(); l++)
    {
        s[l] = toupper(s[l]);
    }
}

void AnnounceLayer::doNextCountDown()
{
    // Remove the old label, if any
    if (countLabel != NULL) {
        countLabel->removeFromParentAndCleanup(true);
        countLabel = NULL;
    }
#if 0
    // Do countdown in Hebrew : Gimmel-Bet-Alef
    string countString;
    switch (countdown) {
        case 3:
            countString = "g";
            break;
        case 2:
            countString = "b";
            break;
        case 1:
            countString = "a";
            break;
        default:
            break;
    }
    
    // Create and initalize a label
    countLabel = CCLabelTTF::create(countString.c_str(), FONT_LETTER_NOR, 256 * SCALE);
#else
    // Do number, 3-2-1
    string countString;
    switch (countdown) {
        case 3:
            countString = "3";
            break;
        case 2:
            countString = "2";
            break;
        case 1:
            countString = "1";
            break;
        default:
            break;
    }
    countLabel = CCLabelTTF::create(countString.c_str(), FONT_COMMON_STD, 256 * SCALE);
#endif
    
    // Put the label in the middle of the screen
    countLabel->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    this->addChild(countLabel);
    
    // Start Action
    CCScaleTo* shrinkAction = CCScaleTo::create(1.0, 0.1);
    CCCallFunc* endAction = CCCallFunc::create(this, callfunc_selector(AnnounceLayer::endCountDownAction));
    CCSequence* seq = CCSequence::create(shrinkAction, endAction, NULL);
    countLabel->runAction(seq);
}

void AnnounceLayer::endCountDownAction()
{
    // Do next count down
    countdown--;
    if (countdown > 0) {
        this->doNextCountDown();
    }
    else
    {
        // Remove the old countdown label
        countLabel->removeFromParentAndCleanup(true);
        countLabel = NULL;
        
        CCSprite* letter_name_bg = CCSprite::create(getResPath(GAMESCENE_LETTER_BG_IMG));
        letter_name_bg->setScaleX(SCALEX);
        letter_name_bg->setScaleY(SCALEY);
        letter_name_bg->setPosition(ccp(480 * SCALEX, 200 * SCALEY));
        this->addChild(letter_name_bg);
        
        // Done countdown. Announce the letters
        ((GameScene*)this->getParent())->changeGameState(GAME_START_GAME);
    }
}
void AnnounceLayer::endShowHints()
{
    ((CCSprite*)this->getChildByTag(TAG_HINTSPT))->setVisible(false);
    ((GameScene*)this->getParent())->changeGameState(GAME_COUNTDOWN);
}

void AnnounceLayer::startShowHints()
{
    CCCallFunc* endAction = CCCallFunc::create(this, callfunc_selector(AnnounceLayer::endShowHints));
    
    CCSprite* hint = CCSprite::create(getResPath(GAME_DIFF_HIT_IMG));
    hint->setScale(SCALE);
    hint->setPosition(ccp(winSize.width * 0.5, 772 * SCALEY));
    hint->setTag(TAG_HINTSPT);
    this->addChild(hint);
    
    hint->runAction(CCSequence::create(CCBlink::create(2.0, 3), endAction, NULL));
}

void AnnounceLayer::announceLetter(int letterIndex)
{
    // Remove the old label
    if (letterLabel != NULL) {
        letterLabel->removeFromParentAndCleanup(true);
        letterLabel = NULL;
    }
    
    // Get the name of the letter
    string letterString = AlphaBetUtils::getInstance()->getLetterName(letterIndex);
    stringToUpper(letterString);
    
    // create and initialize a Label
    if (letterLabel == NULL) {
        letterLabel = CCLabelTTF::create(letterString.c_str(), FONT_COMMON_STD, STD_HEADING_SIZE * SCALE * 1.2);
        // Locate the label
        letterLabel->setPosition(ccp(480 * SCALEX, 200 * SCALEY));
        letterLabel->setColor(ccYELLOW);
        
        this->addChild(letterLabel);
    }else
    {
        letterLabel->setString(letterString.c_str());
    }
    

}

void AnnounceLayer::announceHit(bool hit)
{
    // Remove the old label
    if (hitLabel !=NULL) {
        hitLabel->removeFromParentAndCleanup(true);
        hitLabel = NULL;
    }
    
    string hitMissString;
    if (hit) {
        hitMissString = "HIT!";
    }else
    {
        hitMissString = "MISS";
    }
    
    // Create and initialize a label
    hitLabel = CCLabelTTF::create(hitMissString.c_str(), FONT_COMMON_STD, 64 * SCALE);
    hitLabel->setScale(0.15);
    
    // Put the label in the middle of the screen
    hitLabel->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.75));
    this->addChild(hitLabel);
    
    hitSuccess = hit;
    
    // Start Action
    CCScaleTo* growAction = CCScaleTo::create(1.0, 1.0);
    CCCallFunc* endAction = CCCallFunc::create(this, callfunc_selector(AnnounceLayer::endAnnounceHit));
    CCSequence* seq = CCSequence::create(growAction, CCDelayTime::create(0.3),endAction, NULL);
    hitLabel->runAction(seq);
}

void AnnounceLayer::endAnnounceHit()
{
    // Remove the label
    if (hitLabel != NULL) {
        hitLabel->removeFromParentAndCleanup(true);
        hitLabel = NULL;
    }
    
    // Start a new Letter
    if (hitSuccess) {
        ((GameScene*)this->getParent())->changeGameState(GAME_END_ANNOUNCE_MISS);
    }else
    {
        ((GameScene*)this->getParent())->changeGameState(GAME_END_ANNOUNCE_HIT);
    }
}