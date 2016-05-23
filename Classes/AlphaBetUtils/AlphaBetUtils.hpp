//
//  AlphaBetUtils.hpp
//  AlephBet
//
//  Created by Fredric on 12/16/15.
//
//

#ifndef AlphaBetUtils_hpp
#define AlphaBetUtils_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

#define NUM_LETTERS_IDX         33
#define FIRST_VOWEL_IDX         21
#define LAST_CONSONANT_IDX      20

class AlphaBetUtils
{
private:
    static AlphaBetUtils* instance;
    string letterNames[34];
    string letterFontKeyMap[34];
    CCArray* soundAlikes;
    
public:
    AlphaBetUtils();
    ~AlphaBetUtils();
    static  AlphaBetUtils*    getInstance();
    
    string   getLetterName(int index);
    string   getKeyMapFont(int index);
    int      getLetterIndex(string letterName);
    
    void     setupLetterFontKeyMap_Print();
    void     setupLetterNameArray();
    void     setupSoundAlikes();
    
    bool     isSoundaAlikesVowel(int scrLetter, int compareLetter);
    bool     isVowel(int scrLetter);
};

#endif /* AlphaBetUtils_hpp */
