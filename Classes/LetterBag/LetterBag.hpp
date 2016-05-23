//
//  LetterBag.hpp
//  AlephBet
//
//  Created by Fredric on 12/23/15.
//
//

#ifndef LetterBag_hpp
#define LetterBag_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Const.h"

#define NO_REPEAT_INDEX_FIRST_TIME  -1
#define KEY_COUNT       "COUNT"
#define KEY_VALUE       "LETTER_"

using namespace cocos2d;
using namespace std;

class LetterBag {
private:
    static LetterBag* instance;
    CCArray* bagOfLetter;
    CCArray* bagOfMissedLetter;
    int numLetterChoosen;
    int noRepeatIndex;
public:
    LetterBag();
    ~LetterBag();
    static LetterBag* getInstance();
    
    int getLetterCountInBag();
    bool addLetter(int letterIndex);
    bool removeLetter(int letterIndex);
    void removeAllLetters();
    
    bool verifyLetterCount();
    bool letterInBag(int letterIndex);
    
    CCArray* getRandomLettersFromAlephBet(int numLetters, int excludeLetter);

    int getRandomLetterFormBagLimitRepeats();
    
    void shuffleBagOffLetters();
    void logAllLettersInBag();
    void syncDefaultLetters();
    void getDefaultLetters();
    
// Add Functions
    bool addMissedLetter(int letterIndex);
    CCArray* getMissedLetters();
};

#endif /* LetterBag_hpp */
