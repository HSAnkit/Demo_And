// Copyright (c) 2021 Helpshift

#pragma once

#include "Misc/Variant.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "HelpshiftConfigParameter.generated.h"

template<>
struct TVariantTraits<TArray<FHelpshiftConfigParameter>>
{
    static CONSTEXPR EVariantTypes GetType() { return EVariantTypes::Custom; }
};

template<>
struct TVariantTraits<TMap<FString, FHelpshiftConfigParameter>>
{
    static CONSTEXPR EVariantTypes GetType() { return EVariantTypes::Custom; }
};

UENUM(BlueprintType)
enum class EHelpshiftConfigParameterValueType : uint8
{
    Null,
    Integer,
    Float,
    Bool,
    String,
    Array,
    Map
};

/**
 * Generic value parameter that can accept different types as values.
 */
USTRUCT(BlueprintType)
struct HELPSHIFTSDK_API FHelpshiftConfigParameter
{
    GENERATED_BODY()

public:
    
    template<typename T>
    T GetValue() const;

    UPROPERTY(BlueprintReadOnly)
    EHelpshiftConfigParameterValueType Type = EHelpshiftConfigParameterValueType::Null;
    
    FVariant Value;
    
    friend FArchive& operator<<(FArchive& Ar, FHelpshiftConfigParameter& Variant)
    {
        return Ar << Variant.Type << Variant.Value;
    }
};

UCLASS(BlueprintType)
class HELPSHIFTSDK_API UHelpshiftConfigParameterFunctions : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
    
public:
    /**
    * Conterts int to Value Variant.
    */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "Integer To Value Variant", CompactNodeTitle = "->", BlueprintAutocast), Category = "Helpshift|ConfigParameter")
    static FHelpshiftConfigParameter Conv_intToHelpshiftConfigParameter(int32 Value);

    /**
    * Conterts float to Value Variant.
    */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "Float To Value Variant", CompactNodeTitle = "->", BlueprintAutocast), Category = "Helpshift|ConfigParameter")
    static FHelpshiftConfigParameter Conv_floatToHelpshiftConfigParameter(float Value);

    /**
    * Conterts bool to Value Variant.
    */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "Bool To Value Variant", CompactNodeTitle = "->", BlueprintAutocast), Category = "Helpshift|ConfigParameter")
    static FHelpshiftConfigParameter Conv_boolToHelpshiftConfigParameter(bool Value);

    /**
    * Conterts String to Value Variant.
    */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "String To Value Variant", CompactNodeTitle = "->", BlueprintAutocast), Category = "Helpshift|ConfigParameter")
    static FHelpshiftConfigParameter Conv_StringToHelpshiftConfigParameter(const FString& Value);

    /**
    * Conterts Array to Value Variant.
    */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "Array To Value Variant", CompactNodeTitle = "->", BlueprintAutocast), Category = "Helpshift|ConfigParameter")
    static FHelpshiftConfigParameter Conv_ArrayToHelpshiftConfigParameter(const TArray<FHelpshiftConfigParameter>& Value);

    /**
    * Conterts Map to Value Variant.
    */
    UFUNCTION(BlueprintPure, meta = (DisplayName = "Map To Value Variant", CompactNodeTitle = "->", BlueprintAutocast), Category = "Helpshift|ConfigParameter")
    static FHelpshiftConfigParameter Conv_MapToHelpshiftConfigParameter(const TMap<FString, FHelpshiftConfigParameter>& Value);
    
    /**
    * Get value
    *
    * @return - Integer value.
    */
    UFUNCTION(BlueprintPure, meta = (CompactNodeTitle = "Integer"), Category = "Helpshift|ConfigParameter")
    static int32 GetInteger(const FHelpshiftConfigParameter& Variant);

    /**
    * Get value
    *
    * @return - Float value.
    */
    UFUNCTION(BlueprintPure, meta = (CompactNodeTitle = "Float"), Category = "Helpshift|ConfigParameter")
    static float GetFloat(const FHelpshiftConfigParameter& Variant);

    /**
    * Get value
    *
    * @return - Boolean value.
    */
    UFUNCTION(BlueprintPure, meta = (CompactNodeTitle = "Bool"), Category = "Helpshift|ConfigParameter")
    static bool GetBool(const FHelpshiftConfigParameter& Variant);

    /**
    * Get value
    *
    * @return - String value.
    */
    UFUNCTION(BlueprintPure, meta = (CompactNodeTitle = "String"), Category = "Helpshift|ConfigParameter")
    static FString GetString(const FHelpshiftConfigParameter& Variant);

    /**
    * Get value
    *
    * @return - Array value.
    */
    UFUNCTION(BlueprintPure, meta = (CompactNodeTitle = "Array"), Category = "Helpshift|ConfigParameter")
    static TArray<FHelpshiftConfigParameter> GetArray(const FHelpshiftConfigParameter& Variant);

    /**
    * Get value
    *
    * @return - Map value.
    */
    UFUNCTION(BlueprintPure, meta = (CompactNodeTitle = "Map"), Category = "Helpshift|ConfigParameter")
    static TMap<FString, FHelpshiftConfigParameter> GetMap(const FHelpshiftConfigParameter& Variant);
};

