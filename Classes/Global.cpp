//
//  Global.cpp
//  AlephBet
//
//  Created by Fredric on 2/1/16.
//
//

#include "Global.hpp"

const char* getResFileName(const char* path)
{
    CCString *s = CCString::create(path);
    CCArray *arr = componentsSeparatedByString( s,"/" );
    if ( arr->count() > 0 )
        return ((CCString*)arr->lastObject())->getCString();
    return path;
}

const char* getResPath(const char* path)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    return getResFileName(path);
#endif
    return path;
}

CCArray* componentsSeparatedByString( CCString* srcStr,const char*sepStr )
{
    CCArray* arr = CCArray::create();
    std::string src = srcStr->m_sString;
    std::string sep(sepStr);
    std::string subStr;
    int n1 = 0;
    int n2 = (int)src.find(sep,n1);
    while ( n2 >= 0 )
    {
        subStr = src.substr(n1,n2-n1);
        if ( subStr != "" )
            arr->addObject( CCString::create( subStr ) );
        n1 = n2+1;
        n2 = (int)src.find(sep,n1);
    }
    n2 = (int)src.length();
    subStr = src.substr(n1,n2-n1);
    if ( subStr != "" )
        arr->addObject( CCString::create( subStr ) );
    
    return arr;
}