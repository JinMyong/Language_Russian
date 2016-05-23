//
//  Const.h
//  AlephBet
//
//  Created by Fredric on 12/15/15.
//
//

#ifndef Const_h
#define Const_h

#include "cocos2d.h"

#define SCALEX CCDirector::sharedDirector()->getWinSize().width / 640
#define SCALEY CCDirector::sharedDirector()->getWinSize().height / 1136
#define SCALE  MIN(SCALEX, SCALEY)

#define LETTER_COUNT    34
#define MAX_LEVEL       11

#define LETTER_FONT_SIZE_REG    70
#define LETTER_FONT_SIZE_VOWEL  56

#define MIN_LETTERS_TO_PLAY     3

#define ARROW_LEN               64
#define MAX_PIXELS_PER_SECOND   500

#define STD_HEADING_SIZE        32
#define GAME_INFO_FONT_SIZE     40
#define GAME_RESULT_FNTSIZE     40

#define FONT_LETTER_NOR                     "fonts/TimesNewRomanPSMT.ttf"              //"bwhebb"
#define FONT_LETTER_CUR                     "fonts/CIRPnova_D.ttf"
#define FONT_COMMON_STD                     "fonts/Dokchampa.ttf"
#define FONT_TITLE                          "fonts/TektonPro-Bold.ttf"

#define EMAIL_TEXT_SOCRE                    "Hi,\n\n I have been playing Alif Ba Ta Bullseye and here is my score."
#define EMAIL_TEXT_FRIEND                   "I thought you might like to see this app for learning the Alif Ba Ta. \n The app is called Alif Ba Ta Bullseye."
#define EMAIL_TEXT_MISSED                   "Here are the letters I am having trouble with."
#define WEBSITE_URL                         "http://www.tzedekamerica.org"

#define ANDROID_URL                         "https://play.google.com/store/apps/details?id=com.bullseye.alifbatabullseye"
#define IOS_URL                             "https://itunes.apple.com/us/app/russian-alphabet-bullseye/id1101090318?ls=1&mt=8"

#define CHAIR_BLUE_IMG                      "images/global/chair_blue.png"
#define CHAIR_YELLOW_IMG                    "images/global/chair_yellow.png"

#define MAINMENU_BACKGROUND_IMAGE           "images/global/mainmenu_bg.png"
#define MAINMENU_CHARACTER_BOY_IMG          "images/global/character_boy_main.png"
#define MAINMENU_PLAY_BTN_IMG_NOR           "images/global/btn_play_nor.png"
#define MAINMENU_PLAY_BTN_IMG_PRS           "images/global/btn_play_prs.png"
#define MAINMENU_CHOOSE_BTN_IMG_NOR         "images/mainmenuScene/btn_choose_nor.png"
#define MAINMENU_CHOOSE_BTN_IMG_PRS         "images/mainmenuScene/btn_choose_prs.png"
#define MAINMENU_OPTION_BTN_IMG_NOR         "images/mainmenuScene/btn_options_nor.png"
#define MAINMENU_OPTION_BTN_IMG_PRS         "images/mainmenuScene/btn_options_prs.png"
#define MAINMENU_HSCORE_BTN_IMG_NOR         "images/global/btn_highscore_nor.png"
#define MAINMENU_HSCORE_BTN_IMG_PRS         "images/global/btn_highscore_prs.png"
#define MAINMENU_BTN_STORE_IMG_NOR          "images/mainmenuScene/btn_store_nor.png"
#define MAINMENU_BTN_STORE_IMG_PRS          "images/mainmenuScene/btn_store_prs.png"
#define MAINMENU_BTN_RESET_IMG_NOR          "images/mainmenuScene/btn_reset_nor.png"
#define MAINMENU_BTN_RESET_IMG_PRS          "images/mainmenuScene/btn_reset_prs.png"
#define MAINMENU_ABOUT_BTN_IMG_NOR          "images/mainmenuScene/btn_about_nor.png"
#define MAINMENU_ABOUT_BTN_IMG_PRS          "images/mainmenuScene/btn_about_prs.png"
#define MAINMENU_TOP_TITLE_IMG              "images/mainmenuScene/mainmenu_top_title.png"
#define MAINMENU_BOTTOM_TITLE_IMG           "images/mainmenuScene/mainmenu_bottom_title.png"

#define INTRO_BACKGROUND_IMGAE              "images/global/main_bg.png"
#define INTRO_PLAY_BUTTON_IMAGE_NOR         "images/global/btn_play_nor.png"
#define INTRO_PLAY_BUTTON_IMAGE_PRS         "images/global/btn_play_prs.png"
#define INTRO_MAINMENU_BUTTON_IMAGE_NOR     "images/global/btn_mainmenu_nor.png"
#define INTRO_MAINMENU_BUTTON_IMAGE_PRS     "images/global/btn_mainmenu_prs.png"
#define INTRO_DESCRIPTION_IMG               "images/introScene/intro_text.png"
#define INTRO_DESCRIPTION_BG_IMG            "images/global/letterboard_bg.png"
#define INTRO_CHARACTER_IMG                 "images/introScene/character_boy_intro.png"

#define CHOOSE_LETTERSCENE_BACKROUND_IMG    "images/global/main_bg.png"
#define CHOOSE_LETTERBOARD_BG_IMG           "images/global/letterboard_bg.png"
#define CHOOSE_CHARACTER_IMG                "images/global/character_boy_choose.png"
#define CHOOSE_ALL_BTN_IMG_NOR              "images/chooseLetterScene/btn_all_nor.png"
#define CHOOSE_ALL_BTN_IMG_PRS              "images/chooseLetterScene/btn_all_prs.png"
#define CHOOSE_CLEAR_BTN_IMG_NOR            "images/chooseLetterScene/btn_clear_nor.png"
#define CHOOSE_CLEAR_BTN_IMG_PRS            "images/chooseLetterScene/btn_clear_prs.png"
#define CHOOSE_MAINMENU_IMG_NOR             "images/global/btn_mainmenu_nor.png"
#define CHOOSE_MAINMENU_IMG_PRS             "images/global/btn_mainmenu_prs.png"
#define CHOOSE_PLAY_IMG_NOR                 "images/global/btn_play_nor.png"
#define CHOOSE_PLAY_IMG_PRS                 "images/global/btn_play_prs.png"
#define CHOOSE_TITLE_IMG                    "images/chooseLetterScene/choose_top_title.png"

#define OPTIONS_BG_IMG                      "images/global/mainmenu_bg.png"
#define OPTIONS_BG_BLACK                    "images/global/letterboard_bg.png"
#define OPTIONS_TITLE_DIFFCULTY             "images/optionScene/title_difficult.png"
#define OPTIONS_TITLE_SOUND                 "images/optionScene/title_sound.png"
#define OPTIONS_TITLE_EFFECT                "images/optionScene/title_effect.png"
#define OPTIONS_TITLE_VOICE                 "images/optionScene/title_voice.png"
#define OPTIONS_title_fontSTYLE             "images/optionScene/title_font_style.png"
#define OPTIONS_title_fontCOLOR             "images/optionScene/title_text_color.png"
// Normal Button
#define OPTIONS_BTN_NORMAL_ON               "images/optionScene/normal_on.png"
#define OPTIONS_BTN_NORMAL_OFF              "images/optionScene/normal_off.png"
// Hard Button
#define OPTIONS_BTN_HARD_ON                 "images/optionScene/hard_on.png"
#define OPTIONS_BTN_HARD_OFF                "images/optionScene/hard_off.png"
// Background Music Button
#define OPTIONS_BTN_SOUND_ON_ON             "images/optionScene/sound_on_on.png"
#define OPTIONS_BTN_SOUND_ON_OFF            "images/optionScene/sound_on_off.png"
#define OPTIONS_BTN_SOUND_OFF_ON            "images/optionScene/sound_off_on.png"
#define OPTIONS_BTN_SOUND_OFF_OFF           "images/optionScene/sound_off_off.png"
// Sound Effect Button
#define OPTIONS_BTN_EFFECT_ON_ON            "images/optionScene/effect_on_on.png"
#define OPTIONS_BTN_EFFECT_ON_OFF           "images/optionScene/effect_on_off.png"
#define OPTIONS_BTN_EFFECT_OFF_ON           "images/optionScene/effect_off_on.png"
#define OPTIONS_BTN_EFFECT_OFF_OFF          "images/optionScene/effect_off_off.png"
// Voice Boy Button
#define OPTIONS_BTN_VOICE_BOY_ON            "images/optionScene/voice_boy_on.png"
#define OPTIONS_BTN_VOICE_BOY_OFF           "images/optionScene/voice_boy_off.png"
#define OPTIONS_BTN_VOICE_GIRL_ON           "images/optionScene/voice_girl_on.png"
#define OPTIONS_BTN_VOICE_GIRL_OFF          "images/optionScene/voice_girl_off.png"
// Font Print Button
#define OPTIONS_BTN_FONT_PRINT_ON           "images/optionScene/font_print_on.png"
#define OPTIONS_BTN_FONT_PRINT_OFF          "images/optionScene/font_print_off.png"
#define OPTIONS_BTN_FONT_SCRIPT_ON          "images/optionScene/font_script_on.png"
#define OPTIONS_BTN_FONT_SCRIPT_OFF         "images/optionScene/font_script_off.png"
// MainMenu Button
#define OPTIONS_BTN_MAINMENU_NOR            "images/global/btn_mainmenu_nor.png"
#define OPTIONS_BTN_MAINMENU_PRS            "images/global/btn_mainmenu_prs.png"
// Font color
#define OPTIONS_BTN_FONTCOLOR_WHITE_OFF     "images/optionScene/font_color_white_off.png"
#define OPTIONS_BTN_FONTCOLOR_BLACK_OFF     "images/optionScene/font_color_black_off.png"
#define OPTIONS_BTN_FONTCOLOR_PINK_OFF      "images/optionScene/font_color_pink_off.png"
#define OPTIONS_BTN_FONTCOLOR_BLUE_OFF      "images/optionScene/font_color_blue_off.png"
#define OPTIONS_BTN_FONTCOLOR_WHITE_ON      "images/optionScene/font_color_white_on.png"
#define OPTIONS_BTN_FONTCOLOR_BLACK_ON      "images/optionScene/font_color_black_on.png"
#define OPTIONS_BTN_FONTCOLOR_PINK_ON       "images/optionScene/font_color_pink_on.png"
#define OPTIONS_BTN_FONTCOLOR_BLUE_ON       "images/optionScene/font_color_blue_on.png"

#define HSCORE_BG_IMG                       "images/global/mainmenu_bg.png"
#define HSCORE_BTN_MAINMENU_IMG_NOR         "images/global/btn_mainmenu_nor.png"
#define HSCORE_BTN_MAINMENU_IMG_PRS         "images/global/btn_mainmenu_prs.png"
#define HSCORE_BTN_SENDEMAIL_IMG_NOR        "images/highScoreScene/btn_email_teacher_nor.png"
#define HSCORE_BTN_SENDEMAIL_IMG_PRS        "images/highScoreScene/btn_email_teacher_prs.png"
#define HSCORE_TITLE_TXT_IMG                "images/highScoreScene/title_highscore.png"
#define HSCORE_CHARACTER_IMG                "images/global/character_boy_choose.png"
#define HSCORE_LETTER_BG_IMG                "images/global/letterboard_bg.png"

#define STORE_BG_IMG                        "images/global/main_bg.png"
#define STORE_TABLE_IMG                     "images/storeScene/table.png"
#define STORE_TITLE_IMG                     "images/storeScene/title_shuk.png"
#define STORE_TABLE_BULB_ON                 "images/storeScene/table_bulb_on.png"
#define STORE_TABLE_BULB_OFF                "images/storeScene/table_bulb_off.png"
#define STORE_TABLE_FISH_ON                 "images/storeScene/table_fish_on.png"
#define STORE_TABLE_FISH_OFF                "images/storeScene/table_fish_off.png"
#define STORE_TABLE_AIRPLANE_ON             "images/storeScene/table_airplane_on.png"
#define STORE_TABLE_AIRPLANE_OFF            "images/storeScene/table_airplane_off.png"
#define STORE_TABLE_EGG_ON                  "images/storeScene/table_egg_on.png"
#define STORE_TABLE_EGG_OFF                 "images/storeScene/table_egg_off.png"
#define STORE_TABLE_BALLOON_ON              "images/storeScene/table_balloon_on.png"
#define STORE_TABLE_BALLOON_OFF             "images/storeScene/table_balloon_off.png"
#define STORE_TABLE_PENCIL_ON               "images/storeScene/table_pencil_on.png"
#define STORE_TABLE_PENCIL_OFF              "images/storeScene/table_pencil_off.png"
#define STORE_MAINMENU_IMG_NOR              "images/global/btn_mainmenu_nor.png"
#define STORE_MAINMENU_IMG_PRS              "images/global/btn_mainmenu_prs.png"

#define ABOUT_BG_IMG                        "images/global/main_bg.png"
#define ABOUT_BTN_MAINMENU_IMG_NOR          "images/global/btn_mainmenu_nor.png"
#define ABOUT_BTN_MAINMENU_IMG_PRS          "images/global/btn_mainmenu_prs.png"
#define ABOUT_BTN_EMAIL_IMG_NOR             "images/aboutScene/btn_email_nor.png"
#define ABOUT_BTN_EMAIL_IMG_PRS             "images/aboutScene/btn_email_prs.png"
#define ABOUT_BTN_LINK_IMG_NOR              "images/aboutScene/btn_link_nor.png"
#define ABOUT_BTN_LINK_IMG_PRS              "images/aboutScene/btn_link_prs.png"
#define ABOUT_TITLE_SCENE_IMG               "images/aboutScene/title_about.png"
#define ABOUT_TITLE_GAME_IMG                "images/aboutScene/title_about_game.png"
#define ABOUT_TEXT_GAME                     "images/aboutScene/txt_game.png"
#define ABOUT_TEXT_BG_IMG                   "images/global/letterboard_bg.png"
#define ABOUT_CHARACTER_IMG                 "images/global/character_boy_main.png"

#define GAMESCENE_BACKROUND_IMG             "images/global/main_bg.png"
#define GAMESCENE_LETTER_BG_IMG             "images/gameScene/game_letter_bg.png"
#define GAME_DIFF_HIT_IMG                   "images/gameScene/diff_hint.png"
#define GAME_TARGET_IMG                     "images/gameScene/target.png"
#define GAME_BTN_PAUSE_IMAGE_NOR            "images/gameScene/btn_pause_nor.png"
#define GAME_BTN_PAUSE_IMAGE_PRS            "images/gameScene/btn_pause_prs.png"
#define GAME_BTN_CONTINUE_IMAGE_NOR         "images/gameScene/btn_continue_nor.png"
#define GAME_BTN_CONTINUE_IMAGE_PRS         "images/gameScene/btn_continue_prs.png"
#define GAME_BTN_QUIT_IMAGE_NOR             "images/gameScene/btn_quit_nor.png"
#define GAME_BTN_QUIT_IMAGE_PRS             "images/gameScene/btn_quit_nor.png"

#define GAMERESULT_BG_IMG                   "images/global/main_bg.png"
#define GAMERESULT_BTN_MAINMENU_NOR         "images/global/btn_mainmenu_nor.png"
#define GAMERESULT_BTN_MAINMENU_PRS         "images/global/btn_mainmenu_prs.png"
#define GAMERESULT_BTN_RESTART_NOR          "images/gameResultScene/btn_restart_nor.png"
#define GAMERESULT_BTN_RESTART_PRS          "images/gameResultScene/btn_restart_prs.png"
#define GAMERESULT_BTN_CONTINUE_NOR         "images/gameResultScene/btn_next_nor.png"
#define GAMERESULT_BTN_CONTINUE_PRS         "images/gameResultScene/btn_next_prs.png"
#define GAMERESULT_BTN_SENDEMAIL_IMG_NOR    "images/gameResultScene/btn_email_teacher_nor.png"
#define GAMERESULT_BTN_SENDEMAIL_IMG_PRS    "images/gameResultScene/btn_email_teacher_prs.png"
#define GAMERESULT_BTN_MISEED_IMG_NOR       "images/gameResultScene/btn_missedletter_nor.png"
#define GAMERESULT_BTN_MISEED_IMG_PRS       "images/gameResultScene/btn_missedletter_prs.png"
#define GAMERESULT_BG_TXT_IMG               "images/global/letterboard_bg.png"
#define GAMERESULT_CHARACTER_BOY_IMG        "images/global/character_boy_choose.png"
#define GAMERESULT_COIN_IMG                 "images/global/coins.png"

#define MISSEDLETTER_BTN_BACK_NOR           "images/missedLetterScene/btn_back_nor.png"
#define MISSEDLETTER_BTN_BACK_PRS           "images/missedLetterScene/btn_back_prs.png"
#define MISSEDLETTER_BTN_EMAIL_NOR          "images/gameResultScene/btn_email_teacher_nor.png"
#define MISSEDLETTER_BTN_EMAIL_PRS          "images/gameResultScene/btn_email_teacher_prs.png"
#define MISSEDLETTER_BTN_MENU_NOR           "images/global/btn_mainmenu_nor.png"
#define MISSEDLETTER_BTN_MENU_PRS           "images/global/btn_mainmenu_prs.png"

#define EFFECT_BULB_HIT                     "sounds/effect/bulb_hit.mp3"
#define EFFECT_BULB_MISS                    "sounds/effect/bulb_miss.mp3"
#define EFFECT_BUTTON                       "sounds/effect/button.mp3"
#define EFFECT_FISH_HIT                     "sounds/effect/fish_hit.mp3"
#define EFFECT_FISH_MISS                    "sounds/effect/fish_miss.mp3"
#define EFFECT_GET_COIN                     "sounds/effect/get_coin.mp3"
#define EFFECT_LEVEL_COMPLETE               "sounds/effect/level_complete.mp3"
#define EFFECT_LEVEL_FAILED                 "sounds/effect/level_failed.mp3"
#define EFFECT_MATZAHBALL_HIT               "sounds/effect/matzahball_hit.mp3"
#define EFFECT_MATZAHBALL_MISS              "sounds/effect/matzahball_miss.mp3"
#define EFFECT_MATZAH_HIT                   "sounds/effect/matzah_hit.mp3"
#define EFFECT_MATZAH_MISS                  "sounds/effect/matzah_miss.mp3"
#define EFFECT_PENCIL_HIT                   "sounds/effect/pencil_hit.mp3"
#define EFFECT_PENCIL_MISS                  "sounds/effect/pencil_miss.mp3"
#define EFFECT_STAR_HIT                     "sounds/effect/star_hit.mp3"
#define EFFECT_STAR_MISS                    "sounds/effect/star_miss.mp3"
#define EFFECT_THROW_ITEM                   "sounds/effect/throw_item.mp3"
#define EFFECT_UNLOCK_ITEM                  "sounds/effect/unlock_item.mp3"
#define EFFECT_TICK                         "sounds/effect/tick.mp3"
#define EFFECT_TICK_ONE                     "sounds/effect/tick_one.mp3"
#define EFFECT_ALARM                        "sounds/effect/alarm.mp3"
#define BG_MUSIC_THEME                      "sounds/music/bg_music_1.mp3"
#define BG_MUSIC_LEVEL_NAME                 "sounds/music/bg_music_"

#define TARGET_AREA_PAD         30 * SCALE
#define TARGET_AREA_Y_OFFSET    200 * SCALE

#define KEY_PLAY_COMPLETE       "PLAY_COMPLETEEFFECT"

#define kMusic                  "BG_MUSIC"
#define kEffect                 "SOUND_EFFECT"

#define TXT_MAIN_TOPTITLE       "Ready, Set..."
#define TXT_MAIN_BOTTOMTITLE    "Russian AlphaBet Bullseye"
#define TXT_CHOOSE_TITLE        "Choose the letters you want to learn."
#define TXT_STORE_TITLE         "Welcome to Store"
#define TXT_OPTION_TITLE        "Options"
#define TXT_ABOUUT_TITLE        "Ready, Set, Russian AlphaBet Bullseye"

#define COLOR_PAL_HIGHLIGHT     ccc3(0xFF, 0xE2, 0x00)
#define COLOR_TITLE_TOP         ccc3(127, 180, 213)
#define COLOR_TITLE_BOTTOM      ccc3(213, 194, 127)

#endif /* Const_h */
