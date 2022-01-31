// Copyright (c) 2021 Helpshift

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "HelpshiftConfigParameter.h"
#include "HelpshiftCustomIssueFieldParameter.h"

#if PLATFORM_IOS
#include "../Private/IOS/HelpshiftCallbackDelegate.h"
#endif

#include "HelpshiftLibrary.generated.h"

UENUM(BlueprintType)
enum class EHelpshiftAuthenticationFailureReason : uint8
{
    REASON_AUTH_TOKEN_NOT_PROVIDED = 0,
    REASON_INVALID_AUTH_TOKEN = 1,
    UNKNOWN = 2
};

USTRUCT(BlueprintType)
struct FHelpshiftMapWrapper
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Helpshift")
    TMap<FString, FHelpshiftConfigParameter> Data;
};

DECLARE_DYNAMIC_DELEGATE_TwoParams(FHelpshiftEventDelegate, const FString&, EventName, const FHelpshiftMapWrapper&, DataWrapper);
DECLARE_DYNAMIC_DELEGATE_OneParam(FHelpshiftAuthFailureDelegate, EHelpshiftAuthenticationFailureReason, Reason);

UCLASS()
class HELPSHIFTSDK_API UHelpshiftLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
    
public:
    
    /**
     * Initialise the Helpshift SDK. Helpshift uniquely identifies each registered App with a combination of 2 tokens that are set in the Project Settings -> Helpshift SDK.
     * Should be called as soon as possible (Event Construct).
     *
     * @param Parameters: additional data to pass for the initialization.
     * https://developers.helpshift.com/sdkx_android/sdk-configuration/
     * https://developers.helpshift.com/sdkx_ios/sdk-configuration/
     */
    UFUNCTION(BlueprintCallable, Category = "Helpshift", meta = (AutoCreateRefTerm = "Parameters"))
    static void Init(TMap<FString, FHelpshiftConfigParameter> Parameters);
    
    /**
    * You can use the API call to allow a user to directly send feedback or start a new conversation without having to first view FAQs.
    * Once, a user starts a new conversation, this API call will show the conversation screen. The conversation will continue until it is resolved or rejected by the agent.
    *
    * @param Parameters: additional data to pass for the conversation.
    * https://developers.helpshift.com/sdkx_android/sdk-configuration/
    * https://developers.helpshift.com/sdkx_ios/sdk-configuration/
    * @param Tags: additional tags for the conversation.
    * https://developers.helpshift.com/sdkx_android/tracking/#adding-tags
    * @param CustomIssueFields: custom issue fields for the conversation.
    * https://developers.helpshift.com/sdkx_android/tracking/#set-custom-issue-fields
    */
    UFUNCTION(BlueprintCallable, Category = "Helpshift", meta = (AutoCreateRefTerm = "Parameters,Tags,CustomIssueFields"))
    static void ShowConversation(const TMap<FString, FHelpshiftConfigParameter>& Parameters, const TArray<FString>& Tags, const TMap<FString, FHelpshiftCustomIssueFieldParameter>& CustomIssueFields);
    
    /**
    * You can use the API call to provide a way for the user to invoke the purpose-built help/support section in your app.
    * This is the easiest approach to enable help in your app as it bundles all the capabilities of the Helpshift SDK in a simple and intuitive interface.
    * You can wire this API call to a "Help" or "Support" action in your app.
    *
    * @param Parameters: additional data to pass.
    * https://developers.helpshift.com/sdkx_android/sdk-configuration/
    * https://developers.helpshift.com/sdkx_ios/sdk-configuration/
    */
    UFUNCTION(BlueprintCallable, Category = "Helpshift", meta = (AutoCreateRefTerm = "Parameters"))
    static void ShowFrequentlyAskedQuestions(const TMap<FString, FHelpshiftConfigParameter>& Parameters);
    
    /**
    * You can use the API call to invoke a particular section of your FAQs with its FAQ section publish-id.
    *
    * @param SectionId: FAQ section publish-id.
    * @param Parameters: additional data to pass.
    */
    UFUNCTION(BlueprintCallable, Category = "Helpshift", meta = (AutoCreateRefTerm = "Parameters"))
    static void ShowSection(const FString& SectionId, const TMap<FString, FHelpshiftConfigParameter>& Parameters);
    
    /**
    * You can use the API call to invoke a particular question of your FAQs with its FAQ question publish-id.
    *
    * @param QuestionId: FAQ question publish-id.
    * @param Parameters: additional data to pass.
    */
    UFUNCTION(BlueprintCallable, Category = "Helpshift", meta = (AutoCreateRefTerm = "Parameters"))
    static void ShowQuestion(const FString& QuestionId, const TMap<FString, FHelpshiftConfigParameter>& Parameters);
    
    /**
    * You can set the language by calling this API to set the language after the initialization code.
    * The list of supported languages can be found here: https://developers.helpshift.com/sdkx_ios/internationalization/
    *
    * @param Language: language code.
    */
    UFUNCTION(BlueprintCallable, Category = "Helpshift")
    static void SetLanguage(const FString& Language);
    
    /**
    * You should call Helpshift SDK's login API whenever the user successfully logs into your app.
    * For the list of supported data parameters visit: https://developers.helpshift.com/sdkx_ios/users/#users
    *
    * @param Parameters: login data.
    */
    UFUNCTION(BlueprintCallable, Category = "Helpshift", meta = (AutoCreateRefTerm = "Parameters"))
    static void Login(const TMap<FString, FString>& Parameters);
    
    /**
    * Once a user logs out from your app, you should call the Helpshift SDK's logout API to ensure no one else can view this user's conversations.
    */
    UFUNCTION(BlueprintCallable, Category = "Helpshift")
    static void Logout();
    
    /**
    * An anonymous user is someone who can access the app without a username and password.
    * If a user identifier (UserID and/or Email) is not passed via the login API, then Helpshift assumes that the user is an anonymous user.
    *
    * If your use case involves multiple logged in/anonymous users using the same device and discussing info during support conversations
    * (which you ideally wouldn't want to be shared across logins), you should use this API.
    * If this API is used, then anonymous users will be cleared whenever a user logs in. Once cleared, such users (and their conversations) cannot be fetched again for the end users.
    */
    UFUNCTION(BlueprintCallable, Category = "Helpshift")
    static void ClearAnonymousUserOnLogin();
    
    /**
    * For Helpshift SDK to work with the Helpshift push notification service you will need to invoke this call after obtaining the push notification token.
    * The token is handled automatically on iOS.
    *
    * @param Token: push notifications token.
    */
    UFUNCTION(BlueprintCallable, Category = "Helpshift")
    static void RegisterPushToken(const FString& Token);
    
    /**
    * Pass the push notification data to Helpshift SDK. Use this only if you can't modify the native callbacks.
    *
    * @param Parameters: notification data.
    */
    UFUNCTION(BlueprintCallable, Category = "Helpshift", meta = (AutoCreateRefTerm = "Parameters"))
    static void HandlePushAndroid(const TMap<FString, FString>& Parameters);
    
    /**
    * Pass the push notification data to Helpshift SDK. Use this only if you can't modify the native callbacks.
    *
    * @param Parameters: notification data.
    * @param IsLaunch: was the app launched via notification.
    */
    UFUNCTION(BlueprintCallable, Category = "Helpshift", meta = (AutoCreateRefTerm = "Parameters"))
    static void HandlePushIos(const TMap<FString, FHelpshiftConfigParameter>& Parameters, bool IsLaunch);
    
    /**
    * To fetch unread messages count from the server you can call this API. It will return unread messages count via delegate.
    * Based on the value of FetchFromServer, the locally stored count will be returned if FetchFromServer is false else from the server by fetching remotely when FetchFromServer is true.
    *
    * @param FetchFromServer: should the messages count be fetched from the server.
    */
    UFUNCTION(BlueprintCallable, Category = "Helpshift")
    static void RequestUnreadMessageCount(bool FetchFromServer);
    
    /**
    * Bind an event delegate to the Helpshift Event handler.
    *
    * @param Callback: function to be invoked when an SDK event is triggered..
    */
    UFUNCTION(BlueprintCallable, Category = "Helpshift")
    static void BindEventDelegate(const FHelpshiftEventDelegate& Callback);
    
    /**
    * Bind an event delegate to the Helpshift Authentication Failure handler.
    *
    * @param Callback: function to be invoked when user authentication fails.
    */
    UFUNCTION(BlueprintCallable, Category = "Helpshift")
    static void BindAuthFailureDelegate(const FHelpshiftAuthFailureDelegate& Callback);
    
    /**
    * Helper function to parse the JSON payload of iOS notification into Map of Helpshift Config Parameters.
    *
    * @param Payload: payload of iOS notification.
    */
    UFUNCTION(BlueprintCallable, Category = "Helpshift|Demo")
    static TMap<FString, FHelpshiftConfigParameter> ParseIosNotificationPayload(const FString& Payload);
    
    static FHelpshiftEventDelegate HelpshiftEventHandler;
    static FHelpshiftAuthFailureDelegate AuthFailureReasonHandler;
    
#if PLATFORM_IOS
    static HelpshiftCallbackDelegate* IosDelegate;
#endif
};
