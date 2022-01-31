// Copyright (c) 2021 Helpshift

#include "HelpshiftConvertor.h"

namespace HelpshiftConvertor
{

NSArray* ConvertToNSArray(const TArray<FString>& array)
{
    NSMutableArray *outArray = [NSMutableArray new];

    for(int i = 0; i < array.Num(); i++)
    {
        NSString *recipientStr = array[i].GetNSString();
        [outArray addObject:recipientStr];
    }

    return outArray;
}

NSDictionary* ConvertToNSDictionary(const TMap<FString, FString>& Map)
{
    NSDictionary* Dict = [NSMutableDictionary dictionary];
    
    for (const auto& DataPair : Map)
    {
        [Dict setValue:DataPair.Value.GetNSString() forKey:DataPair.Key.GetNSString()];
    }
    
    return Dict;
}

NSData* FromByteArray(const TArray<uint8>& Data)
{
    uint8* bytes = (uint8*)malloc(Data.Num());
    
    for (int i = 0; i < Data.Num(); i++) {
        bytes[i] = Data[i];
    }
    
    return [NSData dataWithBytes:bytes length:Data.Num()];
}

}
