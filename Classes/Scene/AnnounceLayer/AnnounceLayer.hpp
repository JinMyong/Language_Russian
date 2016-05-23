//
//  AnnounceLayer.hpp
//  AlephBet
//
//  Created by Fredric on 12/28/15.
//
//

#ifndef AnnounceLayer_hpp
#define AnnounceLayer_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class AnnounceLayer:public CCLayer
{
private:
    CCSize winSize;
    // Big, Showy dynamic labels
    CCLabelTTF* countLabel;
    CCLabelTTF* letterLabel;
    CCLabelTTF* hitLabel;
    CCLabelTTF* nextLevelLabel;
    CCLabelTTF* perfectLabel;
    CCLabelTTF* gameOverLabel;
    CCLabelTTF* highScoreLabel;
    
    // Stat labels
    CCLabelTTF* scoreLabel;
    CCLabelTTF* levelSateLabel;
    
    int countdown;
    bool hitSuccess;
public:
    virtual bool init();
    void startCountDown();
    void endCountDownAction();
    void doNextCountDown();
    void announceLetter(int letterIndex);
    void announceHit(bool hit);
    void endAnnounceHit();
    void announceLevelResults(int level, bool perfect);
    void endAnnounceLevelResults();
    void startShowHints();
    void endShowHints();
    
    CREATE_FUNC(AnnounceLayer);
};

#endif /* AnnounceLayer_hpp */
