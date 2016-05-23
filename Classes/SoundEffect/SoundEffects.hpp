//
//  SoundEffects.hpp
//  AlephBet
//
//  Created by Fredric on 1/9/16.
//
//

#ifndef SoundEffects_hpp
#define SoundEffects_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameOptions.hpp"
#include "Const.h"

using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;

class SoundEffects{
private:
    static SoundEffects* sharedSoundEffects;
    string voiceName[LETTER_COUNT];
    int tick_index;
public:
    SoundEffects();
    ~SoundEffects();
    static SoundEffects* getInstance();
    void playLetterSound(int letterIndex);
    void playThemeBackgroundMusic();
    void playLevelBackgroundMusic();
    void stopBackgroundMusic();
    void muteBackgroundMusic();
    void playButtonEffect();
    void playTargetHit(ThrowThings item, bool wasGoodHit);
    void playLevelComplete(bool success);
    void playThrowItem();
    void playUnlockItem();
    void playGetCoin();
    void playTick();
    void playTickOne();
    void playAlarm();
    void preloadSounds();
    void pauseEffects();
    void resumeEffects();
};

#endif /* SoundEffects_hpp */
