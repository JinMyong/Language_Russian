//
//  Hero.hpp
//  AlephBet
//
//  Created by Fredric on 1/25/16.
//
//

#ifndef Hero_hpp
#define Hero_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GameOptions.hpp"

using namespace cocos2d;

class Hero:public CCSprite
{
private:
    GameOptions* options;
public:
    virtual bool init();
    void stop();
    void shoot();
    
    CREATE_FUNC(Hero);
};

#endif /* Hero_hpp */
