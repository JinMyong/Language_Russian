//
//  AboutScene.hpp
//  AlephBet
//
//  Created by Fredric on 1/12/16.
//
//

#ifndef AboutScene_hpp
#define AboutScene_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class AboutScene:public CCLayer
{
private:
    CCSize winSize;
public:
    static CCScene* scene();
    virtual bool init();
    void createUI();
    void mainmenuHandler(CCObject* sender);
    void emailHandler(CCObject* sender);
    void linkHandler(CCObject* sender);
    
CREATE_FUNC(AboutScene);
};

#endif /* AboutScene_hpp */
