//
//  GameOptionScene.cpp
//  AlephBet
//
//  Created by Fredric on 1/12/16.
//
//

#include "GameOptionScene.hpp"
#include "MainMenuScene.hpp"
#include "Const.h"
#include "SimpleAudioEngine.h"
#include "SoundEffects.hpp"

using namespace CocosDenshion;

CCScene* GameOptionsScene::scene()
{
    CCScene* scene = CCScene::create();
    GameOptionsScene* layer = GameOptionsScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameOptionsScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    winSize = CCDirector::sharedDirector()->getWinSize();
    options = GameOptions::getInstance();
//    options->setCoins(3000); //     For Test
//    options->setCurrentLevel(11);
    createUI();
    return true;
}

void GameOptionsScene::createUI()
{
    // Add Background image
    CCSprite* bg = CCSprite::create(getResPath(OPTIONS_BG_IMG));
    bg->setScaleX(SCALEX);
    bg->setScaleY(SCALEY);
    bg->setPosition(ccp(winSize.width * 0.5, winSize.height* 0.5));
    this->addChild(bg);
    
    CCSprite* bg_black = CCSprite::create(getResPath(OPTIONS_BG_BLACK));
    bg_black->setScaleX(SCALEX);
    bg_black->setScaleY(SCALEY);
    bg_black->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    this->addChild(bg_black);
    
    CCLabelTTF* top_title = CCLabelTTF::create(TXT_OPTION_TITLE, FONT_TITLE, 60 * SCALE);
    top_title->setPosition(ccp(winSize.width * 0.5, 1090 * SCALEY));
    top_title->setColor(COLOR_TITLE_TOP);
    this->addChild(top_title);
    
    // Add Buttons
    createMenu();
    
    // Init Buttons
    initMenuVariables();
    
    // Add title difficulty
    CCSprite* title_difficulty = CCSprite::create(getResPath(OPTIONS_TITLE_DIFFCULTY));
    title_difficulty->setScale(SCALE);
    title_difficulty->setPosition(ccp(winSize.width * 0.5, btn_diff_normal->getPositionY() + 55 * SCALEY));
    this->addChild(title_difficulty);
    
    // Add title Sound
    CCSprite* title_sound = CCSprite::create(getResPath(OPTIONS_TITLE_SOUND));
    title_sound->setScale(SCALE);
    title_sound->setPosition(ccp(winSize.width * 0.5, btn_sound_on->getPositionY() + 55 * SCALEY));
    this->addChild(title_sound);
    
    // Add title Effect
    CCSprite* title_effect = CCSprite::create(getResPath(OPTIONS_TITLE_EFFECT));
    title_effect->setScale(SCALE);
    title_effect->setPosition(ccp(winSize.width * 0.5, btn_effect_on->getPositionY() + 55 * SCALEY));
    this->addChild(title_effect);
    
    // Add title Voice
    CCSprite* title_voice = CCSprite::create(getResPath(OPTIONS_TITLE_VOICE));
    title_voice->setScale(SCALE);
    title_voice->setPosition(ccp(winSize.width * 0.5, btn_voice_boy->getPositionY()  + 55 * SCALEY));
    this->addChild(title_voice);
    
    // Add tittle font style
    CCSprite* title_font = CCSprite::create(getResPath(OPTIONS_title_fontSTYLE));
    title_font->setScale(SCALE);
    title_font->setPosition(ccp(winSize.width * 0.5, btn_font_print->getPositionY()  + 55 * SCALEY));
    this->addChild(title_font);
    
    CCSprite* title_fontcolor = CCSprite::create(getResPath(OPTIONS_title_fontCOLOR));
    title_fontcolor->setScale(SCALE);
    title_fontcolor->setPosition(ccp(winSize.width * 0.5, btn_fontcolor_black->getPositionY() + 55 * SCALEY));
    this->addChild(title_fontcolor);
}

void GameOptionsScene::createMenu()
{
    // Add mainmenu button
    CCMenuItem* mainmenuItem = CCMenuItemImage::create(getResPath(OPTIONS_BTN_MAINMENU_NOR), getResPath(OPTIONS_BTN_MAINMENU_PRS), this, menu_selector(GameOptionsScene::mainmenuHandler));
    mainmenuItem->setScale(MIN(SCALEX, SCALEY));
    mainmenuItem->setPosition(winSize.width * 0.5, 90 * SCALEY);
    
    
    // Add Normal Button
    CCMenuItemImage* diff_normal_on  = CCMenuItemImage::create(getResPath(OPTIONS_BTN_NORMAL_ON), getResPath(OPTIONS_BTN_NORMAL_ON));
    CCMenuItemImage* diff_normal_off = CCMenuItemImage::create(getResPath(OPTIONS_BTN_NORMAL_OFF), getResPath(OPTIONS_BTN_NORMAL_OFF));
    btn_diff_normal = CCMenuItemToggle::createWithTarget(this, menu_selector(GameOptionsScene::gameDiffHandler), diff_normal_off, diff_normal_on, NULL);
    btn_diff_normal->setAnchorPoint(ccp(1, 0.5));
    btn_diff_normal->setPosition(ccp(winSize.width * 0.5 - PADDING_X * SCALEX, winSize.height - 222 * SCALEY));
    
    // Add Hard Button
    CCMenuItemImage* diff_hard_on = CCMenuItemImage::create(getResPath(OPTIONS_BTN_HARD_ON), getResPath(OPTIONS_BTN_HARD_ON));
    CCMenuItemImage* diff_hard_off = CCMenuItemImage::create(getResPath(OPTIONS_BTN_HARD_OFF), getResPath(OPTIONS_BTN_HARD_OFF));
    btn_diff_hard = CCMenuItemToggle::createWithTarget(this, menu_selector(GameOptionsScene::gameDiffHandler), diff_hard_off, diff_hard_on, NULL);
    btn_diff_hard->setAnchorPoint(ccp(0, 0.5));
    btn_diff_hard->setPosition(ccp(winSize.width * 0.5 + PADDING_X * SCALEX, btn_diff_normal->getPositionY()));
    
    
    // Add Sound On
    CCMenuItemImage* sound_on_on = CCMenuItemImage::create(getResPath(OPTIONS_BTN_SOUND_ON_ON), getResPath(OPTIONS_BTN_SOUND_ON_ON));
    CCMenuItemImage* sound_on_off = CCMenuItemImage::create(getResPath(OPTIONS_BTN_SOUND_ON_OFF), getResPath(OPTIONS_BTN_SOUND_ON_OFF));
    btn_sound_on = CCMenuItemToggle::createWithTarget(this, menu_selector(GameOptionsScene::gameSoundHandler), sound_on_off, sound_on_on, NULL);
    btn_sound_on->setAnchorPoint(ccp(1, 0.5));
    btn_sound_on->setPosition(ccp(winSize.width * 0.5 - PADDING_X * SCALEX, btn_diff_normal->getPositionY() - PADDING_Y * SCALEY));
    
    // Add Sound Off
    CCMenuItemImage* sound_off_on = CCMenuItemImage::create(getResPath(OPTIONS_BTN_SOUND_OFF_ON), getResPath(OPTIONS_BTN_SOUND_OFF_ON));
    CCMenuItemImage* sound_off_off = CCMenuItemImage::create(getResPath(OPTIONS_BTN_SOUND_OFF_OFF), getResPath(OPTIONS_BTN_SOUND_OFF_OFF));
    btn_sound_off = CCMenuItemToggle::createWithTarget(this, menu_selector(GameOptionsScene::gameSoundHandler), sound_off_off, sound_off_on, NULL);
    btn_sound_off->setAnchorPoint(ccp(0, 0.5));
    btn_sound_off->setPosition(ccp(winSize.width * 0.5 + PADDING_X * SCALEX, btn_sound_on->getPositionY()));
    
    // Add Effect On
    CCMenuItemImage* effect_on_on = CCMenuItemImage::create(getResPath(OPTIONS_BTN_EFFECT_ON_ON), getResPath(OPTIONS_BTN_EFFECT_ON_ON));
    CCMenuItemImage* effect_on_off = CCMenuItemImage::create(getResPath(OPTIONS_BTN_EFFECT_ON_OFF), getResPath(OPTIONS_BTN_EFFECT_ON_OFF));
    btn_effect_on = CCMenuItemToggle::createWithTarget(this, menu_selector(GameOptionsScene::gameEffectHandler), effect_on_off, effect_on_on, NULL);
    btn_effect_on->setAnchorPoint(ccp(1, 0.5));
    btn_effect_on->setPosition(ccp(winSize.width * 0.5 - PADDING_X * SCALEX, btn_sound_on->getPositionY() - PADDING_Y * SCALEY));
    
    // Add Effect off
    CCMenuItemImage* effect_off_on = CCMenuItemImage::create(getResPath(OPTIONS_BTN_EFFECT_OFF_ON), getResPath(OPTIONS_BTN_EFFECT_OFF_ON));
    CCMenuItemImage* effect_off_off = CCMenuItemImage::create(getResPath(OPTIONS_BTN_EFFECT_OFF_OFF), getResPath(OPTIONS_BTN_EFFECT_OFF_OFF));
    btn_effect_off = CCMenuItemToggle::createWithTarget(this, menu_selector(GameOptionsScene::gameEffectHandler), effect_off_off, effect_off_on, NULL);
    btn_effect_off->setAnchorPoint(ccp(0, 0.5));
    btn_effect_off->setPosition(ccp(winSize.width * 0.5 + PADDING_X * SCALEX, btn_effect_on->getPositionY()));
    
    
    // Add Voice Boy
    CCMenuItem* voice_boy_on = CCMenuItemImage::create(getResPath(OPTIONS_BTN_VOICE_BOY_ON), getResPath(OPTIONS_BTN_VOICE_BOY_ON));
    CCMenuItem* voice_boy_off = CCMenuItemImage::create(getResPath(OPTIONS_BTN_VOICE_BOY_OFF), getResPath(OPTIONS_BTN_VOICE_BOY_OFF));
    btn_voice_boy = CCMenuItemToggle::createWithTarget(this, menu_selector(GameOptionsScene::gameVoiceHandler), voice_boy_off, voice_boy_on, NULL);
    btn_voice_boy->setAnchorPoint(ccp(1, 0.5));
    btn_voice_boy->setPosition(ccp(winSize.width * 0.5 - PADDING_X * SCALEX, btn_effect_on->getPositionY() - PADDING_Y * SCALEY));
    
    // Add Voice Girl
    CCMenuItem* voice_girl_on = CCMenuItemImage::create(getResPath(OPTIONS_BTN_VOICE_GIRL_ON), getResPath(OPTIONS_BTN_VOICE_GIRL_ON));
    CCMenuItem* voice_girl_off = CCMenuItemImage::create(getResPath(OPTIONS_BTN_VOICE_GIRL_OFF), getResPath(OPTIONS_BTN_VOICE_GIRL_OFF));
    btn_voice_girl = CCMenuItemToggle::createWithTarget(this, menu_selector(GameOptionsScene::gameVoiceHandler), voice_girl_off, voice_girl_on, NULL);
    btn_voice_girl->setAnchorPoint(ccp(0, 0.5));
    btn_voice_girl->setPosition(ccp(winSize.width * 0.5 + PADDING_X * SCALEX, btn_voice_boy->getPositionY()));
    
    // Add Font Print
    CCMenuItem* font_print_on = CCMenuItemImage::create(getResPath(OPTIONS_BTN_FONT_PRINT_ON), getResPath(OPTIONS_BTN_FONT_PRINT_ON));
    CCMenuItem* font_print_off = CCMenuItemImage::create(getResPath(OPTIONS_BTN_FONT_PRINT_OFF), getResPath(OPTIONS_BTN_FONT_PRINT_OFF));
    btn_font_print = CCMenuItemToggle::createWithTarget(this, menu_selector(GameOptionsScene::gameFontStyleHandler), font_print_off, font_print_on, NULL);
    btn_font_print->setAnchorPoint(ccp(1, 0.5));
    btn_font_print->setPosition(ccp(winSize.width * 0.5 - PADDING_X * SCALEX, btn_voice_boy->getPositionY() - PADDING_Y * SCALEY));
    
    // Add Font Script
    CCMenuItem* font_script_on = CCMenuItemImage::create(getResPath(OPTIONS_BTN_FONT_SCRIPT_ON), getResPath(OPTIONS_BTN_FONT_SCRIPT_ON));
    CCMenuItem* font_script_off = CCMenuItemImage::create(getResPath(OPTIONS_BTN_FONT_SCRIPT_OFF), getResPath(OPTIONS_BTN_FONT_SCRIPT_OFF));
    btn_font_script = CCMenuItemToggle::createWithTarget(this, menu_selector(GameOptionsScene::gameFontStyleHandler), font_script_off, font_script_on, NULL);
    btn_font_script->setAnchorPoint(ccp(0, 0.5));
    btn_font_script->setPosition(ccp(winSize.width * 0.5 + PADDING_X * SCALEX, btn_font_print->getPositionY()));
    
    // Add Font Color
    CCMenuItem* font_color_back_off = CCMenuItemImage::create(getResPath(OPTIONS_BTN_FONTCOLOR_BLACK_OFF), getResPath(OPTIONS_BTN_FONTCOLOR_BLACK_OFF));
    CCMenuItemImage* font_color_black_on = CCMenuItemImage::create(getResPath(OPTIONS_BTN_FONTCOLOR_BLACK_ON), getResPath(OPTIONS_BTN_FONTCOLOR_BLACK_ON));
    btn_fontcolor_black = CCMenuItemToggle::createWithTarget(this, menu_selector(GameOptionsScene::gameFontColorHandler), font_color_back_off, font_color_black_on, NULL);
    
    CCMenuItem* font_color_white_off = CCMenuItemImage::create(getResPath(OPTIONS_BTN_FONTCOLOR_WHITE_OFF), getResPath(OPTIONS_BTN_FONTCOLOR_WHITE_OFF));
    CCMenuItemImage* font_color_white_on = CCMenuItemImage::create(getResPath(OPTIONS_BTN_FONTCOLOR_WHITE_ON), getResPath(OPTIONS_BTN_FONTCOLOR_WHITE_ON));
    btn_fontcolor_white = CCMenuItemToggle::createWithTarget(this, menu_selector(GameOptionsScene::gameFontColorHandler), font_color_white_off, font_color_white_on, NULL);
    
    CCMenuItem* font_color_pink_off = CCMenuItemImage::create(getResPath(OPTIONS_BTN_FONTCOLOR_PINK_OFF), getResPath(OPTIONS_BTN_FONTCOLOR_PINK_OFF));
    CCMenuItemImage* font_color_pink_on = CCMenuItemImage::create(getResPath(OPTIONS_BTN_FONTCOLOR_PINK_ON), getResPath(OPTIONS_BTN_FONTCOLOR_PINK_ON));
    btn_fontcolor_pink = CCMenuItemToggle::createWithTarget(this, menu_selector(GameOptionsScene::gameFontColorHandler), font_color_pink_off, font_color_pink_on, NULL);
    
    CCMenuItem* font_color_blue_off = CCMenuItemImage::create(getResPath(OPTIONS_BTN_FONTCOLOR_BLUE_OFF), getResPath(OPTIONS_BTN_FONTCOLOR_BLUE_OFF));
    CCMenuItemImage* font_color_blue_on = CCMenuItemImage::create(getResPath(OPTIONS_BTN_FONTCOLOR_BLUE_ON), getResPath(OPTIONS_BTN_FONTCOLOR_BLUE_ON));
    btn_fontcolor_blue = CCMenuItemToggle::createWithTarget(this, menu_selector(GameOptionsScene::gameFontColorHandler), font_color_blue_off, font_color_blue_on, NULL);
    
    btn_fontcolor_white->setTag(FONT_COLOR_WHITE);
    btn_fontcolor_black->setTag(FONT_COLOR_BLACK);
    btn_fontcolor_pink->setTag(FONT_COLOR_PINK);
    btn_fontcolor_blue->setTag(FONT_COLOR_BLUE);
    
    btn_fontcolor_white->setScale(SCALE);
    btn_fontcolor_black->setScale(SCALE);
    btn_fontcolor_pink->setScale(SCALE);
    btn_fontcolor_blue->setScale(SCALE);
    
    btn_fontcolor_black->setAnchorPoint(ccp(1, 0.5));
    btn_fontcolor_black->setPosition(ccp(winSize.width * 0.5, 224 * SCALEY));
    btn_fontcolor_white->setAnchorPoint(ccp(1, 0.5));
    btn_fontcolor_white->setPosition(ccp(winSize.width * 0.5 - btn_fontcolor_black->getContentSize().width * SCALE, 224 * SCALEY));
    btn_fontcolor_pink->setAnchorPoint(ccp(0, 0.5));
    btn_fontcolor_pink->setPosition(ccp(winSize.width * 0.5, 224 * SCALEY));
    btn_fontcolor_blue->setAnchorPoint(ccp(0, 0.5));
    btn_fontcolor_blue->setPosition(ccp(winSize.width * 0.5 + btn_fontcolor_pink->getContentSize().width * SCALE, 224 * SCALEY));
    
    CCMenu* fontcolorMenu = CCMenu::create(btn_fontcolor_white, btn_fontcolor_black, btn_fontcolor_pink, btn_fontcolor_blue, NULL);
    fontcolorMenu->setPosition(CCPointZero);
//    fontcolorMenu->alignItemsHorizontallyWithPadding(0);
//    fontcolorMenu->setContentSize(CCSize(winSize.width * 2, winSize.height));
    this->addChild(fontcolorMenu);
    
    btn_diff_normal->setScale(SCALE);
    btn_diff_hard->setScale(SCALE);
    btn_sound_on->setScale(SCALE);
    btn_sound_off->setScale(SCALE);
    btn_effect_on->setScale(SCALE);
    btn_effect_off->setScale(SCALE);
    btn_voice_boy->setScale(SCALE);
    btn_voice_girl->setScale(SCALE);
    
    btn_font_print->setScale(SCALE);
    btn_font_script->setScale(SCALE);

    CCMenu* menu_on = CCMenu::create(mainmenuItem,
                                     btn_diff_normal,   btn_diff_hard,
                                     btn_sound_on,      btn_sound_off,
                                     btn_effect_on,     btn_effect_off,
                                     btn_voice_boy,     btn_voice_girl,
                                     btn_font_print,    btn_font_script,
                                     NULL);
    menu_on->setPosition(CCPointZero);
    this->addChild(menu_on);
}

void GameOptionsScene::mainmenuHandler(cocos2d::CCObject *sender)
{
    SoundEffects::getInstance()->playButtonEffect();
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5,MainMenuScene::scene()));
}

void GameOptionsScene::initMenuVariables()
{
    // Init Difficulty
    if (options->getDifficulty() == 0) {
        btn_diff_normal->setSelectedIndex(1);
        btn_diff_hard->setSelectedIndex(0);
    }else
    {
        btn_diff_normal->setSelectedIndex(0);
        btn_diff_hard->setSelectedIndex(1);
    }
    // Init Sound
    if (SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() > 0) {
        btn_sound_on->setSelectedIndex(1);
        btn_sound_off->setSelectedIndex(0);
    }else
    {
        btn_sound_on->setSelectedIndex(0);
        btn_sound_off->setSelectedIndex(1);
    }
    // Init Effect
    if (SimpleAudioEngine::sharedEngine()->getEffectsVolume() > 0) {
        btn_effect_on->setSelectedIndex(1);
        btn_effect_off->setSelectedIndex(0);
    }else
    {
        btn_effect_on->setSelectedIndex(0);
        btn_effect_off->setSelectedIndex(1);
    }
    // Init Voice
    if (options->getPlayerType()) {
        btn_voice_boy->setSelectedIndex(1);
        btn_voice_girl->setSelectedIndex(0);
    }else
    {
        btn_voice_boy->setSelectedIndex(0);
        btn_voice_girl->setSelectedIndex(1);
    }
    
    // Init Font Style
    if (options->getFontType()) {
        btn_font_print->setSelectedIndex(1);
        btn_font_script->setSelectedIndex(0);
    }else
    {
        btn_font_print->setSelectedIndex(0);
        btn_font_script->setSelectedIndex(1);
    }
    
    // Init Font Color
    ccColor3B fontcolor = options->getLetterColor();
    if (compareColor(fontcolor, ccWHITE)) {
        selectFontColor(FONT_COLOR_WHITE);
    }else if (compareColor(fontcolor, ccBLACK))
    {
        selectFontColor(FONT_COLOR_BLACK);
    }else if (compareColor(fontcolor, ccPINK))
    {
        selectFontColor(FONT_COLOR_PINK);
    }else if (compareColor(fontcolor, ccBLUE))
    {
        selectFontColor(FONT_COLOR_BLUE);
    }
}

void GameOptionsScene::gameDiffHandler(cocos2d::CCObject *sender)
{
    SoundEffects::getInstance()->playButtonEffect();
    int diff = options->getDifficulty();
    if (diff == 0) {
        options->setDifficulty(1);
        btn_diff_normal->setSelectedIndex(0);
        btn_diff_hard->setSelectedIndex(1);
    }else
    {
        options->setDifficulty(0);
        btn_diff_normal->setSelectedIndex(1);
        btn_diff_hard->setSelectedIndex(0);
    }
    options->setCurrentLevel(0);
}

void GameOptionsScene::gameSoundHandler(cocos2d::CCObject *sender)
{
    SoundEffects::getInstance()->playButtonEffect();
    if (SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() > 0) {
        CCLog("Background Sound Button Pressed - Off");
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
        CCUserDefault::sharedUserDefault()->setBoolForKey(kMusic, false);
        btn_sound_on->setSelectedIndex(0);
        btn_sound_off->setSelectedIndex(1);
    }else
    {
        CCLog("Background Sound Button Pressed - On");
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1);
        CCUserDefault::sharedUserDefault()->setBoolForKey(kMusic, true);
        btn_sound_on->setSelectedIndex(1);
        btn_sound_off->setSelectedIndex(0);
    }
}

void GameOptionsScene::gameEffectHandler(cocos2d::CCObject *sender)
{
    SoundEffects::getInstance()->playButtonEffect();
    if (SimpleAudioEngine::sharedEngine()->getEffectsVolume() > 0) {
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
        CCUserDefault::sharedUserDefault()->setBoolForKey(kEffect, false);
        btn_effect_on->setSelectedIndex(0);
        btn_effect_off->setSelectedIndex(1);
    }else
    {
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(1);
        CCUserDefault::sharedUserDefault()->setBoolForKey(kEffect, true);
        btn_effect_on->setSelectedIndex(1);
        btn_effect_off->setSelectedIndex(0);
    }
}

void GameOptionsScene::gameVoiceHandler(cocos2d::CCObject *sender)
{
    // Init Voice
    SoundEffects::getInstance()->playButtonEffect();
    bool voice_type = options->getPlayerType();
    if (voice_type) {
        options->setPlayerType(false);
        btn_voice_boy->setSelectedIndex(0);
        btn_voice_girl->setSelectedIndex(1);
    }else
    {
        options->setPlayerType(true);
        btn_voice_boy->setSelectedIndex(1);
        btn_voice_girl->setSelectedIndex(0);
    }
}

void GameOptionsScene::gameFontStyleHandler(cocos2d::CCObject *sender)
{
    // Init Font Style
    SoundEffects::getInstance()->playButtonEffect();
    
    bool font_type = options->getFontType();
    if (font_type) {
        options->setFontType(false);
        btn_font_print->setSelectedIndex(0);
        btn_font_script->setSelectedIndex(1);
    }else
    {
        options->setFontType(true);
        btn_font_print->setSelectedIndex(1);
        btn_font_script->setSelectedIndex(0);
    }
    options->setCurrentLevel(0);
}

void GameOptionsScene::gameFontColorHandler(cocos2d::CCObject *sender)
{
    SoundEffects::getInstance()->playButtonEffect();
    int index = ((CCMenuItemToggle*)sender)->getTag();
    selectFontColor(index);
    
}

void GameOptionsScene::selectFontColor(int index)
{
    if (index >= NUM_COLOR_COUNT || index < FONT_COLOR_WHITE) {
        return;
    }
    switch (index) {
        case FONT_COLOR_WHITE:
            options->setLetterColor(ccWHITE);
            btn_fontcolor_white->setSelectedIndex(1);
            btn_fontcolor_white->setZOrder(100);
            btn_fontcolor_black->setSelectedIndex(0);
            btn_fontcolor_pink->setSelectedIndex(0);
            btn_fontcolor_blue->setSelectedIndex(0);
            break;
        case FONT_COLOR_BLACK:
            options->setLetterColor(ccBLACK);
            btn_fontcolor_white->setSelectedIndex(0);
            btn_fontcolor_black->setSelectedIndex(1);
            btn_fontcolor_pink->setSelectedIndex(0);
            btn_fontcolor_blue->setSelectedIndex(0);
            btn_fontcolor_black->setZOrder(100);
            break;
        case FONT_COLOR_PINK:
            options->setLetterColor(ccPINK);
            btn_fontcolor_white->setSelectedIndex(0);
            btn_fontcolor_black->setSelectedIndex(0);
            btn_fontcolor_pink->setSelectedIndex(1);
            btn_fontcolor_blue->setSelectedIndex(0);
            btn_fontcolor_pink->setZOrder(100);
            break;
        case FONT_COLOR_BLUE:
            options->setLetterColor(ccBLUE);
            btn_fontcolor_white->setSelectedIndex(0);
            btn_fontcolor_black->setSelectedIndex(0);
            btn_fontcolor_pink->setSelectedIndex(0);
            btn_fontcolor_blue->setSelectedIndex(1);
            btn_fontcolor_blue->setZOrder(100);
            break;
        default:
            break;
    }
}

bool GameOptionsScene::compareColor(ccColor3B first, ccColor3B second)
{
    if (first.r == second.r && first.g == second.g && first.b == second.b) {
        return true;
    }
    return false;
}