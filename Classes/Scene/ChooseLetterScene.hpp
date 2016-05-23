//
//  ChooseLetterScene.hpp
//  AlephBet
//
//  Created by Fredric on 12/16/15.
//
//

#ifndef ChooseLetterScene_hpp
#define ChooseLetterScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GameOptions.hpp"

#define NUM_COLUMNS             6
#define LETTER_BOARD_OFFSET_X   20
#define LETTER_BOARD_OFFSET_Y   10
#define LETTER_BOARD_PAD_X      5
#define LETTER_BOARD_PAD_Y      5
#define VOWEL_ROW_OFFSET        20
#define LETTER_BOARD_Z          10

#define LETTER_OFFSET_Y         94
#define BG_ZORDER               0
#define YC_ZORDER               1   // YELLOW CHAIR ZORDER
#define LB_ZORDER               2   // LETTER BOARD ZORDER
#define BC_ZORDER               3   // BLUE CHAIR ZORDER
#define CH_ZORDER               4   // CHARACTER ZORDER
#define MN_ZORDER               5   // MENU ZORDER
#define LL_ZORDER               6   // Last Letter zorder

using namespace cocos2d;
using namespace std;

class ChooseLetterScene:public CCLayer
{
private:
    CCSize winSize;
    int lastLetterChosen;
    CCLabelTTF* lastLetterLabel;
    void stringToUpper(string &s);
    bool isGotoGameScene;
    GameOptions* options;
    bool testCur;
    
public:
    static CCScene* scene();
    virtual bool init();
    void createUI();
    void createLetterBoard();
    void createMenu();
    
    void gotoMainMenu(CCObject* sender);
    void selectAllHandle(CCObject* sender);
    void selectClearHandle(CCObject* sender);
    void selectPlayHandele(CCObject* sender);
    
    CCAction* getSelectedAction();
    void letterSpriteSelected(CCLabelTTF* letterSprite);
    void selectAllLetters();
    void unselectAllLetters();
    
    bool verifyEnoughLetters();
    void displayLastLetter(int lastLetterIndex);
    void clearLastLetter();
    
    void testCursive();
    
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    CREATE_FUNC(ChooseLetterScene);
};

#endif /* ChooseLetterScene_hpp */
