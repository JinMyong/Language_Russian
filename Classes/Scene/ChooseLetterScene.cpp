//
//  ChooseLetterScene.cpp
//  AlephBet
//
//  Created by Fredric on 12/16/15.
//
//

#include "ChooseLetterScene.hpp"
#include "MainMenuScene.hpp"
#include "AlphaBetUtils.hpp"
#include "LetterBag.hpp"
#include "SoundEffects.hpp"
#include "GameOptions.hpp"
#include "IntroScene.hpp"

#include "Const.h"

void ChooseLetterScene::stringToUpper(string &s)
{
    for(unsigned int l = 0; l < s.length(); l++)
    {
        s[l] = toupper(s[l]);
    }
}

CCScene* ChooseLetterScene::scene()
{
    CCScene* scene = CCScene::create();
    ChooseLetterScene* layer = ChooseLetterScene::create();
    scene->addChild(layer);
    return scene;
}

bool ChooseLetterScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    options = GameOptions::getInstance();
    createUI();
    
    this->setTouchEnabled(true);
    
    return true;
}

void ChooseLetterScene::createUI()
{
    // Add background
    CCSprite* background = CCSprite::create(getResPath(CHOOSE_LETTERSCENE_BACKROUND_IMG));
    background->setScaleX(SCALEX);
    background->setScaleY(SCALEY);
    background->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    this->addChild(background, BG_ZORDER);
    
    // Add top title("choose ")
    CCLabelTTF* top_title = CCLabelTTF::create(TXT_CHOOSE_TITLE, FONT_TITLE, 40 * SCALE);
    top_title->setPosition(ccp(winSize.width * 0.5, 1090 * SCALEY));
    top_title->setColor(COLOR_TITLE_TOP);
    this->addChild(top_title);
    
    // Add yellow chair
    CCSprite* chair_yellow = CCSprite::create(getResPath(CHAIR_YELLOW_IMG));
    chair_yellow->setScale(SCALE * 0.9);
    chair_yellow->setPosition(ccp(506 * SCALEX, 278 * SCALEY));
    this->addChild(chair_yellow, YC_ZORDER);
    
    // Add Blue Chair
    CCSprite* chair_blue = CCSprite::create(getResPath(CHAIR_BLUE_IMG));
    chair_blue->setScale(SCALE * 0.9);
    chair_blue->setPosition(ccp(104 * SCALEX, 200 * SCALEY));
    this->addChild(chair_blue, BC_ZORDER);
    
    // Add Character
    CCSprite* character = CCSprite::create(getResPath(CHOOSE_CHARACTER_IMG));
    character->setScale(SCALE * 0.9);
    character->setPosition(ccp(150 * SCALEX, 295 * SCALEY));
    this->addChild(character, CH_ZORDER);
    
    createLetterBoard();
    createMenu();
}

void ChooseLetterScene::createLetterBoard()
{
    // Add letterboard background image
    CCSprite* letterboard_bg = CCSprite::create(getResPath(CHOOSE_LETTERBOARD_BG_IMG));
    letterboard_bg->setScaleX(SCALEX);
    letterboard_bg->setScaleY(SCALEY);
    letterboard_bg->setPosition(ccp(winSize.width * 0.5, 592 * SCALEY));
    this->addChild(letterboard_bg, LB_ZORDER);
    
    AlphaBetUtils* AlphaBetUtils = AlphaBetUtils::getInstance();
    LetterBag* letterbag = LetterBag::getInstance();
            
    int vowelRowCount = 0;  // Count rows of vowels to offset ther secont row of vowels a little
    
    int fontSize = 60 * SCALE;
    
    CCLog("Scale is %f", SCALE);
    
    // Make 6 wide by 7 high grid
    
    int yIndex = -1;    // start with -1. It will get increment the first pass through
    int xIndex = 0;
    
    float factor = 1.0;     // For letter row space
    string fontName;
    bool fontType = GameOptions::getInstance()->getFontType();
    if (fontType) {
        fontName = FONT_LETTER_NOR;
        factor = 1.2;
    }else
    {
        fontName = FONT_LETTER_CUR;
        factor = 1.2;
    }
    
    for (int letterIndex = 0; letterIndex < LETTER_COUNT; letterIndex++) {
        if (xIndex % NUM_COLUMNS == 0) {
            yIndex++;
            xIndex = 0;
            
            // Count vowel rows for special offset
            if (letterIndex > LAST_CONSONANT_IDX) {
                vowelRowCount++;
            }
        }
        
        string letterString = AlphaBetUtils->getKeyMapFont(letterIndex);
        
        CCLabelTTF* letterSprite = CCLabelTTF::create(letterString.c_str(), fontName.c_str(), fontSize);
        letterSprite->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
        letterSprite->setHorizontalAlignment(kCCTextAlignmentCenter);
        letterSprite->setDimensions(CCSize(fontSize * 1.3, fontSize * 1.5));
        
        if (letterbag->letterInBag(letterIndex)) {
            // TODO show cool selected sprite
            letterSprite->setOpacity(0x80);
        }
        
        CCSize targetSize = letterSprite->getContentSize();
        targetSize.height *= 0.75;
        
        int colSpace = (winSize.width - (2 * LETTER_BOARD_OFFSET_X * MIN(SCALEX, SCALEY))) / (NUM_COLUMNS);
        int xPos = LETTER_BOARD_OFFSET_X  * MIN(SCALEX, SCALEY) + (xIndex * colSpace) + (colSpace * 0.5);
        int yPos = winSize.height - LETTER_BOARD_OFFSET_Y * MIN(SCALEX, SCALEY) - (yIndex * targetSize.height * factor) - (targetSize.height * 0.5) - (94 * MIN(SCALEX, SCALEY));
        
        // If this is the second row of vowels, lower it a little
        if (vowelRowCount >= 1) {
            yPos -= VOWEL_ROW_OFFSET;
        }
        
        letterSprite->setPosition(ccp(xPos, yPos));
        this->addChild(letterSprite, LETTER_BOARD_Z, letterIndex);
        
        // Little back to start a new row for the vowels
        if (letterIndex == LAST_CONSONANT_IDX) {
            xIndex = 0;
        }else
        {
            // Normal case
            xIndex++;
        }
    }
}

void ChooseLetterScene::createMenu()
{
    CCMenuItem* select_all_item = CCMenuItemImage::create(getResPath(CHOOSE_ALL_BTN_IMG_NOR), getResPath(CHOOSE_ALL_BTN_IMG_PRS), this, menu_selector(ChooseLetterScene::selectAllHandle));
    select_all_item->setScale(SCALE * 0.9);
    select_all_item->setPosition(460 * SCALEX, 366 * SCALEY);
    
    CCMenuItem* select_clear_item = CCMenuItemImage::create(getResPath(CHOOSE_CLEAR_BTN_IMG_NOR), getResPath(CHOOSE_CLEAR_BTN_IMG_PRS), this, menu_selector(ChooseLetterScene::selectClearHandle));
    select_clear_item->setScale(SCALE * 0.9);
    select_clear_item->setPosition(460 * SCALEX, 278 * SCALEY);
    
    isGotoGameScene = GameOptions::getInstance()->getGotoPlayScene();
    CCMenuItem* mainmenuItem;
    CCMenu* menu;
    if (isGotoGameScene) {
        mainmenuItem = CCMenuItemImage::create(getResPath(CHOOSE_PLAY_IMG_NOR), getResPath(CHOOSE_PLAY_IMG_PRS), this, menu_selector(ChooseLetterScene::gotoMainMenu));
        menu = CCMenu::create(select_all_item, select_clear_item, mainmenuItem, NULL);
    }else
    {
        CCMenuItem* select_play_item = CCMenuItemImage::create(getResPath(CHOOSE_PLAY_IMG_NOR), getResPath(CHOOSE_PLAY_IMG_PRS), this, menu_selector(ChooseLetterScene::selectPlayHandele));
        select_play_item->setScale(SCALE * 0.9);
        select_play_item->setPosition(ccp(460 * SCALEX, 190 * SCALEY));
        mainmenuItem = CCMenuItemImage::create(getResPath(CHOOSE_MAINMENU_IMG_NOR), getResPath(CHOOSE_MAINMENU_IMG_PRS), this, menu_selector(ChooseLetterScene::gotoMainMenu));
        menu = CCMenu::create(select_all_item, select_clear_item, select_play_item, mainmenuItem, NULL);
    }
    
    mainmenuItem->setScale(SCALE * 0.9);
    mainmenuItem->setPosition(winSize.width * 0.5 + 50 * SCALEX, 90 * SCALEY);

    menu->setPosition(CCPointZero);
    this->addChild(menu, MN_ZORDER);
}

void ChooseLetterScene::selectAllHandle(cocos2d::CCObject *sender)
{
    options->setCurrentLevel(0);
    CCLOG("Select All Letters on ChooseLetterScene");
    SoundEffects::getInstance()->playButtonEffect();
    selectAllLetters();
}

void ChooseLetterScene::selectClearHandle(cocos2d::CCObject *sender)
{
    options->setCurrentLevel(0);
    CCLOG("Clear All Letters on ChooseLetterScene");
    SoundEffects::getInstance()->playButtonEffect();
    unselectAllLetters();
}

void ChooseLetterScene::gotoMainMenu(cocos2d::CCObject *sender)
{
    CCLOG("Go to MainMenu from ChooseLetterScene");
    
    CCLog("%d Letters selected", LetterBag::getInstance()->getLetterCountInBag());
    
    SoundEffects::getInstance()->playButtonEffect();
    
    if (verifyEnoughLetters()) {
        if (isGotoGameScene) {
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, IntroScene::scene()));
        }else{
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, MainMenuScene::scene()));
        }
    }
    
}

void ChooseLetterScene::selectPlayHandele(cocos2d::CCObject *sender)
{
    SoundEffects::getInstance()->playButtonEffect();
    if (verifyEnoughLetters()) {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5, IntroScene::scene()));
    }
}

void ChooseLetterScene::letterSpriteSelected(cocos2d::CCLabelTTF *letterSprite)
{
    options->setCurrentLevel(0);
    
    int tag = letterSprite->getTag();
    
    // If the sprite running an action, ignore the selection.
    if (letterSprite->numberOfRunningActions() > 0) {
        return;
    }
    
    AlphaBetUtils* AlphaBetUtils = AlphaBetUtils::getInstance();
    LetterBag* letterbag = LetterBag::getInstance();
    
    // Get the "Name" of the letter
    string letterName = AlphaBetUtils->getLetterName(tag);
        
    // Check if the letter was already selected or not
    if (letterbag->letterInBag(tag))
    {
        // Already chosen. Remove it from the set
        CCLog("%s at index %d was unchosen", letterName.c_str(), tag);
        
        // Remove it
        if (letterbag->removeLetter(tag)) {
            // TODO do cool sprite animation to un-select sprite
            letterSprite->setOpacity(0xFF);
            // Run Action
            letterSprite->runAction(this->getSelectedAction());
        }
        
        // Clear the last letter display
        this->clearLastLetter();
    }
    else
    {
        // Add the letter to the set
        CCLog("%s at index %d was chosen", letterName.c_str(), tag);
        
        // Add Letter
        if (letterbag->addLetter(tag)) {
            // TODO do cool sprite animation to un-select sprite
            letterSprite->setOpacity(0x80);
            // Run Action
            letterSprite->runAction(this->getSelectedAction());
            // Display Letter
            this->displayLastLetter(tag);
            // Play Announcement of Letter
            SoundEffects::getInstance()->playLetterSound(tag);
        }
    }
}

void ChooseLetterScene::selectAllLetters()
{
    LetterBag* letterBag = LetterBag::getInstance();
    // Walk through each letter and select each one thet is not already selected.
    for (int letterIndex = 0; letterIndex < NUM_LETTERS_IDX; letterIndex++) {
        // Check if the letter was already selected or not
        if (!letterBag->letterInBag(letterIndex)) {
            // Add letter
            if (letterBag->addLetter(letterIndex)) {
                // Get the sprite by tag
                CCLabelTTF* lettersprite = (CCLabelTTF*)this->getChildByTag(letterIndex);
                
                lettersprite->setOpacity(0x80);
                
                // Run Action
                lettersprite->runAction(this->getSelectedAction());

            }
        }
    }
    
    // Clear the last letter display
    this->clearLastLetter();
}

void ChooseLetterScene::unselectAllLetters()
{
    LetterBag* letterBag = LetterBag::getInstance();
    // Walk through each letter and select each one thet is not already selected.
    for (int letterIndex = 0; letterIndex < NUM_LETTERS_IDX; letterIndex++) {
        // Check if the letter was already selected or not
        if (letterBag->letterInBag(letterIndex)) {
            // Add letter
            if (letterBag->removeLetter(letterIndex)) {
                // Get the sprite by tag
                CCLabelTTF* lettersprite = (CCLabelTTF*)this->getChildByTag(letterIndex);
                
                lettersprite->setOpacity(0xFF);
                
                // Run Action
                lettersprite->runAction(this->getSelectedAction());
                
            }
        }
    }
    
    letterBag->removeAllLetters();
    
    // Clear the last letter display
    this->clearLastLetter();
    
}

CCAction* ChooseLetterScene::getSelectedAction()
{
    float scale = 1.5;
    float duration = 0.125;
    
    CCScaleBy* grow = CCScaleBy::create(duration, scale);
    CCScaleBy* shrink = CCScaleBy::create(duration, 1.0 / scale);
    
    CCSequence* composite = CCSequence::create(grow, shrink, NULL);
    
    return composite;
}

bool ChooseLetterScene::verifyEnoughLetters()
{
    bool enough = LetterBag::getInstance()->verifyLetterCount();
    if (!enough) {
        string title = "Not Enough Letters";
        string message = "Please choose at least 3 letters to play.";
        CCMessageBox(message.c_str(), title.c_str());
    }    
    return enough;
}

void ChooseLetterScene::displayLastLetter(int lastLetterIndex)
{
//    const int yOffset = 450 * SCALEY;
    
    // Store the last letter
    lastLetterChosen = lastLetterIndex;
    
    // Get the "name" of the letter
    string letterName = AlphaBetUtils::getInstance()->getLetterName(lastLetterIndex);
    stringToUpper(letterName);
    this->removeChild(lastLetterLabel, true);
    
    // Create and initialize a Label
    lastLetterLabel = CCLabelTTF::create(letterName.c_str(), FONT_COMMON_STD, 40 * SCALE);
    
    // Position the label on the center of the screen
    lastLetterLabel->setPosition(ccp(450 * SCALEX, 450 * SCALEY));
    
    // Color
    lastLetterLabel->setColor(COLOR_PAL_HIGHLIGHT);
    
    // Add the label as a child to this Layer
    this->addChild(lastLetterLabel, LL_ZORDER);
}

void ChooseLetterScene::clearLastLetter()
{
    this->removeChild(lastLetterLabel, true);
}

void ChooseLetterScene::testCursive()
{
    GameOptions::getInstance()->setFontType(!testCur);
}

void ChooseLetterScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCTouch* fingerOne = (CCTouch*)pTouches->anyObject();
    CCPoint pointOne = CCDirector::sharedDirector()->convertToUI(fingerOne->getLocationInView());
    CCPoint location = this->convertToNodeSpace(pointOne);
    
//    CCLog("Touch Pos(%f, %f)", location.x, location.y);
    
    // Loop though all letter board and check if one was touched.
    for (int letterIndex = 0; letterIndex < NUM_LETTERS_IDX; letterIndex++)
    {
        // Get the sprite by Tag (index)
        CCLabelTTF* letterSprite = (CCLabelTTF*)this->getChildByTag(letterIndex);
        
        // Get the box of the sprite
        CCRect rect = letterSprite->boundingBox();
        
        // Touch point in the box?
        if (rect.containsPoint(location)) {
            this->letterSpriteSelected(letterSprite);
            CCLog("Toched %d", letterIndex);
            break;
        }
    }
}