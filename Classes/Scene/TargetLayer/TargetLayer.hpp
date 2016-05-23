//
//  TargetLayer.hpp
//  AlephBet
//
//  Created by Fredric on 12/25/15.
//
//

#ifndef TargetLayer_hpp
#define TargetLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GameOptions.hpp"
#include "ShootItem.hpp"

using namespace cocos2d;
using namespace std;

#define TAG_ARROW       0
#define TAG_LETTER      1
#define TAG_TARGET      100

#define DEFAULT_COLS    3

class TargetLayer:public CCLayer
{
private:
    ShootItem*       arrowSprite;
    CCArray*        targets;
    float           shotSpeed;
    CCSize          winSize;
    GameOptions*    options;
    ccColor3B       letterColor;
    
    
public:
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    void enableTouches();
    void disableTouches();
    void makeTargets(int countTargets, CCArray* targetLetters);
    
    void removeArrowSprite();
    ShootItem* makeArrowSprite();
    void doShoot(CCSprite* target);
    void shootArrow(CCPoint dest, bool wasGoodHit);
    CCPoint getArrowStartLocation();
    void moveAnchor();
    
    void endHitShot();
    void endMissedShot();
    
    void hideLetters();
    void showLetters();
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    CREATE_FUNC(TargetLayer)
    
};

#endif /* TargetLayer_hpp */
