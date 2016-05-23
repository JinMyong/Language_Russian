//
//  IntroScene.hpp
//  AlephBet
//
//  Created by Fredric on 12/15/15.
//
//

#ifndef IntroScene_hpp
#define IntroScene_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class IntroScene:public CCLayer{
private:
    CCSize winSize;
public:
    static CCScene* scene();
    virtual bool init();
    void createUI();
    
    void gotoplay(CCNode* sender);
    void gotoMainMenu(CCNode* sender);
    
    CREATE_FUNC(IntroScene);
};

#endif /* IntroScene_hpp */
