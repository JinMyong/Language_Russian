//
//  Global.hpp
//  AlephBet
//
//  Created by Fredric on 2/1/16.
//
//

#ifndef Global_hpp
#define Global_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

const char* getResPath(const char* path);
const char* getResFileName(const char* path);
CCArray* componentsSeparatedByString( CCString* srcStr,const char*sepStr);

#endif /* Global_hpp */
