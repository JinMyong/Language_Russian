//
//  CharacterLayer.hpp
//  AlephBet
//
//  Created by Fredric on 1/26/16.
//
//

#ifndef CharacterLayer_hpp
#define CharacterLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GameOptions.hpp"
#include "ShootItem.hpp"
#include "Hero.hpp"
#include "Const.h"

using namespace cocos2d;
using namespace std;

class CharacterLayer:public CCLayer
{
private:
    Hero*           hero;
    ShootItem*      shootItem;
    GameOptions*    options;
    CCSize          winSize;
    CCPoint         target_pos;
    bool            goodHit;
    
public:
    virtual bool init();
    
    void createObjects();
    void shoot(CCPoint dest, bool wasGoodHit);
    void doShoot();
    void endHitShot();
    void endMissShot();
    void stop();
    
    CREATE_FUNC(CharacterLayer);
};


#endif /* CharacterLayer_hpp */
