// Copyright (c) 2021 Helpshift

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "HelpshiftConstants.generated.h"

UCLASS()
class HELPSHIFTSDK_API UHelpshiftConstants : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
    
public:
    
    /**
     * A key to pass to enable/disable the Helpshift in-app-notifications.
     *
     * Value type: bool.
     * Valid for: UHelpshiftLibrary::Init.
     */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Configuration")
    static inline FString HelpshiftConfigEnableInAppNotificationsKey()
    {
        return "enableInAppNotification";
    }
    
    /**
    * A key to pass to set the Helpshift controller orientation.
    *
    * Value type: int (HelpshiftConfigScreenOrientationLandscape or HelpshiftConfigScreenOrientationPortrait).
    * Valid for: UHelpshiftLibrary::Init.
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Configuration")
    static inline FString HelpshiftConfigScreenOrientationKey()
    {
        return "screenOrientation";
    }
    
    /**
    * A key to pass to enable/disable the Helpshift logs.
    *
    * Value type: bool.
    * Valid for: UHelpshiftLibrary::Init.
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Configuration")
    static inline FString HelpshiftConfigEnableLoggingKey()
    {
        return "enableLogging";
    }
    
    /**
    * A key to pass to set the custom notification small icon on Android.
    * Pass the name of the file without the extension (notification_icon for notification_icon.png).
    *
    * Value type: string.
    * Valid for: UHelpshiftLibrary::Init.
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Configuration")
    static inline FString HelpshiftConfigNotificationIconKey()
    {
        return "notificationIcon";
    }
    
    /**
    * A key to pass to set the custom notification large icon on Android.
    * Pass the name of the file without the extension (notification_icon for notification_icon.png).
    *
    * Value type: string.
    * Valid for: UHelpshiftLibrary::Init.
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Configuration")
    static inline FString HelpshiftConfigNotificationLargeIconKey()
    {
        return "notificationLargeIcon";
    }
    
    /**
    * A key to pass to set the custom notification sound on Android.
    * Pass the name of the file without the extension (notification_sound for notification_sound.mp3).
    *
    * Value type: string.
    * Valid for: UHelpshiftLibrary::Init.
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Configuration")
    static inline FString HelpshiftConfigNotificationSoundIdKey()
    {
        return "notificationSoundId";
    }
    
    /**
    * A key to pass to set the custom notification channel on Android.
    * The channel has to be already created in order for the notifications to be sent.
    *
    * Value type: string.
    * Valid for: UHelpshiftLibrary::Init.
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Configuration")
    static inline FString HelpshiftConfigNotificationChannelIdKey()
    {
        return "notificationChannelId";
    }
    
    /**
    * A key to pass to enable/disable the full privacy of the user.
    * https://developers.helpshift.com/sdkx_android/sdk-configuration/#fullprivacy
    *
    * Value type: bool.
    * Valid for: UHelpshiftLibrary::ShowConversation, UHelpshiftLibrary::ShowFrequentlyAskedQuestions.
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Configuration")
    static inline FString HelpshiftConfigEnableFullPrivacyKey()
    {
        return "fullPrivacy";
    }
    
    /**
    * A key to pass to customise the in-app-notification on iOS.
    *
    * Value type: Map.
    * Valid for: UHelpshiftLibrary::Init.
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Configuration")
    static inline FString HelpshiftConfigInAppNotificationAppearanceKey()
    {
        return "inAppNotificationAppearance";
    }
    
    /**
    * A key to pass to customise the in-app-notification background color on iOS.
    *
    * Value type: color hex string.
    * Valid for: UHelpshiftLibrary::Init.
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Configuration")
    static inline FString HelpshiftConfigInAppNotificationBannerBackgroundColorKey()
    {
        return "bannerBackgroundColor";
    }
    
    /**
    * A key to pass to customise the in-app-notification text color on iOS.
    *
    * Value type: color hex string.
    * Valid for: UHelpshiftLibrary::Init.
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Configuration")
    static inline FString HelpshiftConfigInAppNotificationTextColorKey()
    {
        return "textColor";
    }
    
    /**
    * A key to pass to customise the in-app-notification text color on iOS.
    * The default value is false, presents support views as UIModalPresentationFormSheet.
    * When the value is set to true, support views are presented in UIModalPresentationFullScreen. Use this setting to show Helpshift in full-screen mode.
    *
    * Value type: bool.
    * Valid for: UHelpshiftLibrary::Init.
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Configuration")
    static inline FString HelpshiftConfigPresentFullScreenOniPadKey()
    {
        return "presentFullScreenOniPad";
    }
    
    /**
    * A value to pass to set the landscape Helpshift controller orientation.
    *
    * Valid for HelpshiftConfigScreenOrientationKey key.
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Configuration")
    static inline int HelpshiftConfigScreenOrientationLandscape()
    {
        return 0;
    }
    
    /**
    * A value to pass to set the portrait Helpshift controller orientation.
    *
    * Valid for HelpshiftConfigScreenOrientationKey key.
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Configuration")
    static inline int HelpshiftConfigScreenOrientationPortrait()
    {
        return 1;
    }
    
    /**
    * This event is triggered when the user opens or exits the chat screen.
    *
    * Keys in event data: HelpshiftEventDataSDKVisible (bool).
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventWidgetToggle()
    {
        return "widgetToggle";
    }
    
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventDataSDKVisible()
    {
        return "visible";
    }
    
    /**
    * This event triggers when the user sends the first message in a conversation.
    *
    * Keys in event data: HelpshiftEventDataMessage (string).
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventConversationStart()
    {
        return "conversationStart";
    }
    
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventDataMessage()
    {
        return "message";
    }
    
    /**
    * This event is triggered when the user adds a message in a conversation. It might be a text message, response via bot input, or an attachment.
    *
    * Keys in event data: HelpshiftEventDataMessageType (HelpshiftEventDataMessageTypeAttachment or HelpshiftEventDataMessageTypeText),
    * HelpshiftEventDataMessageBody (string).
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventMessageAdd()
    {
        return "messageAdd";
    }
    
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventDataMessageType()
    {
        return "type";
    }
    
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventDataMessageBody()
    {
        return "body";
    }
    
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventDataMessageTypeAttachment()
    {
        return "attachment";
    }
    
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventDataMessageTypeText()
    {
        return "text";
    }
    
    /**
    * This event is triggered when the user submits a CSAT rating after the conversation ends.
    *
    * Keys in event data: HelpshiftEventDataCsatRating (int), HelpshiftEventDataAdditionalFeedback (string).
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventCsatSubmit()
    {
        return "csatSubmit";
    }
    
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventDataCsatRating()
    {
        return "rating";
    }
    
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventDataAdditionalFeedback()
    {
        return "additionalFeedback";
    }
    
    /**
    * This event contains information about the current ongoing conversation.
    *
    * Keys in event data: HelpshiftEventDataLatestIssueId (string), HelpshiftEventDataLatestIssuePublishId (string), HelpshiftEventDataIsIssueOpen (bool).
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventConversationStatus()
    {
        return "conversationStatus";
    }
    
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventDataLatestIssueId()
    {
        return "latestIssueId";
    }
    
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventDataLatestIssuePublishId()
    {
        return "latestIssuePublishId";
    }
    
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventDataIsIssueOpen()
    {
        return "open";
    }
    
    /**
    * This event is triggered when the conversation ends (resolved or rejected) and it cannot be reopened.
    *
    * Keys in event data: none.
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventConversationEnd()
    {
        return "conversationEnd";
    }
    
    /**
    * This event is triggered when an agent rejects the conversation.
    *
    * Keys in event data: none.
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventConversationRejected()
    {
        return "conversationRejected";
    }
    
    /**
    * This event is triggered when an agent resolves the conversation.
    *
    * Keys in event data: none.
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventConversationResolved()
    {
        return "conversationResolved";
    }
    
    /**
    * When resolution question is enabled, the users are asked if they're satisfied with the resolution.
    * If the user rejects it and sends a new message, then the conversation is reopened and the Conversation Reopened event is triggered.
    *
    * Keys in event data: none.
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventConversationReopened()
    {
        return "conversationReopened";
    }
    
    /**
    * If you want to keep track of when helpshift session starts in your app, you can implement this delegate callback. The delegate will get fired every time the Helpshift session starts.
    *
    * Keys in event data: none.
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventSDKSessionStarted()
    {
        return "helpshiftSessionStarted";
    }
    
    /**
    * If you want to keep track of when helpshift session ends in your app, you can implement this delegate callback. The delegate will get fired every time the Helpshift session ends.
    *
    * Keys in event data: none.
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventSDKSessionEnded()
    {
        return "helpshiftSessionEnded";
    }
    
    /**
    * If you want a count of all new messages received in an existing conversation, you can call UHelpshiftLibrary::RequestUnreadMessageCount(bool FetchFromServer).
    * The count of the number of messages will be conveyed to your app via this event. You can also use this event to keep your badge counts updated.
    *
    * Keys in event data: HelpshiftEventDataMessageCount (int), HelpshiftEventDataMessageCountFromCache (int).
    */
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventReceivedUnreadMessageCount()
    {
        return "receivedUnreadMessageCount";
    }
    
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventDataMessageCount()
    {
        return "count";
    }
    
    UFUNCTION(BlueprintPure, Category = "Helpshift|Constants|Events")
    static inline FString HelpshiftEventDataMessageCountFromCache()
    {
        return "fromCache";
    }
};
