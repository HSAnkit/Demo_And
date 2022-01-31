// Copyright (c) 2021 Helpshift

#include "HelpshiftCustomIssueFieldParameter.h"

template<typename T>
T FHelpshiftCustomIssueFieldParameter::GetValue() const
{
    return Value.GetValue<T>();
}

template int64 FHelpshiftCustomIssueFieldParameter::GetValue<int64>() const;
template int FHelpshiftCustomIssueFieldParameter::GetValue<int>() const;
template bool FHelpshiftCustomIssueFieldParameter::GetValue<bool>() const;
template FString FHelpshiftCustomIssueFieldParameter::GetValue<FString>() const;

FHelpshiftCustomIssueFieldParameter UHelpshiftCustomIssueFieldParameterFunctions::NewSingleLineParameter(const FString& Value)
{
    FHelpshiftCustomIssueFieldParameter Result;
    
    Result.Type = EHelpshiftCustomIssueFieldParameterValueType::SingleLine;
    Result.Value = Value;
    
    return Result;
}

FHelpshiftCustomIssueFieldParameter UHelpshiftCustomIssueFieldParameterFunctions::NewMultiLineParameter(const FString& Value)
{
    FHelpshiftCustomIssueFieldParameter Result;
    
    Result.Type = EHelpshiftCustomIssueFieldParameterValueType::MultiLine;
    Result.Value = Value;
    
    return Result;
}

FHelpshiftCustomIssueFieldParameter UHelpshiftCustomIssueFieldParameterFunctions::NewNumberParameter(int Value)
{
    FHelpshiftCustomIssueFieldParameter Result;
    
    Result.Type = EHelpshiftCustomIssueFieldParameterValueType::Number;
    Result.Value = Value;
    
    return Result;
}

FHelpshiftCustomIssueFieldParameter UHelpshiftCustomIssueFieldParameterFunctions::NewDropdownParameter(const FString& Value)
{
    FHelpshiftCustomIssueFieldParameter Result;
    
    Result.Type = EHelpshiftCustomIssueFieldParameterValueType::Dropdown;
    Result.Value = Value;
    
    return Result;
}

FHelpshiftCustomIssueFieldParameter UHelpshiftCustomIssueFieldParameterFunctions::NewDateParameter(const FDateTime& Value)
{
    FHelpshiftCustomIssueFieldParameter Result;
    
    Result.Type = EHelpshiftCustomIssueFieldParameterValueType::Date;
    Result.Value = Value.ToUnixTimestamp() * 1000;
    
    return Result;
}

FHelpshiftCustomIssueFieldParameter UHelpshiftCustomIssueFieldParameterFunctions::NewCheckboxParameter(bool Value)
{
    FHelpshiftCustomIssueFieldParameter Result;
    
    Result.Type = EHelpshiftCustomIssueFieldParameterValueType::Checkbox;
    Result.Value = Value;
    
    return Result;
}
