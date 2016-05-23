//
//  SocialGame.h
//  AlephBet
//
//  Created by Fredric on 2/1/16.
//
//

#ifndef SocialGame_h
#define SocialGame_h

class SocialGame {
public:
    static void sendemail(const char* mailbody);
    static void openWebSite();
    static void sendemailWithScreenShot(const char* filePath, const char* mailBody);
    static void rategame();
};

#endif /* SocialGame_h */
