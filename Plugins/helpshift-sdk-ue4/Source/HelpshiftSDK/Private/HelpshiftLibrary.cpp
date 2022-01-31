// Copyright (c) 2021 Helpshift

#include "HelpshiftLibrary.h"

#include "HelpshiftSDK.h"
#include "HelpshiftCustomIssueFieldParameter.h"

#include "HelpshiftLog.h"

#include "Async/Async.h"

#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"

#include "Kismet/KismetSystemLibrary.h"

#if PLATFORM_ANDROID
#include "Android/HelpshiftJavaConvertor.h"
#include "Android/HelpshiftMethodCallUtils.h"
#include "Android/HelpshiftVariantUtils.h"
#endif

#if PLATFORM_IOS
#import <HelpshiftX_Static/HelpshiftX.h>

#include "IOS/HelpshiftConvertor.h"
#include "IOS/HelpshiftVariantUtils.h"

#include "IOS/IOSAppDelegate.h"
#endif

static const ANSICHAR* HelpshiftBridgeClassName = "com/helpshift/unrealsdk/HelpshiftBridge";

FHelpshiftEventDelegate UHelpshiftLibrary::HelpshiftEventHandler;
FHelpshiftAuthFailureDelegate UHelpshiftLibrary::AuthFailureReasonHandler;

#if PLATFORM_IOS
HelpshiftCallbackDelegate* UHelpshiftLibrary::IosDelegate;
#endif

void UHelpshiftLibrary::Init(TMap<FString, FHelpshiftConfigParameter> Parameters)
{
    UHelpshiftSettings* settings = FHelpshiftSDKModule::Get().GetSettings();
    
    FHelpshiftConfigParameter EngineVersion = UHelpshiftConfigParameterFunctions::Conv_StringToHelpshiftConfigParameter(UKismetSystemLibrary::GetEngineVersion());
    
    Parameters.Add(TEXT("sdkType"), UHelpshiftConfigParameterFunctions::Conv_StringToHelpshiftConfigParameter(TEXT("uex")));
    Parameters.Add(TEXT("pluginVersion"), UHelpshiftConfigParameterFunctions::Conv_StringToHelpshiftConfigParameter(TEXT("10.0.0")));
    Parameters.Add(TEXT("runtimeVersion"), EngineVersion);
    
#if PLATFORM_ANDROID
    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    
    HelpshiftMethodCallUtils::CallStaticVoidMethod(HelpshiftBridgeClassName, "init", "(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;)V", FJavaWrapper::GameActivityThis, HelpshiftJavaConvertor::GetJavaString(settings->DomainName), HelpshiftJavaConvertor::GetJavaString(settings->AppIdAndroid), HelpshiftVariantUtils::VariantMapToJavaMap(Env, Parameters));
#elif PLATFORM_IOS
    [Helpshift installWithPlatformId:settings->AppIdIOS.GetNSString()
                              domain:settings->DomainName.GetNSString()
                              config:HelpshiftVariantUtils::VariantMapToNSDictionary(Parameters)];
    
    IosDelegate = [HelpshiftCallbackDelegate new];
    IosDelegate.onEventReceived = ^(NSString* eventName, NSDictionary* eventData) {
        FString EventName = FString(eventName);
        TMap<FString, FHelpshiftConfigParameter> EventData = HelpshiftVariantUtils::NSDictionaryToVariantMap(eventData);
        
        FHelpshiftMapWrapper Wrapper;
        Wrapper.Data = EventData;
        
        AsyncTask(ENamedThreads::GameThread, [=]() {
            UHelpshiftLibrary::HelpshiftEventHandler.ExecuteIfBound(EventName, Wrapper);
        });
    };
    
    IosDelegate.onAuthError = ^(HelpshiftAuthenticationFailureReason reason) {
        EHelpshiftAuthenticationFailureReason FailReason = (EHelpshiftAuthenticationFailureReason) reason;
        
        AsyncTask(ENamedThreads::GameThread, [=]() {
            UHelpshiftLibrary::AuthFailureReasonHandler.ExecuteIfBound(FailReason);
        });
    };
    
    [Helpshift sharedInstance].delegate = IosDelegate;
#endif
}

void UHelpshiftLibrary::ShowConversation(const TMap<FString, FHelpshiftConfigParameter>& Parameters, const TArray<FString>& Tags, const TMap<FString, FHelpshiftCustomIssueFieldParameter>& CustomIssueFields)
{
#if PLATFORM_ANDROID
    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    
    HelpshiftMethodCallUtils::CallStaticVoidMethod(HelpshiftBridgeClassName, "showConversation", "(Landroid/app/Activity;Ljava/util/Map;[Ljava/lang/String;Ljava/util/Map;)V", FJavaWrapper::GameActivityThis, HelpshiftVariantUtils::VariantMapToJavaMap(Env, Parameters), HelpshiftJavaConvertor::ConvertToJStringArray(Tags), HelpshiftVariantUtils::CifVariantMapToJavaMap(Env, CustomIssueFields));
#elif PLATFORM_IOS
    NSMutableDictionary* params = HelpshiftVariantUtils::VariantMapToNSDictionary(Parameters);
    
    params[@"customIssueFields"] = HelpshiftVariantUtils::CifVariantMapToNSDictionary(CustomIssueFields);
    
    params[@"tags"] = HelpshiftConvertor::ConvertToNSArray(Tags);
    
    [Helpshift showConversationWith:[IOSAppDelegate GetDelegate].IOSController
                             config:params];
#endif
}

void UHelpshiftLibrary::ShowFrequentlyAskedQuestions(const TMap<FString, FHelpshiftConfigParameter>& Parameters)
{
#if PLATFORM_ANDROID
    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    
    HelpshiftMethodCallUtils::CallStaticVoidMethod(HelpshiftBridgeClassName, "showFaq", "(Landroid/app/Activity;Ljava/util/Map;)V", FJavaWrapper::GameActivityThis, HelpshiftVariantUtils::VariantMapToJavaMap(Env, Parameters));
#elif PLATFORM_IOS
    [Helpshift showFAQsWith:[IOSAppDelegate GetDelegate].IOSController
                     config:HelpshiftVariantUtils::VariantMapToNSDictionary(Parameters)];
#endif
}

void UHelpshiftLibrary::ShowSection(const FString& SectionId, const TMap<FString, FHelpshiftConfigParameter>& Parameters)
{
#if PLATFORM_ANDROID
    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    
    HelpshiftMethodCallUtils::CallStaticVoidMethod(HelpshiftBridgeClassName, "showFaqSection", "(Landroid/app/Activity;Ljava/lang/String;Ljava/util/Map;)V", FJavaWrapper::GameActivityThis, HelpshiftJavaConvertor::GetJavaString(SectionId), HelpshiftVariantUtils::VariantMapToJavaMap(Env, Parameters));
#elif PLATFORM_IOS
    [Helpshift showFAQSection:SectionId.GetNSString()
                         with:[IOSAppDelegate GetDelegate].IOSController
                       config:HelpshiftVariantUtils::VariantMapToNSDictionary(Parameters)];
#endif
}

void UHelpshiftLibrary::ShowQuestion(const FString& QuestionId, const TMap<FString, FHelpshiftConfigParameter>& Parameters)
{
#if PLATFORM_ANDROID
    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    
    HelpshiftMethodCallUtils::CallStaticVoidMethod(HelpshiftBridgeClassName, "showFaqQuestion", "(Landroid/app/Activity;Ljava/lang/String;Ljava/util/Map;)V", FJavaWrapper::GameActivityThis, HelpshiftJavaConvertor::GetJavaString(QuestionId), HelpshiftVariantUtils::VariantMapToJavaMap(Env, Parameters));
#elif PLATFORM_IOS
    [Helpshift showSingleFAQ:QuestionId.GetNSString()
                        with:[IOSAppDelegate GetDelegate].IOSController
                      config:HelpshiftVariantUtils::VariantMapToNSDictionary(Parameters)];
#endif
}

void UHelpshiftLibrary::SetLanguage(const FString& Language)
{
#if PLATFORM_ANDROID
    HelpshiftMethodCallUtils::CallStaticVoidMethod(HelpshiftBridgeClassName, "setLanguage", "(Ljava/lang/String;)V", HelpshiftJavaConvertor::GetJavaString(Language));
#elif PLATFORM_IOS
    [Helpshift setLanguage:Language.GetNSString()];
#endif
}

void UHelpshiftLibrary::Login(const TMap<FString, FString>& Parameters)
{
#if PLATFORM_ANDROID
    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    
    HelpshiftMethodCallUtils::CallStaticVoidMethod(HelpshiftBridgeClassName, "login", "(Ljava/util/Map;)V", HelpshiftJavaConvertor::StringMapToJavaMap(Parameters));
#elif PLATFORM_IOS
    [Helpshift loginUser:HelpshiftConvertor::ConvertToNSDictionary(Parameters)];
#endif
}

void UHelpshiftLibrary::Logout()
{
#if PLATFORM_ANDROID
    HelpshiftMethodCallUtils::CallStaticVoidMethod(HelpshiftBridgeClassName, "logout", "()V");
#elif PLATFORM_IOS
    [Helpshift logout];
#endif
}

void UHelpshiftLibrary::ClearAnonymousUserOnLogin()
{
#if PLATFORM_ANDROID
    HelpshiftMethodCallUtils::CallStaticVoidMethod(HelpshiftBridgeClassName, "clearAnonymousUserOnLogin", "()V");
#elif PLATFORM_IOS
    [Helpshift clearAnonymousUserOnLogin];
#endif
}

void UHelpshiftLibrary::RegisterPushToken(const FString& Token)
{
    UE_LOG(LogHelpshift, Verbose, TEXT("RegisterPushToken: %s"), *Token);
    
    UHelpshiftSettings* Settings = FHelpshiftSDKModule::Get().GetSettings();
    
    if (!Settings->UsePushNotifications) {
        UE_LOG(LogHelpshift, Error, TEXT("Use Push Notifications is not enabled in the Project Settings. Will not register the token."));
        return;
    }
    
#if PLATFORM_ANDROID
    HelpshiftMethodCallUtils::CallStaticVoidMethod(HelpshiftBridgeClassName, "registerPushToken", "(Ljava/lang/String;)V", HelpshiftJavaConvertor::GetJavaString(Token));
#elif PLATFORM_IOS
    UE_LOG(LogHelpshift, Verbose, TEXT("RegisterPushToken is called automatically on iOS. Skipping."));
#endif
}

void UHelpshiftLibrary::HandlePushAndroid(const TMap<FString, FString>& Parameters)
{
    UHelpshiftSettings* Settings = FHelpshiftSDKModule::Get().GetSettings();
    
    if (!Settings->UsePushNotifications) {
        UE_LOG(LogHelpshift, Error, TEXT("Use Push Notifications is not enabled in the Project Settings. Will not handle the notification data."));
        return;
    }
    
#if PLATFORM_ANDROID
    HelpshiftMethodCallUtils::CallStaticVoidMethod(HelpshiftBridgeClassName, "handlePush", "(Ljava/util/Map;)V", HelpshiftJavaConvertor::StringMapToJavaMap(Parameters));
#endif
}

void UHelpshiftLibrary::HandlePushIos(const TMap<FString, FHelpshiftConfigParameter>& Parameters, bool IsLaunch)
{
    UHelpshiftSettings* Settings = FHelpshiftSDKModule::Get().GetSettings();
    
    if (!Settings->UsePushNotifications) {
        UE_LOG(LogHelpshift, Error, TEXT("Use Push Notifications is not enabled in the Project Settings. Will not handle the notification data."));
        return;
    }
    
#if PLATFORM_IOS
    [Helpshift handleNotificationWithUserInfoDictionary:HelpshiftVariantUtils::VariantMapToNSDictionary(Parameters)
                                            isAppLaunch:IsLaunch
                                         withController:[IOSAppDelegate GetDelegate].IOSController];
#endif
}

void UHelpshiftLibrary::RequestUnreadMessageCount(bool FetchFromServer)
{
#if PLATFORM_ANDROID
    HelpshiftMethodCallUtils::CallStaticVoidMethod(HelpshiftBridgeClassName, "requestUnreadMessageCount", "(Z)V", FetchFromServer);
#elif PLATFORM_IOS
    [Helpshift requestUnreadMessageCount:FetchFromServer];
#endif
}

void UHelpshiftLibrary::BindEventDelegate(const FHelpshiftEventDelegate& Callback)
{
    HelpshiftEventHandler = Callback;
}

void UHelpshiftLibrary::BindAuthFailureDelegate(const FHelpshiftAuthFailureDelegate& Callback)
{
    AuthFailureReasonHandler = Callback;
}

TMap<FString, FHelpshiftConfigParameter> UHelpshiftLibrary::ParseIosNotificationPayload(const FString& Payload)
{
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
    TMap<FString, FHelpshiftConfigParameter> Parameters;
    
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Payload);
    if (FJsonSerializer::Deserialize(Reader, JsonObject))
    {
#if PLATFORM_IOS
        Parameters = HelpshiftVariantUtils::DeserializeJson(JsonObject);
#endif
    }
    
    return Parameters;
}

#if PLATFORM_ANDROID
JNI_METHOD void Java_com_helpshift_unrealsdk_HelpshiftBridge_OnHelpshiftEventOccurred(JNIEnv* env, jclass clazz, jstring type, jobject javaDataMap)
{
    JNIEnv* Env = FAndroidApplication::GetJavaEnv();
    
    FString EventName = HelpshiftJavaConvertor::FromJavaString(type);
    TMap<FString, FHelpshiftConfigParameter> Parameters = HelpshiftVariantUtils::JavaMapToVariantMap(Env, javaDataMap);
    
    UE_LOG(LogHelpshift, Verbose, TEXT("Java_com_helpshift_unrealsdk_HelpshiftBridge_OnHelpshiftEventOccurred"));
    
    FHelpshiftMapWrapper Wrapper;
    Wrapper.Data = Parameters;
    
    AsyncTask(ENamedThreads::GameThread, [=]() {
        UE_LOG(LogHelpshift, Verbose, TEXT("UHelpshiftLibrary::HelpshiftEventHandler"));
        UHelpshiftLibrary::HelpshiftEventHandler.ExecuteIfBound(EventName, Wrapper);
    });
}

JNI_METHOD void Java_com_helpshift_unrealsdk_HelpshiftBridge_OnHelpshiftAuthError(JNIEnv* env, jclass clazz, jint reason)
{
    EHelpshiftAuthenticationFailureReason FailReason = (EHelpshiftAuthenticationFailureReason) reason;
    
    UE_LOG(LogHelpshift, Verbose, TEXT("Java_com_helpshift_unrealsdk_HelpshiftBridge_OnHelpshiftAuthError"));
    
    AsyncTask(ENamedThreads::GameThread, [=]() {
        UE_LOG(LogHelpshift, Verbose, TEXT("UHelpshiftLibrary::AuthFailureReasonHandler"));
        UHelpshiftLibrary::AuthFailureReasonHandler.ExecuteIfBound(FailReason);
    });
}
#endif
