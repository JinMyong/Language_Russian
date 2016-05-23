//
//  GameResultScene.hpp
//  AlephBet
//
//  Created by Fredric on 1/16/16.
//
//

#ifndef GameResultScene_hpp
#define GameResultScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GameOptions.hpp"

#define TAG_COIN        10
#define TAG_EARNCOIN    12
#define TAG_ACTCOIN     11

#define COIN_INIT_POS   ccp(420 * SCALEX, 620 * SCALEY)

using namespace cocos2d;
using namespace std;

class GameResultScene:public CCLayer
{
private:
    CCSize winSize;
    GameOptions* options;
    int     temp_coin;
    int     temp_earn;
    int     current_coin;
    int     targetCoin;
    int     current_level;
    int     current_score;
    int     target_score;
    
public:
    static CCScene* scene();
    virtual bool init();
    
    void createUI();
    void showGameInfo();
    void showButtons();
    void getCoins();
    void mainMenuHandler(CCObject* sender);
    void gotoNextScene(CCObject* sender);
    void emailHandle(CCObject* sender);
    void gotoMissedLetterScene(CCObject* sender);
    void moveCoin();
    void incCoinCount();
    
    void updateCoinLabel();
    
    CREATE_FUNC(GameResultScene);
};

#endif /* GameResultScene_hpp */
