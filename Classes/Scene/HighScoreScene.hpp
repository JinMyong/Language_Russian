//
//  HighScoreScene.hpp
//  AlephBet
//
//  Created by Fredric on 1/12/16.
//
//

#ifndef HighScoreScene_hpp
#define HighScoreScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GameOptions.hpp"

using namespace cocos2d;
using namespace std;

class HighScoreScene:public CCLayer
{
private:
    CCSize winSize;
    int highScore;
public:
    static CCScene* scene();
    virtual bool init();
    void createUI();
    void mainmenuHandle(CCObject* sender);
    void emailHandle(CCObject* sender);
    
    CREATE_FUNC(HighScoreScene);
};

#endif /* HighScoreScene_hpp */
