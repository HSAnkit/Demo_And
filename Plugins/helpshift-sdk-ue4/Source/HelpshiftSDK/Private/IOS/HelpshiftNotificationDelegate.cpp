// Copyright (c) 2021 Helpshift

#include "HelpshiftNotificationDelegate.h"

#import <HelpshiftX_Static/HelpshiftX.h>
#import "IOS/IOSAppDelegate.h"

#include "HelpshiftLog.h"

NS_ASSUME_NONNULL_BEGIN

@implementation HelpshiftNotificationDelegate

- (void)userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void (^)(void))completionHandler {
    UE_LOG(LogHelpshift, Warning, TEXT("DidReceiveNotificationResponse."));
    
    if([[response.notification.request.content.userInfo objectForKey:@"origin"] isEqualToString:@"helpshift"]) {
        [Helpshift handleNotificationWithUserInfoDictionary:response.notification.request.content.userInfo
                                                isAppLaunch:YES
                                             withController:[IOSAppDelegate GetDelegate].IOSController];
    }
    
    completionHandler();
}

- (void) userNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions options))completionHandler {
    UE_LOG(LogHelpshift, Warning, TEXT("WillPresentNotification."));
    
    if([[notification.request.content.userInfo objectForKey:@"origin"] isEqualToString:@"helpshift"]) {
        [Helpshift handleNotificationWithUserInfoDictionary:notification.request.content.userInfo
                                                isAppLaunch:NO
                                             withController:[IOSAppDelegate GetDelegate].IOSController];
    }
    
    if([[UIApplication sharedApplication] applicationState] == UIApplicationStateActive) {
        completionHandler(UNNotificationPresentationOptionNone);
    } else {
        completionHandler(UNNotificationPresentationOptionBadge | UNNotificationPresentationOptionAlert);
    }
}

@end

NS_ASSUME_NONNULL_END
