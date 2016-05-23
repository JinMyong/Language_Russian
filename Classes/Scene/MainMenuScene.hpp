//
//  MainMenuScene.hpp
//  AlephBet
//
//  Created by Fredric on 12/15/15.
//
//

#ifndef MainMenuScene_hpp
#define MainMenuScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GameOptions.hpp"
#include "AlphaBetUtils.hpp"
#include "LetterBag.hpp"
#include "Global.hpp"

using namespace cocos2d;
using namespace std;

class MainMenuScene:public CCLayer
{
private:
    CCSize          winSize;
    GameOptions*    options;
    LetterBag*      bag;
public:
    static CCScene* scene();
    virtual bool init();
    void createUI();
    
    void gotoPlay(CCObject* sender);
    void gotochooseLetter(CCObject* sender);
    void gotoOption(CCObject* sender);
    void gotoHighScore(CCObject* sender);
    void gotoAbout(CCObject* sender);
    void gotoStore(CCObject* sender);
    void resetHandler(CCObject* sender);
    void alertOKHandler(CCObject* sender);
    void alertCancelHandler(CCObject* sender);
    
    CREATE_FUNC(MainMenuScene);
};

#endif /* MainMenuScene_hpp */
