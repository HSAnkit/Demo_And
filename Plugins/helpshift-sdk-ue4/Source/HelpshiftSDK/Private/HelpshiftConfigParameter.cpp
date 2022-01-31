// Copyright (c) 2021 Helpshift

#include "HelpshiftConfigParameter.h"

#include "HelpshiftLog.h"

template<typename T>
T FHelpshiftConfigParameter::GetValue() const
{
    return Value.GetValue<T>();
}

template int32 FHelpshiftConfigParameter::GetValue<int32>() const;
template float FHelpshiftConfigParameter::GetValue<float>() const;
template bool FHelpshiftConfigParameter::GetValue<bool>() const;
template FString FHelpshiftConfigParameter::GetValue<FString>() const;
template TArray<FHelpshiftConfigParameter> FHelpshiftConfigParameter::GetValue<TArray<FHelpshiftConfigParameter>>() const;
template TMap<FString, FHelpshiftConfigParameter> FHelpshiftConfigParameter::GetValue<TMap<FString, FHelpshiftConfigParameter>>() const;

FHelpshiftConfigParameter UHelpshiftConfigParameterFunctions::Conv_intToHelpshiftConfigParameter(int32 Value)
{
    FHelpshiftConfigParameter Result;
    
    Result.Type = EHelpshiftConfigParameterValueType::Integer;
    Result.Value = Value;
    
    return Result;
}

FHelpshiftConfigParameter UHelpshiftConfigParameterFunctions::Conv_floatToHelpshiftConfigParameter(float Value)
{
    FHelpshiftConfigParameter Result;
    
    Result.Type = EHelpshiftConfigParameterValueType::Float;
    Result.Value = Value;
    
    return Result;
}

FHelpshiftConfigParameter UHelpshiftConfigParameterFunctions::Conv_boolToHelpshiftConfigParameter(bool Value)
{
    FHelpshiftConfigParameter Result;
    
    Result.Type = EHelpshiftConfigParameterValueType::Bool;
    Result.Value = Value;
    
    return Result;
}

FHelpshiftConfigParameter UHelpshiftConfigParameterFunctions::Conv_StringToHelpshiftConfigParameter(const FString& Value)
{
    FHelpshiftConfigParameter Result;
    
    Result.Type = EHelpshiftConfigParameterValueType::String;
    Result.Value = Value;
    
    return Result;
}

FHelpshiftConfigParameter UHelpshiftConfigParameterFunctions::Conv_ArrayToHelpshiftConfigParameter(const TArray<FHelpshiftConfigParameter>& Value)
{
    FHelpshiftConfigParameter Result;
    
    Result.Type = EHelpshiftConfigParameterValueType::Array;
    Result.Value = Value;
    
    return Result;
}

FHelpshiftConfigParameter UHelpshiftConfigParameterFunctions::Conv_MapToHelpshiftConfigParameter(const TMap<FString, FHelpshiftConfigParameter>& Value)
{
    FHelpshiftConfigParameter Result;
    
    Result.Type = EHelpshiftConfigParameterValueType::Map;
    Result.Value = Value;
    
    return Result;
}

int32 UHelpshiftConfigParameterFunctions::GetInteger(const FHelpshiftConfigParameter& Variant)
{
    if (Variant.Type != EHelpshiftConfigParameterValueType::Integer)
    {
        UE_LOG(LogHelpshift, Warning, TEXT("Variant does not contain an integer value. Returning default value."));
        return 0;
    }

    return Variant.GetValue<int32>();
}

float UHelpshiftConfigParameterFunctions::GetFloat(const FHelpshiftConfigParameter& Variant)
{
    if (Variant.Type != EHelpshiftConfigParameterValueType::Float)
    {
        UE_LOG(LogHelpshift, Warning, TEXT("Variant does not contain a float value. Returning default value."));
        return 0.0;
    }

    return Variant.GetValue<float>();
}

bool UHelpshiftConfigParameterFunctions::GetBool(const FHelpshiftConfigParameter& Variant)
{
    if (Variant.Type != EHelpshiftConfigParameterValueType::Bool)
    {
        UE_LOG(LogHelpshift, Warning, TEXT("Variant does not contain a bool value. Returning default value."));
        return false;
    }

    return Variant.GetValue<bool>();
}

FString UHelpshiftConfigParameterFunctions::GetString(const FHelpshiftConfigParameter& Variant)
{
    if (Variant.Type != EHelpshiftConfigParameterValueType::String)
    {
        UE_LOG(LogHelpshift, Warning, TEXT("Variant does not contain a string value. Returning empty string."));
        return FString();
    }

    return Variant.GetValue<FString>();
}

TArray<FHelpshiftConfigParameter> UHelpshiftConfigParameterFunctions::GetArray(const FHelpshiftConfigParameter& Variant)
{
    if (Variant.Type != EHelpshiftConfigParameterValueType::Array)
    {
        UE_LOG(LogHelpshift, Warning, TEXT("Variant does not contain an array value. Returning empty array."));
        return TArray<FHelpshiftConfigParameter>();
    }

    return Variant.GetValue<TArray<FHelpshiftConfigParameter>>();
}

TMap<FString, FHelpshiftConfigParameter> UHelpshiftConfigParameterFunctions::GetMap(const FHelpshiftConfigParameter& Variant)
{
    if (Variant.Type != EHelpshiftConfigParameterValueType::Map)
    {
        UE_LOG(LogHelpshift, Warning, TEXT("Variant does not contain a map value. Returning empty map."));
        return TMap<FString, FHelpshiftConfigParameter>();
    }

    return Variant.GetValue<TMap<FString, FHelpshiftConfigParameter>>();
}
