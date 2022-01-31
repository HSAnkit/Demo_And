// Copyright (c) 2021 Helpshift

#pragma once

#include "HelpshiftConfigParameter.h"
#include "HelpshiftCustomIssueFieldParameter.h"

#include "Dom/JsonObject.h"

namespace HelpshiftVariantUtils
{
id VariantArrayToNSArray(const TArray<FHelpshiftConfigParameter>& ValueArray);
id VariantMapToNSDictionary(const TMap<FString, FHelpshiftConfigParameter>& ValueMap);
TArray<FHelpshiftConfigParameter> NSArrayToVariantArray(NSArray* Array);
TMap<FString, FHelpshiftConfigParameter> NSDictionaryToVariantMap(NSDictionary* Dict);
id VariantToId(const FHelpshiftConfigParameter& Value);
FHelpshiftConfigParameter IdToVariant(id Object);

id CifVariantMapToNSDictionary(const TMap<FString, FHelpshiftCustomIssueFieldParameter>& ValueMap);
id CifVariantToId(const FHelpshiftCustomIssueFieldParameter& Value);

TMap<FString, FHelpshiftConfigParameter> DeserializeJson(TSharedPtr<FJsonObject> Payload);
FHelpshiftConfigParameter DeserealizeJsonValue(TSharedPtr<FJsonValue> Value);
}
