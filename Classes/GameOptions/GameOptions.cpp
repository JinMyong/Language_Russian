//
//  GameOptions.cpp
//  AlephBet
//
//  Created by Fredric on 1/9/16.
//
//

#include "GameOptions.hpp"
#include "AlphaBetUtils.hpp"

GameOptions* GameOptions::instance = NULL;

GameOptions* GameOptions::getInstance()
{
    if (instance == NULL) {
        instance = new GameOptions();
    }
    return instance;
}

GameOptions::GameOptions()
{
    userDefault = CCUserDefault::sharedUserDefault();
    
    // Load player type (default Boy)
    playerType = userDefault->getBoolForKey(KEY_TYPE, true);
    
    // Load game mode (default : Easy)
    difficulty = userDefault->getIntegerForKey(KEY_DIFF, 0);
    
    // Load sound effect option (default : on)
    soundEffect = userDefault->getBoolForKey(KEY_EFFECT, true);
    
    // Load backgound Music option (default : on)
    soundBG = userDefault->getBoolForKey(KEY_BG, true);
    
    // Load Coin Count (default : 0)
    coin_count = userDefault->getIntegerForKey(KEY_COINS, 0);
    
    // Load Throw Item (default : pencil)
    throwItem = (ThrowThings)userDefault->getIntegerForKey(KEY_ITEM, item_Pencil);
    
    // Load Letter Color (default : whitecolor)
    letterColor.r = userDefault->getIntegerForKey(KEY_LCOLOR_R, 255);
    letterColor.g = userDefault->getIntegerForKey(KEY_LCOLOR_G, 255);
    letterColor.b = userDefault->getIntegerForKey(KEY_LCOLOR_B, 255);
    
    // Load Font type
    fontType = userDefault->getBoolForKey(KEY_FONTTYPE, true);
    
    currentLevel = userDefault->getIntegerForKey(KEY_LEVEL, 0);
    
    targetScore[0]  = TARGETSCORE_LEVEL1;
    targetScore[1]  = TARGETSCORE_LEVEL2;
    targetScore[2]  = TARGETSCORE_LEVEL3;
    targetScore[3]  = TARGETSCORE_LEVEL4;
    targetScore[4]  = TARGETSCORE_LEVEL5;
    targetScore[5]  = TARGETSCORE_LEVEL6;
    targetScore[6]  = TARGETSCORE_LEVEL7;
    targetScore[7]  = TARGETSCORE_LEVEL8;
    targetScore[8]  = TARGETSCORE_LEVEL9;
    targetScore[9]  = TARGETSCORE_LEVEL10;
    targetScore[10] = TARGETSCORE_LEVEL11;
    targetScore[11] = TARGETSCORE_LEVEL12;
    
    time_level[0] = Time_Level_1;
    time_level[1] = Time_Level_2;
    time_level[2] = Time_Level_3;
    time_level[3] = Time_Level_4;
    time_level[4] = Time_Level_5;
    time_level[5] = Time_Level_6;
    time_level[6] = Time_Level_7;
    time_level[7] = Time_Level_8;
    time_level[8] = Time_Level_9;
    time_level[9] = Time_Level_10;
    time_level[10] = Time_Level_11;
    time_level[11] = Time_Level_12;
    
    currentScore = 0;
    highScore = 0;
    total_score = 0;
    
    gotoPlayScene = false;
}

bool GameOptions::getPlayerType()
{
    return playerType;
}

int GameOptions::getDifficulty()
{
    return difficulty;
}

bool GameOptions::getSoundEffect()
{
    return soundEffect;
}

bool GameOptions::getSoundBg()
{
    return soundBG;
}

int GameOptions::getCurrentScore()
{
    return currentScore;
}

int GameOptions::getHighScore(int level)
{
    char key[20];
    sprintf(key, "%s%d", KEY_HSCORE,level);
    
    int hscore = userDefault->getIntegerForKey(key, 0);
    return hscore;
}

int GameOptions::getCurrentLevel()
{
    return currentLevel;
}

int GameOptions::getTargetScore(int level)
{
    if (level >= (sizeof(targetScore) / sizeof(targetScore[0]))) {
        return 0;
    }
    return targetScore[level];
}

bool GameOptions::getGotoPlayScene()
{
    return gotoPlayScene;
}

int GameOptions::getCoins()
{
    return coin_count;
}

ThrowThings GameOptions::getItem()
{
    return throwItem;
}

ccColor3B GameOptions::getLetterColor()
{
    return letterColor;
}

bool GameOptions::getFontType()
{
    return fontType;
}

bool GameOptions::isBoughtItem(ThrowThings value)
{
    bool retValue = false;
    switch (value) {
        case item_Fish:
            retValue = userDefault->getBoolForKey(KEY_BOUGHT_FISH, false);
            break;
        case item_Balloon:
            retValue = userDefault->getBoolForKey(KEY_BOUGHT_BALLOON, false);
            break;
        case item_LightBulb:
            retValue = userDefault->getBoolForKey(KEY_BOUGHT_BULB, false);
            break;
        case item_Egg:
            retValue = userDefault->getBoolForKey(KEY_BOUGHT_EGG, false);
            break;
        case item_Airplane:
            retValue = userDefault->getBoolForKey(KEY_BOUGHT_AIRPLANE, false);
            break;
        default:
            break;
    }
    return retValue;
}

int GameOptions::getTime(int level)
{
    if (level >= (sizeof(time_level) / sizeof(time_level[0]))) {
        return time_level[0];
    }
    return time_level[level];
}

int GameOptions::getTotoalScore()
{
    return total_score;
}

// ------------------------------------------------------------------------------ //

void GameOptions::setPlayerType(bool type)
{
    playerType = type;
    userDefault->setBoolForKey(KEY_TYPE, playerType);
}

void GameOptions::setSoundEffect(bool effect)
{
    soundEffect = effect;
    userDefault->setBoolForKey(KEY_EFFECT, soundEffect);
}

void GameOptions::setSoundBg(bool bg)
{
    soundBG = bg;
    userDefault->setBoolForKey(KEY_BG, soundBG);
}

void GameOptions::setDifficulty(int diff)
{
    difficulty = diff;
    userDefault->setIntegerForKey(KEY_DIFF, difficulty);
}

void GameOptions::setCurrentScore(int value)
{
    currentScore = value;
}

void GameOptions::setHighScore(int value, int level)
{
    highScore = value;
    char key[20];
    sprintf(key, "%s%d", KEY_HSCORE,level);
    userDefault->setIntegerForKey(key, highScore);
}

void GameOptions::setCurrentLevel(int value)
{
    currentLevel = value;
    userDefault->setIntegerForKey(KEY_LEVEL, currentLevel);
}

void GameOptions::setGotoPlayScene(bool value)
{
    gotoPlayScene = value;
}

void GameOptions::setCoins(int value)
{
    coin_count = value;
    userDefault->setIntegerForKey(KEY_COINS, coin_count);
}

void GameOptions::setItem(ThrowThings value)
{
    throwItem = value;
    userDefault->setIntegerForKey(KEY_ITEM, throwItem);
}

void GameOptions::setLetterColor(ccColor3B value)
{
    letterColor = value;
    userDefault->setIntegerForKey(KEY_LCOLOR_R, letterColor.r);
    userDefault->setIntegerForKey(KEY_LCOLOR_G, letterColor.g);
    userDefault->setIntegerForKey(KEY_LCOLOR_B, letterColor.b);
}

void GameOptions::setFontType(bool value)
{
    fontType =value;
    userDefault->setBoolForKey(KEY_FONTTYPE, fontType);

    AlphaBetUtils::getInstance()->setupLetterFontKeyMap_Print();
}

void GameOptions::setTotalScore(int value)
{
    total_score = value;
    userDefault->setIntegerForKey(KEY_TOTALSCORE, total_score);
}

void GameOptions::setBuyItem(ThrowThings value)
{
    switch (value) {
        case item_Fish:
            this->setCoins(coin_count - PRICE_FISH);
            userDefault->setBoolForKey(KEY_BOUGHT_FISH, true);
            break;;
        case item_Balloon:
            this->setCoins(coin_count - PRICE_STAR);
            userDefault->setBoolForKey(KEY_BOUGHT_BALLOON, true);
            break;
        case item_LightBulb:
            this->setCoins(coin_count - PRICE_BULB);
            userDefault->setBoolForKey(KEY_BOUGHT_BULB, true);
            break;
        case item_Egg:
            this->setCoins(coin_count - PRICE_MATZAH);
            userDefault->setBoolForKey(KEY_BOUGHT_EGG, true);
            break;
        case item_Airplane:
            this->setCoins(coin_count - PRICE_MATZAHBALL);
            userDefault->setBoolForKey(KEY_BOUGHT_AIRPLANE, true);
            break;
        default:
            break;
    }
}
