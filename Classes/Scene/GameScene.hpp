//
//  GameScene.hpp
//  AlephBet
//
//  Created by Fredric on 12/25/15.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "TargetLayer.hpp"
#include "AnnounceLayer.hpp"
#include "GameOptions.hpp"
#include "ClockLayer.hpp"
#include "Hero.hpp"
#include "CharacterLayer.hpp"


#define BACKGROUND_Z    10
#define TARGET_Z        12
#define ARROW_Z         13
#define CHARACTER_Z     13
#define ANNOUNCE_Z      14
#define CLOCK_Z         15

#define TAG_HINTSPT     20

#define SUCCESS_SCORE   30  // When hit correct target plus this
#define MISS_SCORE      10  // When hit incorrect target minus this

using namespace cocos2d;
using namespace std;

typedef enum
{
    GAME_IDLE = 0,				// Idle state
    GAME_COUNTDOWN,				// Countdown 3-2-1
    GAME_START_GAME,			// Start the game action
    GAME_ANNOUNCE_LETTER,		// Announce the letter
    GAME_SHOOTING,				// Arrow is shooting
    GAME_HIT,					// Arrow hit the target (good letter)
    GAME_MISS,					// Arrow missed (wrong letter)
    GAME_END_ANNOUNCE_HIT,		// End announcing the hit
    GAME_END_ANNOUNCE_MISS,		// End announcing the miss
    GAME_ANNOUNCE_LEVEL,		// End of the round
    GAME_END_ANNOUNCE_LEVEL,	// End of the round
    GAME_END_GAME,				// End of the game
    GAME_EXIT,					// Exit the game scene
    GAME_SHOWING,               // Showing Letters on Difficult Level
    GAME_HIDE,                  // Hide Letters
    GAME_SHOWHINT,               // Showing "Look Quickly" on difficult mode
    NUM_GAME_STATES
} GameState;

class GameScene:public CCLayer
{
private:
    CCSize          winSize;
    TargetLayer*    targetLayer;
    AnnounceLayer*  announceLayer;
    ClockLayer*     clockLayer;
    bool            lastWasHit;
    GameOptions*    options;
    Hero*           hero_boy;
    CharacterLayer* characterLayer;
    int             gameScore;
    int             targetCount;
    bool            isPause;
    
public:
    int             lastTargetLetter;
    GameState       gameState;
    
    static CCScene* scene();
    virtual bool init();
    void createUI();
    void createMenu();
    
    void initVariables();
    void startScene();
    
    void startNewLetter();
    void randomizeLastElement(CCArray* array);
    
    void changeGameState(GameState newGameState);
    void doCountdown();
    void showHints();
    void startGameAction();
    void doStateAnnounceLetter();
    void doStateHit(bool goodhit);
    void doEndAnnounceHit(bool goodhit);
    void doStateAnnounceLevel();
    void doStateEndAnnounceLevel();
    void doGameEnd();
    void exitScene();
    
    void doShoot(int aimedLetter, CCPoint dest);
    
    void startDiffcultGame();
    void changeStateToHide();
    void shotResult(bool hit);
    void updateCurrentScore(int value);
    
    void timerUpdate(int newMinutes, int newSeconds);
    
    void quitHandler(CCNode* sender);
    void pauseHandler(CCNode* sender);
    void gotoNextScene();
    
    CREATE_FUNC(GameScene);
};

#endif /* GameScene_hpp */
