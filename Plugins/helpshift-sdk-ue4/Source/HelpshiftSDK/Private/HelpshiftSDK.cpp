// Copyright (c) 2021 Helpshift

#include "HelpshiftSDK.h"

#include "HelpshiftLog.h"

#include "Engine/Engine.h"
#include "Developer/Settings/Public/ISettingsModule.h"

#if PLATFORM_IOS
#include "HelpshiftNotificationDelegate.h"
#endif

#define LOCTEXT_NAMESPACE "FHelpshiftSDKModule"

#if PLATFORM_IOS
HelpshiftNotificationDelegate* NotificationDelegate;
#endif

void FHelpshiftSDKModule::StartupModule()
{
    // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

    FString PluginName = "HelpshiftSDK";

    HelpshiftSettings = NewObject<UHelpshiftSettings>(GetTransientPackage(), "HelpshiftSDKSettings", RF_Standalone);
    HelpshiftSettings->AddToRoot();

    // Register settings
    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->RegisterSettings("Project", "Plugins", "HelpshiftSDK",
            LOCTEXT("RuntimeSettingsName", "Helpshift SDK"),
            LOCTEXT("RuntimeSettingsDescription", "Configure Helpshift SDK"),
            HelpshiftSettings);
    }
    
#if PLATFORM_IOS
    if (!HelpshiftSettings->UsePushNotifications) {
        return;
    }
    NotificationDelegate = [HelpshiftNotificationDelegate new];
    
    [UNUserNotificationCenter currentNotificationCenter].delegate = NotificationDelegate;
#endif
}

void FHelpshiftSDKModule::ShutdownModule()
{
    // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
    // we call this function before unloading the module.

    if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        SettingsModule->UnregisterSettings("Project", "Plugins", "HelpshiftSDK");
    }

    if (!GExitPurge)
    {
        // If we're in exit purge, this object has already been destroyed
        HelpshiftSettings->RemoveFromRoot();
    }
    else
    {
        HelpshiftSettings = nullptr;
    }
}

UHelpshiftSettings* FHelpshiftSDKModule::GetSettings() const
{
    return HelpshiftSettings;
}

#undef LOCTEXT_NAMESPACE

DEFINE_LOG_CATEGORY(LogHelpshift);

IMPLEMENT_MODULE(FHelpshiftSDKModule, HelpshiftSDK)
