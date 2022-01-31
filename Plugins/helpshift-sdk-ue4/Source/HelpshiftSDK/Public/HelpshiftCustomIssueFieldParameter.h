// Copyright (c) 2021 Helpshift

#pragma once

#include "Misc/Variant.h"

#include "HelpshiftCustomIssueFieldParameter.generated.h"

UENUM(BlueprintType)
enum class EHelpshiftCustomIssueFieldParameterValueType : uint8
{
    Null,
    SingleLine,
    MultiLine,
    Number,
    Dropdown,
    Date,
    Checkbox
};

/**
* Generic object for a custom issue field parameter that can hold different values.
 */
USTRUCT(BlueprintType)
struct HELPSHIFTSDK_API FHelpshiftCustomIssueFieldParameter
{
    GENERATED_BODY()

public:
    
    template<typename T>
    T GetValue() const;

    UPROPERTY(BlueprintReadOnly)
    EHelpshiftCustomIssueFieldParameterValueType Type = EHelpshiftCustomIssueFieldParameterValueType::Null;
    
    FVariant Value;
    
    friend FArchive& operator<<(FArchive& Ar, FHelpshiftCustomIssueFieldParameter& Variant)
    {
        return Ar << Variant.Type << Variant.Value;
    }
};

UCLASS(BlueprintType)
class HELPSHIFTSDK_API UHelpshiftCustomIssueFieldParameterFunctions : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Helpshift")
    static FHelpshiftCustomIssueFieldParameter NewSingleLineParameter(const FString& Value);
    
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Helpshift")
    static FHelpshiftCustomIssueFieldParameter NewMultiLineParameter(const FString& Value);
    
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Helpshift")
    static FHelpshiftCustomIssueFieldParameter NewNumberParameter(int Value);
    
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Helpshift")
    static FHelpshiftCustomIssueFieldParameter NewDropdownParameter(const FString& Value);
    
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Helpshift")
    static FHelpshiftCustomIssueFieldParameter NewDateParameter(const FDateTime& Value);
    
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Helpshift")
    static FHelpshiftCustomIssueFieldParameter NewCheckboxParameter(bool Value);
};
