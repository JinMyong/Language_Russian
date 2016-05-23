//
//  GameOptionScene.hpp
//  AlephBet
//
//  Created by Fredric on 1/12/16.
//
//

#ifndef GameOptionScene_hpp
#define GameOptionScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GameOptions.hpp"

#define PADDING_Y       136
#define PADDING_X       20
#define COL_PADDING     130

using namespace cocos2d;
using namespace std;

enum
{
    FONT_COLOR_WHITE = 10,
    FONT_COLOR_BLACK,
    FONT_COLOR_PINK,
    FONT_COLOR_BLUE,
    
    NUM_COLOR_COUNT
};

const ccColor3B ccPINK= {122,5,155};

class GameOptionsScene:public CCLayer
{
private:
    CCSize winSize;
    CCMenuItemToggle* btn_diff_normal;
    CCMenuItemToggle* btn_diff_hard;
    CCMenuItemToggle* btn_sound_on;
    CCMenuItemToggle* btn_sound_off;
    CCMenuItemToggle* btn_effect_on;
    CCMenuItemToggle* btn_effect_off;
    CCMenuItemToggle* btn_voice_boy;
    CCMenuItemToggle* btn_voice_girl;
    CCMenuItemToggle* btn_font_print;
    CCMenuItemToggle* btn_font_script;
    CCMenuItemToggle* btn_fontcolor_white;
    CCMenuItemToggle* btn_fontcolor_black;
    CCMenuItemToggle* btn_fontcolor_pink;
    CCMenuItemToggle* btn_fontcolor_blue;
    
    GameOptions* options;
    
public:
    virtual bool init();
    static CCScene* scene();
    void createUI();
    void createMenu();
    void initMenuVariables();
    void selectFontColor(int index);
    bool compareColor(ccColor3B first, ccColor3B second);
    void mainmenuHandler(CCObject* sender);
    void gameDiffHandler(CCObject* sender);
    void gameSoundHandler(CCObject* sender);
    void gameEffectHandler(CCObject* sender);
    void gameVoiceHandler(CCObject* sender);
    void gameFontStyleHandler(CCObject* sender);
    void gameFontColorHandler(CCObject* sender);
    
    CREATE_FUNC(GameOptionsScene);
};

#endif /* GameOptionScene_hpp */
