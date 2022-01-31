// Copyright (c) 2021 Helpshift

#pragma once

namespace HelpshiftConvertor
{
NSArray* ConvertToNSArray(const TArray<FString>& array);
NSDictionary* ConvertToNSDictionary(const TMap<FString, FString>& Map);
NSData* FromByteArray(const TArray<uint8>& Data);
};
