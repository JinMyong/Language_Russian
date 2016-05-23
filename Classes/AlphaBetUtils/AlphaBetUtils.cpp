//
//  AlphaBetUtils.cpp
//  AlephBet
//
//  Created by Fredric on 12/16/15.
//
//

#include "AlphaBetUtils.hpp"
#include "GameOptions.hpp"

AlphaBetUtils* AlphaBetUtils::instance = NULL;

AlphaBetUtils* AlphaBetUtils::getInstance()
{
    if (instance == NULL) {
        instance = new AlphaBetUtils();
    }
    return instance;
}

AlphaBetUtils::AlphaBetUtils()
{
    setupLetterFontKeyMap_Print();
    setupLetterNameArray();
}

void AlphaBetUtils::setupLetterFontKeyMap_Print()
{
// Consonant
    letterFontKeyMap[0]  = "Б";     //
    letterFontKeyMap[1]  = "В";     //
    letterFontKeyMap[2]  = "Г";     //
    letterFontKeyMap[3]  = "Д";     //
    letterFontKeyMap[4]  = "Ж";     //
    letterFontKeyMap[5]  = "З";     //
    letterFontKeyMap[6]  = "Й";     //
    letterFontKeyMap[7]  = "К";     //
    letterFontKeyMap[8]  = "Л";     //
    letterFontKeyMap[9]  = "М";     //
    letterFontKeyMap[10] = "Н";     //
    letterFontKeyMap[11] = "П";     //
    letterFontKeyMap[12] = "Р";     //
    letterFontKeyMap[13] = "С";     //
    letterFontKeyMap[14] = "Т";     //
    letterFontKeyMap[15] = "Ф";     //
    letterFontKeyMap[16] = "Х";     //
    letterFontKeyMap[17] = "Ц";     //
    letterFontKeyMap[18] = "Ч";     //
    letterFontKeyMap[19] = "Ш";     //
    letterFontKeyMap[20] = "Щ";     //
// Vowel
    letterFontKeyMap[21] = "А";     //
    letterFontKeyMap[22] = "Е";     //
    letterFontKeyMap[23] = "Ё";     //
    letterFontKeyMap[24] = "И";     //
    letterFontKeyMap[25] = "О";     //
    letterFontKeyMap[26] = "У";     //
    letterFontKeyMap[27] = "Ъ";     //
    letterFontKeyMap[28] = "Ы";     //
    letterFontKeyMap[29] = "Ь";     //
    letterFontKeyMap[30] = "Э";     //
    letterFontKeyMap[31] = "Ю";     //
    letterFontKeyMap[32] = "Я";     //

}

void AlphaBetUtils::setupLetterNameArray()
{
// Consonant
    letterNames[0] =  "be";
    letterNames[1] =  "ve";
    letterNames[2] =  "ge";
    letterNames[3] =  "de";
    letterNames[4] =  "zhe";
    letterNames[5] =  "ze";
    letterNames[6] =  "ee kratkoye";
    letterNames[7] =  "ka";
    letterNames[8] =  "el";
    letterNames[9] =  "em";
    letterNames[10] = "en";
    letterNames[11] = "pe";
    letterNames[12] = "er";
    letterNames[13] = "es";
    letterNames[14] = "te";
    letterNames[15] = "ef";
    letterNames[16] = "kha";
    letterNames[17] = "tse";
    letterNames[18] = "che";
    letterNames[19] = "sha";
    letterNames[20] = "shcha";
// Vowel
    letterNames[21] = "a";
    letterNames[22] = "ye";
    letterNames[23] = "yo";
    letterNames[24] = "ee";
    letterNames[25] = "o";
    letterNames[26] = "oo";
    letterNames[27] = "tviordiy znak";
    letterNames[28] = "ih*";
    letterNames[29] = "myagkiy znak";
    letterNames[30] = "e";
    letterNames[31] = "yoo";
    letterNames[32] = "ya";
}

bool AlphaBetUtils::isSoundaAlikesVowel(int scrLetter, int compareLetter)
{
    bool isAlike = false;
    string scr_name = getLetterName(scrLetter);
    string com_name = getLetterName(compareLetter);
    if (scr_name == com_name) {
        isAlike = true;
    }
    return isAlike;
}

bool AlphaBetUtils::isVowel(int scrLetter)
{
    bool isVowel = false;
    if (scrLetter >= FIRST_VOWEL_IDX) {
        isVowel = true;
    }
    return isVowel;
}

string AlphaBetUtils::getLetterName(int index)
{
    string letterName;
    if (index < (sizeof(letterNames) / sizeof(letterNames[0]))) {
        letterName = letterNames[index];
    }else
    {
        letterName = "Not Found";
    }
    
    return letterName;
}

int AlphaBetUtils::getLetterIndex(string letterName)
{
    int index = 100000;
    for (int i = 0 ; i < (sizeof(letterNames) / sizeof(letterNames[0])); i++) {
        if (letterNames[i].compare(letterName)) {
            index = i;
        }
    }
    return index;
}

string AlphaBetUtils::getKeyMapFont(int index)
{
    string keyMap;
    int sz = sizeof(letterFontKeyMap) / sizeof(letterFontKeyMap[0]);
    if (index < sz) {
        keyMap = letterFontKeyMap[index];
    }else
    {
        keyMap = "Not Found";
    }
    
    return keyMap;
}