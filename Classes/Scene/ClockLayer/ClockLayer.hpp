//
//  ClockLayer.hpp
//  AlephBet
//
//  Created by Fredric on 1/15/16.
//
//

#ifndef ClockLayer_hpp
#define ClockLayer_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class ClockLayer:public CCLayer
{
private:
    CCSize winSize;
    CCLabelTTF* timeLabel;
    
    float lastIntervalSecs;
    int minutes;
    int seconds;
    
public:
    
    virtual bool init();
    void initTimer();
    void displayTime();
    void doTick(float dt);
    void setTimer(int minute, int second);
    void startTimer();
    void stopTimer();
    void pauseTimer();
    
    CREATE_FUNC(ClockLayer);
};

#endif /* ClockLayer_hpp */
