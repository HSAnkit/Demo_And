// Copyright (c) 2021 Helpshift

#include "HelpshiftAppDelegate.h"

#include "HelpshiftSDK.h"

#import <HelpshiftX_Static/HelpshiftX.h>

#include "HelpshiftLog.h"

NS_ASSUME_NONNULL_BEGIN

@implementation IOSAppDelegate(Helpshift)

- (void) application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
    UE_LOG(LogHelpshift, Warning, TEXT("ApplicationRegisteredForRemoteNotification."));
    
    UHelpshiftSettings* Settings = FHelpshiftSDKModule::Get().GetSettings();
    
    if (!Settings->UsePushNotifications) {
        UE_LOG(LogHelpshift, Error, TEXT("Use Push Notifications is not enabled in the Project Settings. Will not register the token."));
        return;
    }
    
    [Helpshift registerDeviceToken:deviceToken];
}

@end

NS_ASSUME_NONNULL_END
