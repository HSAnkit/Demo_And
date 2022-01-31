// Copyright (c) 2021 Helpshift

#pragma once

#include "Engine/EngineTypes.h"
#include "HelpshiftSettings.generated.h"

UCLASS(config = Engine, defaultconfig)
class HELPSHIFTSDK_API UHelpshiftSettings : public UObject
{
    GENERATED_BODY()

public:

    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Helpshift Settings")
    FString DomainName = "";
    
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Helpshift Settings")
    bool UsePushNotifications = false;
    
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Helpshift Settings|iOS")
    FString AppIdIOS = "";
    
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Helpshift Settings|Android")
    FString AppIdAndroid = "";
    
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Helpshift Settings|Android")
    FDirectoryPath DrawablePath;
    
    UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Helpshift Settings|Android")
    FDirectoryPath SoundPath;
};
