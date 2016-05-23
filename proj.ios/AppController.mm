#import "AppController.h"
#import "EAGLView.h"
#import "cocos2d.h"
#import "AppDelegate.h"
#import "RootViewController.h"
#import "Const.h"

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    
    
    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    
    // Init the EAGLView
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGB565
                                     depthFormat: GL_DEPTH24_STENCIL8_OES
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples: 0];

    // Use RootViewController manage EAGLView 
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    
    [window makeKeyAndVisible];
    
    [[UIApplication sharedApplication] setStatusBarHidden:true];
    
    cocos2d::CCApplication::sharedApplication()->run();

    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    cocos2d::CCDirector::sharedDirector()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [window release];
    [super dealloc];
}

#pragma mark - Social Functions
- (void) sendEmail:(NSString*)mailbody
{
    picker = [[MFMailComposeViewController alloc] init];
    if ((!picker) || ![MFMailComposeViewController canSendMail]) {
        NSLog(@"Impossible to send mail");
        return;
    }
    picker.mailComposeDelegate = self;
    NSString* emailbody = [NSString stringWithFormat:@"%@\n%s", mailbody, IOS_URL];
    [picker setMessageBody:emailbody isHTML:NO];
    
    [viewController presentViewController:picker animated:YES completion:NULL];
    
    [picker release];
}

-(void) mailComposeController:(MFMailComposeViewController *)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError *)error{
    UIAlertView* alert = [[UIAlertView alloc] initWithTitle:@"Error"
                                                    message:@"Failed Sending Mail"
                                                   delegate:nil
                                          cancelButtonTitle:@"OK"
                                          otherButtonTitles:nil];
    switch (result) {
        case MFMailComposeResultCancelled:
            NSLog(@"cancelled");
            break;
        case MFMailComposeResultSaved:
            NSLog(@"Mail saved no sent");
            break;
        case MFMailComposeResultFailed:
            NSLog(@"Failed sending mail");
            [alert show];
            break;
        case MFMailComposeResultSent:
            NSLog(@"Mail Sent");
            break;
        default:
            break;
    }
    
    [viewController dismissViewControllerAnimated:YES completion:NULL];
}

-(void) openWebSite
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://www.tzedekamerica.org"]];
}


-(void) sendEmailWithScreen:(NSString*) filepath
{
    if (filepath.length <= 0) {
        return;
    }
    
    UIImage* image = [UIImage imageWithContentsOfFile:filepath];
    NSData * data = UIImagePNGRepresentation(image);
    NSString* mailbody = @"Hi,\n\n I’ve been playing Alif Ba Ta Bullseye and here is my score.";
    [self emailImageWithImageData:data mailBody:mailbody];
}

-(void) sendEmailWithScreen:(NSString *)filepath MailBody:(NSString *)mailbody
{
    if (filepath.length <= 0) {
        return;
    }
    
    UIImage* image = [UIImage imageWithContentsOfFile:filepath];
    NSData * data = UIImagePNGRepresentation(image);
    [self emailImageWithImageData:data mailBody:mailbody];
}

- (void)emailImageWithImageData:(NSData *)data mailBody:(NSString*) mailBodyString
{
    MFMailComposeViewController *mailpicker = [[MFMailComposeViewController alloc] init];
    
    if ((!mailpicker) || ![MFMailComposeViewController canSendMail]) {
        NSLog(@"Impossible to send mail");
        return;
    }
    
    mailpicker.mailComposeDelegate = self;
    
    // This is not an HTML formatted email
    [mailpicker setMessageBody:mailBodyString isHTML:NO];
    
    // Attach image data to the email
    [mailpicker addAttachmentData:data mimeType:@"image/png" fileName:@"screenshot.png"];
    
    // Show email view
    [viewController presentViewController:mailpicker animated:YES completion:NULL];
    
    // Release picker
    [mailpicker release];
}
@end
