//
//  StoreScene.hpp
//  AlephBet
//
//  Created by Fredric on 1/25/16.
//
//

#ifndef StoreScene_hpp
#define StoreScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GameOptions.hpp"

#define BG_ZORDER                   0
#define CHARACTER_ZORDER            1
#define TABLE_ZORDER                2
#define MENU_ZORDER                 3

#define COIN_FONTS_SIZE             40
#define COIN_IMG_SCALE              0.5
#define MSG_NOT_ENOUGH_COIN_TXT     "You have not enough Coins"
#define MSG_NOT_ENOUGH_COIN_TITLE   ""

using namespace cocos2d;

enum{
    TAG_PENCIL = 10,
    TAG_FISH,
    TAG_BALLOON,
    TAG_BULB,
    TAG_EGG,
    TAG_AIRPLANE,
    TAG_HANDITEM,
    TAG_CHARACTER,
    TAG_COIN
};

enum{
    ZORDER_BG = 0,
    ZORDER_CHARACTER,
    ZORDER_TABLE,
    ZORDEER_MENU
};

class StoreScene : public CCLayer
{
private:
    CCSize winSize;
    CCMenuItemToggle* table_pencil;
    CCMenuItemToggle* table_fish;
    CCMenuItemToggle* table_balloon;
    CCMenuItemToggle* table_bulb;
    CCMenuItemToggle* table_egg;
    CCMenuItemToggle* table_airplane;
    
    GameOptions* options;
    int     currentCoin;
    int     targetCoin;
    
public:
    virtual bool init();
    static CCScene* scene();
    void createUI();
    void showItemPrice();
    void initializeCharacter();
    void tableHandler(CCObject* sender);
    void gotoMainMenu(CCObject* sender);
    void updateCoinLabel(float dt);
    
    CREATE_FUNC(StoreScene);
};


#endif /* StoreScene_hpp */
