//
//  LetterBag.cpp
//  AlephBet
//
//  Created by Fredric on 12/23/15.
//
//

#include "LetterBag.hpp"
#include "AlphaBetUtils.hpp"
#include "Const.h"

LetterBag* LetterBag::instance = NULL;

LetterBag* LetterBag::getInstance(){
    if (instance == NULL) {
        instance = new LetterBag();
    }    
    return instance;
}

LetterBag::LetterBag()
{
    bagOfLetter = CCArray::create();
    bagOfLetter->retain();
    bagOfMissedLetter = CCArray::create();
    bagOfMissedLetter->retain();
    
    numLetterChoosen = 0;
    
    this->getDefaultLetters();
    
    noRepeatIndex = NO_REPEAT_INDEX_FIRST_TIME;

    srandom((int)time(NULL));
    
}

int LetterBag::getLetterCountInBag()
{
    return numLetterChoosen;
}

bool LetterBag::addLetter(int letterIndex)
{
    noRepeatIndex = NO_REPEAT_INDEX_FIRST_TIME;
    
    bool success = false;
    CCInteger* letterNumber = CCInteger::create(letterIndex);
    if (!letterInBag(letterIndex)) {
        bagOfLetter->addObject(letterNumber);
        success = true;
    }
    this->syncDefaultLetters();
    return success;
}

bool LetterBag::removeLetter(int letterIndex)
{
    noRepeatIndex = NO_REPEAT_INDEX_FIRST_TIME;
    bool success = false;
    if (letterInBag(letterIndex)) {
        for (int i = 0; i < bagOfLetter->count(); i++) {
            CCInteger* v_object = (CCInteger*)bagOfLetter->objectAtIndex(i);
            if (v_object->getValue() == letterIndex) {
                bagOfLetter->removeObjectAtIndex(i);
                break;
            }
        }
        success = true;
    }
    this->syncDefaultLetters();
    return success;
}

void LetterBag::removeAllLetters()
{
    noRepeatIndex = NO_REPEAT_INDEX_FIRST_TIME;
    bagOfLetter->removeAllObjects();
    this->syncDefaultLetters();
}

bool LetterBag::verifyLetterCount()
{
    bool enough = true;
    
    if (numLetterChoosen < MIN_LETTERS_TO_PLAY) {
        CCLog("Too few letters in bag.");
        enough = false;
    }
    
    return enough;
}

bool LetterBag::letterInBag(int letterIndex)
{
    bool exist = false;
    
    for (int i = 0; i < bagOfLetter->count(); i++) {
        CCInteger* v_object = (CCInteger*)bagOfLetter->objectAtIndex(i);
        if (v_object->getValue() == letterIndex) {
            exist = true;
            break;
        }
    }
    
    return exist;
}

int LetterBag::getRandomLetterFormBagLimitRepeats()
{
    // If it's the first time, suffle the bag
    if (noRepeatIndex == NO_REPEAT_INDEX_FIRST_TIME) {
        shuffleBagOffLetters();
        noRepeatIndex = 0;
        logAllLettersInBag();
    }
    
    // Get the next letter
    CCInteger* letterObj = (CCInteger*)bagOfLetter->objectAtIndex(noRepeatIndex);
    int letterIndex = letterObj->getValue();
    
    noRepeatIndex++;
    
    CCLog("Random no repeat letter:%d %s", letterIndex, AlphaBetUtils::getInstance()->getLetterName(letterIndex).c_str());
    
    // If we hit the end, re-shuffle and start again
    if (noRepeatIndex >= bagOfLetter->count()) {
        shuffleBagOffLetters();
        noRepeatIndex = 0;
        logAllLettersInBag();
        CCLog("End of no repeats in bag");
    }
    
    return letterIndex;
}

CCArray* LetterBag::getRandomLettersFromAlephBet(int numLetters, int excludeLetter)
{
    bool soundAlike = false;
    
    CCArray* letterArray = CCArray::create();
    letterArray->retain();
    
    for (int letterCount = 0; letterCount < numLetters; letterCount++) {
        // Pick a letter an make sure it's not the exclude letter, or sound-alike vowels
        int randLetter = excludeLetter;
        while ((randLetter == excludeLetter) || soundAlike) {
            bool alreadyIn;
            do {
                alreadyIn = false;
                randLetter = random() % NUM_LETTERS_IDX;
                for (int i = 0; i < letterArray->count(); i++) {
                    CCInteger* oldLetter = (CCInteger*)letterArray->objectAtIndex(i);
                    if (oldLetter->getValue() == randLetter) {
                        alreadyIn = true;
                    }
                }
                
                // Check for special "sound alike" vowels
                if (randLetter != excludeLetter) {
                    soundAlike = AlphaBetUtils::getInstance()->isSoundaAlikesVowel(randLetter, excludeLetter);
                }
                
            } while (alreadyIn);
        }
        // Add the new random letter
        CCInteger* randomLetterObj = CCInteger::create(randLetter);
        letterArray->addObject(randomLetterObj);
    }
    
    CCLog("Random letters chosen:");
    for (int i = 0; i < letterArray->count(); i++) {
        int num = ((CCInteger*)letterArray->objectAtIndex(i))->getValue();
        CCLog("%d", num);
    }
    
    return letterArray;
}

void LetterBag::shuffleBagOffLetters()
{
    int count = bagOfLetter->count();
    for (int i = 0; i < count; i++) {
        // Selecta a random element between i and end of array to swap wit.
        int nElements = count - i;
        int n = (random() % nElements) + i;
        bagOfLetter->exchangeObjectAtIndex(i, n);
    }
}

void LetterBag::logAllLettersInBag()
{
    for (int i = 0; i < bagOfLetter->count(); i++) {
        CCInteger* letterIndex = (CCInteger*)bagOfLetter->objectAtIndex(i);
        CCLog("%d %s", letterIndex->getValue(), AlphaBetUtils::getInstance()->getLetterName(letterIndex->getValue()).c_str());
    }
}

void LetterBag::syncDefaultLetters()
{
    int count = bagOfLetter->count();
    CCUserDefault* userdefault = CCUserDefault::sharedUserDefault();
    
    userdefault->setIntegerForKey(KEY_COUNT, count);
    
    char key[20];
    for (int i = 0; i < count; i++) {
        sprintf(key, "%s%d", KEY_VALUE, i);
        int value = ((CCInteger*)bagOfLetter->objectAtIndex(i))->getValue();
        userdefault->setIntegerForKey(key, value);
    }
    // How may letters are in the defaults
    numLetterChoosen = bagOfLetter->count();
}

void LetterBag::getDefaultLetters()
{
    CCUserDefault* userdefault = CCUserDefault::sharedUserDefault();
    
    int count = userdefault->getIntegerForKey(KEY_COUNT, 0);
    
    char key[20];
    if (bagOfLetter != NULL) {
        bagOfLetter->removeAllObjects();
    }
    
    for (int i = 0; i < count; i++) {
        sprintf(key, "%s%d", KEY_VALUE, i);
        int value = userdefault->getIntegerForKey(key);
        bagOfLetter->addObject(CCInteger::create(value));
    }
    
    if (bagOfLetter != NULL) {
        // How may letters are in the defaults
        numLetterChoosen = bagOfLetter->count();
    }
}

bool LetterBag::addMissedLetter(int letterIndex)
{
    bool success = false;
    bool exist = false;
    
    for (int i = 0; i < bagOfMissedLetter->count(); i++) {
        CCInteger* v_object = (CCInteger*)bagOfMissedLetter->objectAtIndex(i);
        if (v_object->getValue() == letterIndex) {
            exist = true;
            break;
        }
    }
    
    if (!exist) {
        CCInteger* letterNumber = CCInteger::create(letterIndex);
        bagOfMissedLetter->addObject(letterNumber);
        success = true;
    }
    return success;
}

CCArray* LetterBag::getMissedLetters()
{
    return bagOfMissedLetter;
}