//
//  TargetLayer.cpp
//  AlephBet
//
//  Created by Fredric on 12/25/15.
//
//

#include "TargetLayer.hpp"
#include "Const.h"
#include "AlphaBetUtils.hpp"
#include "GameScene.hpp"
#include "Global.hpp"

bool TargetLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    
    // Init the target Array
    targets = CCArray::create();
    targets->retain();
    
    // Pre-Clear the arrow sprite
    arrowSprite = NULL;
    
    CCArray* targetLetters = CCArray::create();
    makeTargets(9, targetLetters);
    
    options = GameOptions::getInstance();
    letterColor = options->getLetterColor();
    
    // Initially the speed of arrows is 1.0
    shotSpeed = 1.0;
    
    return true;
}

void TargetLayer::onEnter()
{
    this->enableTouches();
    CCLayer::onEnter();
}

void TargetLayer::onExit()
{
    this->disableTouches();
    CCLayer::onExit();
}

void TargetLayer::makeTargets(int countTargets, cocos2d::CCArray *targetLetters)
{
    this->removeAllChildrenWithCleanup(true);
    targets->removeAllObjects();
    
    int targetCount = 0;
    int rows =(countTargets + DEFAULT_COLS - 1) / DEFAULT_COLS;
    int cols = countTargets > DEFAULT_COLS?DEFAULT_COLS:countTargets;
    
    float targetSpaceX = (winSize.width - (2.0 * TARGET_AREA_PAD)) / cols;

    for (int rowIndex = 0; rowIndex < rows; rowIndex++) {
        
        // Check if more targets than letters. Just stop making targets.
        if (targetCount >= targetLetters->count() && targetLetters->count() != 0) {
            break;
        }
        
        cols = (countTargets - targetCount) > DEFAULT_COLS?DEFAULT_COLS:(countTargets - targetCount);
        targetSpaceX =  (winSize.width - (2.0 * TARGET_AREA_PAD)) / cols;
        CCLog("Cols is %d", cols);
        CCLog("targetSpaceX is %f", targetSpaceX);
        
        // Calculate the Y position
        float yPos = winSize.height - TARGET_AREA_Y_OFFSET - 120 * SCALEY * rowIndex;
        
        
        for (int colIndex = 0; colIndex < cols ; colIndex++) {
            
            // Calculate the X position
            float xPos = (colIndex * targetSpaceX) + targetSpaceX * 0.5 + TARGET_AREA_PAD;
            
            // Add Targret Sprite
            CCSprite* targetSprite = CCSprite::create(getResPath(GAME_TARGET_IMG));
            targetSprite->setPosition(ccp(xPos, yPos));
            targetSprite->setScale(SCALE * 1.2);
            this->addChild(targetSprite, 0);
            
            // Add the target sprite
            targets->addObject(targetSprite);
            
            string fontName;
            bool fontType = GameOptions::getInstance()->getFontType();
            if (fontType) {
                fontName = FONT_LETTER_NOR;
            }else
            {
                fontName = FONT_LETTER_CUR;
            }

            CCLabelTTF* letterSprite;
            if (targetLetters->count() > 0) {
                // Get the next letter for the target
                CCInteger* numberObj = (CCInteger*)targetLetters->objectAtIndex(targetCount);
                int letterIndex = numberObj->getValue();
                
                targetSprite->setTag(TAG_TARGET + letterIndex);
                
                // Make the letter sprite(Label) on the target. Font size is the target width
                string letterString = AlphaBetUtils::getInstance()->getKeyMapFont(letterIndex);
                letterSprite = CCLabelTTF::create(letterString.c_str(), fontName.c_str(), targetSprite->getContentSize().width * 0.6);
                letterSprite->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
                letterSprite->setHorizontalAlignment(kCCTextAlignmentCenter);
                letterSprite->setDimensions(CCSize(targetSprite->getContentSize().width, targetSprite->getContentSize().width));
            }else
            {
                // Fill-in an Empty Target
                letterSprite = CCLabelTTF::create("", fontName.c_str(), targetSprite->getContentSize().width);
            }
            
            letterSprite->setColor(letterColor);
            CCPoint centerPoint = ccp(targetSprite->getContentSize().width * 0.5, targetSprite->getContentSize().height * 0.5);
            letterSprite->setPosition(centerPoint);
            targetSprite->addChild(letterSprite, 10, TAG_LETTER);
            
            targetCount++;
        }
    }
    
    CCLOG("Targets Count is %d", targets->count());
}

void TargetLayer::enableTouches()
{
    this->setTouchEnabled(true);
    this->setTouchPriority(0);
}

void TargetLayer::disableTouches()
{
    this->setTouchEnabled(false);
}

void TargetLayer::doShoot(cocos2d::CCSprite *target)
{
    int aimedLetter = target->getTag();
    CCPoint dest = target->getPosition();
    ((GameScene*)this->getParent())->changeGameState(GAME_SHOOTING);
    ((GameScene*)this->getParent())->doShoot(aimedLetter, dest);
}

void TargetLayer::endHitShot()
{
    CCLog("TargetLayer::endHitShot");
    // Set the game state to "hit"
    ((GameScene*)this->getParent())->changeGameState(GAME_HIT);
}

void TargetLayer::endMissedShot()
{
    CCLog("TargetLayer::endMissedShot");
    // Set the game state to missed
    ((GameScene*)this->getParent())->changeGameState(GAME_MISS);
}

void TargetLayer::removeArrowSprite()
{
    // Remove the old arrow, if any
    CCSprite* arrow = (CCSprite*)this->getChildByTag(TAG_ARROW);
    if (arrow != NULL) {
        arrow->removeFromParentAndCleanup(true);
        arrow = NULL;
    }
}

ShootItem* TargetLayer::makeArrowSprite()
{
    ShootItem* newSprite = ShootItem::create();
    
    return newSprite;
}

CCPoint TargetLayer::getArrowStartLocation()
{
    CCPoint location;
    
    location.x = 440 * SCALEX;
    location.y = 416 * SCALEY;
    
    return location;
}

void TargetLayer::hideLetters()
{
    for (int index = 0; index < targets->count(); index++) {
        CCSprite* target = (CCSprite*)targets->objectAtIndex(index);
        CCLabelTTF* letter = (CCLabelTTF*)target->getChildByTag(TAG_LETTER);
        letter->setVisible(false);
    }
}

void TargetLayer::showLetters()
{
    for (int i = 0; i < targets->count(); i++) {
        CCSprite* target = (CCSprite*)targets->objectAtIndex(i);
        CCLabelTTF* letter = (CCLabelTTF*)target->getChildByTag(TAG_LETTER);
        letter->setVisible(true);
    }
}

void TargetLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCLog("Game State : %d", ((GameScene*)this->getParent())->gameState);
    if ((((GameScene*)this->getParent())->gameState == GAME_ANNOUNCE_LETTER) || ((GameScene*)this->getParent())->gameState == GAME_HIDE) {
        CCTouch* fingerOne = (CCTouch*)pTouches->anyObject();
        CCPoint pointOne = CCDirector::sharedDirector()->convertToUI(fingerOne->getLocationInView());
        CCPoint location = this->convertToNodeSpace(pointOne);
        
        for (int index = 0; index < targets->count(); index++) {
            CCSprite* target = (CCSprite*)targets->objectAtIndex(index);
            
            // Get the Box of the sprite
            CCRect rect = target->boundingBox();
            
            if (rect.containsPoint(location)) {
                
                if (((GameScene*)this->getParent())->gameState == GAME_HIDE) {
                    this->showLetters();
                }
                
                CCLog("Shooted %d", index);
                this->doShoot(target);
                break;
            }
        }
    }
}
