//
//  GameOptions.hpp
//  AlephBet
//
//  Created by Fredric on 1/9/16.
//
//

#ifndef GameOptions_hpp
#define GameOptions_hpp

#include <stdio.h>
#include "cocos2d.h"

#define KEY_TYPE            "PLAYER_TYPE"
#define KEY_DIFF            "GAME_DIFF"
#define KEY_EFFECT          "SOUND_EFF"
#define KEY_BG              "SOUND_BG"
#define KEY_HSCORE          "HIGHSCORE_LEVEL"
#define KEY_LEVEL           "CURRENT_LEVEL"
#define KEY_COINS           "GAME_COINS"
#define KEY_ITEM            "THROW_ITEM"
#define KEY_LCOLOR_R        "LETTER_COLOR_R"
#define KEY_LCOLOR_G        "LETTER_COLOR_G"
#define KEY_LCOLOR_B        "LETTER_COLOR_B"
#define KEY_FONTTYPE        "FONT_TYPE"
#define KEY_TOTALSCORE      "TOTAL_SCORE"

#define KEY_BOUGHT_FISH         "BOUGHT_FISH"
#define KEY_BOUGHT_BULB         "BOUGHT_BULB"
#define KEY_BOUGHT_EGG          "BOUGHT_EGG"
#define KEY_BOUGHT_AIRPLANE     "BOUGHT_AIRPLANE"
#define KEY_BOUGHT_BALLOON      "BOUGHT_BALLOON"

#define PRICE_FISH          75
#define PRICE_STAR          75
#define PRICE_BULB          75
#define PRICE_MATZAHBALL    75
#define PRICE_MATZAH        75

#define TARGETSCORE_LEVEL1  300
#define TARGETSCORE_LEVEL2  400
#define TARGETSCORE_LEVEL3  500
#define TARGETSCORE_LEVEL4  600
#define TARGETSCORE_LEVEL5  700
#define TARGETSCORE_LEVEL6  800
#define TARGETSCORE_LEVEL7  900
#define TARGETSCORE_LEVEL8  1000
#define TARGETSCORE_LEVEL9  1100
#define TARGETSCORE_LEVEL10 1200
#define TARGETSCORE_LEVEL11 1300
#define TARGETSCORE_LEVEL12 1400

#define Time_Level_1        60
#define Time_Level_2        70
#define Time_Level_3        80
#define Time_Level_4        90
#define Time_Level_5        100
#define Time_Level_6        110
#define Time_Level_7        120
#define Time_Level_8        130
#define Time_Level_9        140
#define Time_Level_10       150
#define Time_Level_11       160
#define Time_Level_12       170

using namespace cocos2d;
using namespace std;

typedef enum{
    item_Pencil = 0,
    item_Fish,
    item_Balloon,
    item_LightBulb,
    item_Egg,
    item_Airplane,
    count_Item
}ThrowThings;

class GameOptions
{
private:
    static GameOptions* instance;
    CCUserDefault* userDefault;
    bool    playerType;     // true : boy   false : girl
    int     difficulty;     // 0 : easy     1 : hard
    bool    soundEffect;    // true : on    false : off (Sound Effects)
    bool    soundBG;        // ture : on    false : off (Backgound Music)
    int     currentScore;
    int     highScore;
    int     currentLevel;
    int     targetScore[12];
    int     time_level[12];
    int     coin_count;
    int     total_score;
    
    bool    gotoPlayScene;  // if letter count is enough, show chooseletterScene
    bool    fontType;       // true : print     false : script
    ThrowThings     throwItem;
    ccColor3B       letterColor;
    
public:
    GameOptions();
    ~GameOptions();
    
    static GameOptions* getInstance();
    
    bool    getPlayerType();
    int     getDifficulty();
    bool    getSoundEffect();
    bool    getSoundBg();
    int     getCurrentScore();
    int     getHighScore(int level);
    int     getCurrentLevel();
    int     getTargetScore(int level);
    bool    getGotoPlayScene();
    bool    getFontType();
    int     getCoins();
    bool    isBoughtItem(ThrowThings value);
    ThrowThings     getItem();
    ccColor3B       getLetterColor();
    int     getTime(int level);
    int     getTotoalScore();
    
    void    setPlayerType(bool type);
    void    setDifficulty(int diff);
    void    setSoundEffect(bool effect);
    void    setSoundBg(bool bg);
    void    setCurrentScore(int value);
    void    setHighScore(int value, int level);
    void    setCurrentLevel(int value);
    void    setGotoPlayScene(bool value);
    void    setFontType(bool value);
    void    setCoins(int value);
    void    setItem(ThrowThings value);
    void    setLetterColor(ccColor3B value);
    void    setBuyItem(ThrowThings value);
    void    setTotalScore(int value);
};

#endif /* GameOptions_hpp */
