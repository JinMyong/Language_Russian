//
//  MissedLetterScene.hpp
//  AlephBet
//
//  Created by Fredric on 2/11/16.
//
//

#ifndef MissedLetterScene_hpp
#define MissedLetterScene_hpp

#include <stdio.h>
#include "cocos2d.h"

#define NUM_COLUMNS 6
#define LETTER_BOARD_OFFSET_X   20
#define LETTER_BOARD_OFFSET_Y   10
#define LETTER_BOARD_PAD_X      5
#define LETTER_BOARD_PAD_Y      5
#define VOWEL_ROW_OFFSET        8

using namespace cocos2d;

class MissedLetterScene:public CCLayer
{
private:
    CCSize      winSize;
public:
    static CCScene* scene();
    virtual bool init();
    void createUI();

    void showLetters();
    void backHandle(CCObject* sender);
    void mainMenuHandle(CCObject* sender);
    void emailHandle(CCObject* sender);

    void preloadSounds();
    CREATE_FUNC(MissedLetterScene);
};

#endif /* MissedLetterScene_hpp */
