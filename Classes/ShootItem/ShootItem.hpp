//
//  ShootItem.hpp
//  AlephBet
//
//  Created by Fredric on 1/26/16.
//
//

#ifndef ShootItem_hpp
#define ShootItem_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GameOptions.hpp"

using namespace cocos2d;
using namespace std;

class ShootItem:public CCSprite
{
private:
    ThrowThings item_no;
    GameOptions* options;
public:
    virtual bool init();
    void flying(CCPoint pos, bool success);
    void shooted();
    void failed();
    void stop();
    void gotoInitState();
    void playEffect(ThrowThings item, bool wasGoodHit);
    CREATE_FUNC(ShootItem);
};

#endif /* ShootItem_hpp */
