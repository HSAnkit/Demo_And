// Copyright (c) 2021 Helpshift

#include "HelpshiftVariantUtils.h"

#include "HelpshiftLog.h"

#include "Misc/DefaultValueHelper.h"

namespace HelpshiftVariantUtils
{
id VariantToId(const FHelpshiftConfigParameter& Value)
{
    switch (Value.Type)
    {
        case EHelpshiftConfigParameterValueType::Null:
        {
            return nullptr;
        }
        case EHelpshiftConfigParameterValueType::Integer:
        {
            return [NSNumber numberWithInt:Value.GetValue<int32>()];
        }
        case EHelpshiftConfigParameterValueType::Float:
        {
            return [NSNumber numberWithFloat:Value.GetValue<float>()];
        }
        case EHelpshiftConfigParameterValueType::Bool:
        {
            return Value.GetValue<bool>() ? @YES : @NO;
        }
        case EHelpshiftConfigParameterValueType::String:
        {
            return Value.GetValue<FString>().GetNSString();
        }
        case EHelpshiftConfigParameterValueType::Array:
        {
            return VariantArrayToNSArray(Value.GetValue<TArray<FHelpshiftConfigParameter>>());
        }
        case EHelpshiftConfigParameterValueType::Map:
        {
            return VariantMapToNSDictionary(Value.GetValue<TMap<FString, FHelpshiftConfigParameter>>());
        }
        default:
            return nullptr;
    }
}

FHelpshiftConfigParameter IdToVariant(id Object)
{
    FHelpshiftConfigParameter Variant;
    if (Object == nil || Object == [NSNull null])
        return Variant;

    if ([Object isKindOfClass:[NSNumber class]])
    {
        NSNumber* Number = (NSNumber*)Object;
        const char* Type = [Object objCType];

        if (strcmp(Type, @encode(float)) == 0 ||
            strcmp(Type, @encode(double)) == 0)
        {
            Variant.Type = EHelpshiftConfigParameterValueType::Float;
            Variant.Value = (float)Number.floatValue;
            return Variant;
        }

        else if (strcmp(Type, @encode(BOOL)) == 0 ||
                 strcmp(Type, @encode(signed char)) == 0)
        {
            Variant.Type = EHelpshiftConfigParameterValueType::Bool;
            Variant.Value = Number.boolValue == YES ? true : false;
            return Variant;
        }

        else
        {
            Variant.Type = EHelpshiftConfigParameterValueType::Integer;
            Variant.Value = (int32)Number.intValue;
            return Variant;
        }
    }

    if ([Object isKindOfClass:[NSString class]])
    {
        Variant.Type = EHelpshiftConfigParameterValueType::String;
        Variant.Value = FString((NSString*)Object);
        return Variant;
    }

    if ([Object isKindOfClass:[NSArray class]])
    {
        Variant.Type = EHelpshiftConfigParameterValueType::Array;
        Variant.Value = NSArrayToVariantArray(Object);
        return Variant;
    }

    if ([Object isKindOfClass:[NSDictionary class]])
    {
        Variant.Type = EHelpshiftConfigParameterValueType::Map;
        Variant.Value = NSDictionaryToVariantMap(Object);
        return Variant;
    }

    const FString ClassName(NSStringFromClass([Object class]));
    UE_LOG(LogHelpshift, Warning, TEXT("NSObject of type %s cannot be converted to a variant"), *ClassName);
    return Variant;
}

id VariantArrayToNSArray(const TArray<FHelpshiftConfigParameter>& ValueArray)
{
    NSMutableArray* Array = [NSMutableArray arrayWithCapacity:ValueArray.Num()];
    for (const auto& DataValue : ValueArray)
    {
        [Array addObject:VariantToId(DataValue)];
    }

    return Array;
}

id VariantMapToNSDictionary(const TMap<FString, FHelpshiftConfigParameter>& ValueMap)
{
    NSDictionary* Dict = [NSMutableDictionary dictionaryWithCapacity:ValueMap.Num()];
    for (const auto& DataPair : ValueMap)
    {
        [Dict setValue:VariantToId(DataPair.Value) forKey:DataPair.Key.GetNSString()];
    }

    return Dict;
}

TArray<FHelpshiftConfigParameter> NSArrayToVariantArray(NSArray* Array)
{
    TArray<FHelpshiftConfigParameter> VariantArray;

    for (id Object in Array)
    {
        VariantArray.Add(IdToVariant(Object));
    }

    return VariantArray;
}

TMap<FString, FHelpshiftConfigParameter> NSDictionaryToVariantMap(NSDictionary* Dict)
{
    TMap<FString, FHelpshiftConfigParameter> VariantMap;
    for (id Key in Dict)
    {
        id Value = [Dict objectForKey:Key];
        FHelpshiftConfigParameter Variant = IdToVariant(Value);
        if (Variant.Type != EHelpshiftConfigParameterValueType::Null)
        {
            VariantMap.Add(FString((NSString*)Key), Variant);
        }
    }

    return VariantMap;
}

id CifVariantMapToNSDictionary(const TMap<FString, FHelpshiftCustomIssueFieldParameter>& ValueMap)
{
    NSMutableDictionary* Dict = [NSMutableDictionary dictionaryWithCapacity:ValueMap.Num()];
    for (const auto& DataPair : ValueMap)
    {
        [Dict setValue:CifVariantToId(DataPair.Value) forKey:DataPair.Key.GetNSString()];
    }

    return Dict;
}

id CifVariantToId(const FHelpshiftCustomIssueFieldParameter& Value)
{
    NSMutableDictionary* Dict = [NSMutableDictionary dictionary];
    
    switch (Value.Type)
    {
        case EHelpshiftCustomIssueFieldParameterValueType::SingleLine:
        {
            Dict[@"type"] = @"singleline";
            Dict[@"value"] = Value.GetValue<FString>().GetNSString();
            break;
        }
        case EHelpshiftCustomIssueFieldParameterValueType::MultiLine:
        {
            Dict[@"type"] = @"multiline";
            Dict[@"value"] = Value.GetValue<FString>().GetNSString();
            break;
        }
        case EHelpshiftCustomIssueFieldParameterValueType::Number:
        {
            Dict[@"type"] = @"number";
            Dict[@"value"] = FString::FromInt(Value.GetValue<int>()).GetNSString();
            break;
        }
        case EHelpshiftCustomIssueFieldParameterValueType::Dropdown:
        {
            Dict[@"type"] = @"dropdown";
            Dict[@"value"] = Value.GetValue<FString>().GetNSString();
            break;
        }
        case EHelpshiftCustomIssueFieldParameterValueType::Date:
        {
            int64 Date = Value.GetValue<int64>();
            
            Dict[@"type"] = @"date";
            Dict[@"value"] = [NSNumber numberWithLong:Date];
            break;
        }
        case EHelpshiftCustomIssueFieldParameterValueType::Checkbox:
        {
            Dict[@"type"] = @"checkbox";
            Dict[@"value"] = Value.GetValue<bool>() ? @YES: @NO;
            break;
        }
        default:
        {
            return Dict;
        }
    }
    
    return Dict;
}

TMap<FString, FHelpshiftConfigParameter> DeserializeJson(TSharedPtr<FJsonObject> Payload)
{
    TMap<FString, FHelpshiftConfigParameter> Result;
    
    for (auto KeyValuePair : Payload->Values) {
        FHelpshiftConfigParameter Parameter = DeserealizeJsonValue(KeyValuePair.Value);
        
        if (Parameter.Type != EHelpshiftConfigParameterValueType::Null) {
            Result.Add(KeyValuePair.Key, Parameter);
        }
    }
    
    return Result;
}

FHelpshiftConfigParameter DeserealizeJsonValue(TSharedPtr<FJsonValue> Value)
{
    FHelpshiftConfigParameter Parameter;
    
    switch (Value->Type) {
        case EJson::String: {
            Parameter.Value = Value->AsString();
            Parameter.Type = EHelpshiftConfigParameterValueType::String;
            break;
        }
        case EJson::Number: {
            Parameter.Value = (float) Value->AsNumber();
            Parameter.Type = EHelpshiftConfigParameterValueType::Float;
            break;
        }
        case EJson::Boolean: {
            Parameter.Value = Value->AsBool();
            Parameter.Type = EHelpshiftConfigParameterValueType::Bool;
            break;
        }
        case EJson::Array: {
            TArray<FHelpshiftConfigParameter> Parameters;
            for (auto Element : Value->AsArray()) {
                FHelpshiftConfigParameter ArrayElement = DeserealizeJsonValue(Element);
                Parameters.Add(ArrayElement);
            }
            
            Parameter.Value = Parameters;
            Parameter.Type = EHelpshiftConfigParameterValueType::Array;
            break;
        }
        case EJson::Object: {
            TMap<FString, FHelpshiftConfigParameter> Map = DeserializeJson(Value->AsObject());
            
            Parameter.Value = Map;
            Parameter.Type = EHelpshiftConfigParameterValueType::Map;
            break;
        }
    }
    
    return Parameter;
}

}
