#import <UIKit/UIKit.h>
#import <MessageUI/MessageUI.h>

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate, MFMailComposeViewControllerDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    
    MFMailComposeViewController* picker;
}

-(void) sendEmail:(NSString*)mailbody;
-(void) openWebSite;
-(void) sendEmailWithScreen:(NSString*) filepath;
-(void) sendEmailWithScreen:(NSString*) filepath MailBody:(NSString*)mailbody;

@end

