// Copyright (c) 2021 Helpshift

#pragma once

#import <HelpshiftX_Static/HelpshiftX.h>

@interface HelpshiftCallbackDelegate : NSObject <HelpshiftDelegate>

@property (nonatomic, copy) void (^onEventReceived)(NSString* eventName, NSDictionary* eventData);

@property (nonatomic, copy) void (^onAuthError)(HelpshiftAuthenticationFailureReason reason);

@end
