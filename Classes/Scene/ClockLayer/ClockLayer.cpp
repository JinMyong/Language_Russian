//
//  ClockLayer.cpp
//  AlephBet
//
//  Created by Fredric on 1/15/16.
//
//

#include "ClockLayer.hpp"
#include "Const.h"
#include "GameScene.hpp"
#include "SoundEffects.hpp"

bool ClockLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    
    this->initTimer();
    return true;
}

void ClockLayer::initTimer()
{
    // Start the timer interval at 1 second per thick
    lastIntervalSecs = 1.0;
    
    char timestring [10];
    sprintf(timestring, "%01d:%02d", minutes, seconds);
    
    timeLabel = CCLabelTTF::create(timestring, FONT_COMMON_STD, GAME_INFO_FONT_SIZE * SCALE);
    timeLabel->setPosition(ccp(100 * SCALEX, winSize.height - 45 *SCALEY));
    this->addChild(timeLabel);
}

void ClockLayer::displayTime()
{
    char timestring [10];
    sprintf(timestring, "%01d:%02d", minutes, seconds);
    timeLabel->setString(timestring);
}

void ClockLayer::doTick(float dt)
{
    
    if (seconds <= 10 && minutes <= 0) {
        timeLabel->setColor(ccRED);
        CCLog("Second is %d", seconds);
        if (seconds == 10 && seconds > 0) {
            SoundEffects::getInstance()->playTickOne();
        }
        if (seconds == 0)
        {
            SoundEffects::getInstance()->playAlarm();
        }
    }
    
    seconds--;
    if (seconds < 0) {
        seconds = 59;
        minutes--;
        if (minutes < 0) {
            // Time is 00:00
            minutes = 0;
            seconds = 0;
            
            // Stop the timer
            this->stopTimer();
            
            // Play end game sound
        }
    }
    
    // Display the time on Screen
    this->displayTime();
    
    //Update the game with the new time
    ((GameScene*)this->getParent())->timerUpdate(minutes, seconds);
}

void ClockLayer::startTimer()
{
    this->schedule(schedule_selector(ClockLayer::doTick), lastIntervalSecs);
}

void ClockLayer::stopTimer()
{
    this->unschedule(schedule_selector(ClockLayer::doTick));
}

void ClockLayer::setTimer(int minute, int second)
{
    minutes = minute;
    seconds = second;
}