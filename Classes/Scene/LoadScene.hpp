//
//  LoadScene.hpp
//  AlephBet
//
//  Created by Fredric on 2/2/16.
//
//

#ifndef LoadScene_hpp
#define LoadScene_hpp

#include <stdio.h>
#include "cocos2d.h"


using namespace cocos2d;

class LoadScene:public CCLayer
{
private:
    CCSize      winSize;
    CCSprite*   spLoading;
    CCSprite*   spLoadingProgress;
public:
    static CCScene* scene();
    virtual bool init();
    void createUI();
    void loadResources();
    void onLoad(CCObject * sender);
    void onFinishLoad(CCObject* sender);
    
    void preloadSounds();
    CREATE_FUNC(LoadScene);
};

#endif /* LoadScene_hpp */
