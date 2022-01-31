// Copyright (c) 2021 Helpshift

#include "HelpshiftVariantUtils.h"
#include "HelpshiftJavaConvertor.h"

#include "HelpshiftConfigParameter.h"
#include "HelpshiftCustomIssueFieldParameter.h"

#include "HelpshiftLog.h"

#include "Misc/DefaultValueHelper.h"

namespace HelpshiftVariantUtils
{

FString GetJavaObjectClassName(JNIEnv* Env, jobject Object);

FString GetJavaObjectClassName(JNIEnv* Env, jobject Object)
{
    jclass ObjectClass = Env->GetObjectClass(Object);
    jclass ClassClass = FJavaWrapper::FindClass(Env, "java/lang/Class", false);
    jmethodID GetNameMethod = FJavaWrapper::FindMethod(Env, ClassClass, "getName", "()Ljava/lang/String;", false);

    jstring Name = static_cast<jstring>(Env->CallObjectMethod(ObjectClass, GetNameMethod));
    const auto chars = Env->GetStringUTFChars(Name, 0);
    FString Return = FString(UTF8_TO_TCHAR(chars));
    Env->ReleaseStringUTFChars(Name, chars);

    return Return;
}

jobject VariantToJavaObject(JNIEnv* Env, const FHelpshiftConfigParameter& Value)
{
    switch (Value.Type)
    {
        case EHelpshiftConfigParameterValueType::Integer:
        {
            jclass IntegerClass = FJavaWrapper::FindClass(Env, "java/lang/Integer", false);
            jmethodID IntegerCtor = FJavaWrapper::FindMethod(Env, IntegerClass, "<init>", "(I)V", false);
            return Env->NewObject(IntegerClass, IntegerCtor, Value.GetValue<int32>());
        }
        case EHelpshiftConfigParameterValueType::Float:
        {
            jclass FloatClass = FJavaWrapper::FindClass(Env, "java/lang/Float", false);
            jmethodID FloatCtor = FJavaWrapper::FindMethod(Env, FloatClass, "<init>", "(F)V", false);
            return Env->NewObject(FloatClass, FloatCtor, Value.GetValue<float>());
        }
        case EHelpshiftConfigParameterValueType::Bool:
        {
            jclass BooleanClass = FJavaWrapper::FindClass(Env, "java/lang/Boolean", false);
            jmethodID BooleanCtor = FJavaWrapper::FindMethod(Env, BooleanClass, "<init>", "(Z)V", false);
            return Env->NewObject(BooleanClass, BooleanCtor, Value.GetValue<bool>());
        }
        case EHelpshiftConfigParameterValueType::String:
        {
            return Env->NewStringUTF(TCHAR_TO_UTF8(*Value.GetValue<FString>()));
        }
        case EHelpshiftConfigParameterValueType::Array:
        {
            return VariantArrayToJavaList(Env, Value.GetValue<TArray<FHelpshiftConfigParameter>>());
        }
        case EHelpshiftConfigParameterValueType::Map:
        {
            return VariantMapToJavaMap(Env, Value.GetValue<TMap<FString, FHelpshiftConfigParameter>>());
        }
        default:
            return nullptr;
    }
}

jobject VariantArrayToJavaList(JNIEnv* Env, const TArray<FHelpshiftConfigParameter>& ValueArray)
{
    jclass ArrayListClass = FJavaWrapper::FindClass(Env, "java/util/ArrayList", false);
    jmethodID ArrayListCtor = FJavaWrapper::FindMethod(Env, ArrayListClass, "<init>", "()V", false);
    jmethodID AddMethod = FJavaWrapper::FindMethod(Env, ArrayListClass, "add", "(Ljava/lang/Object;)Z", false);
    jobject ArrayList = Env->NewObject(ArrayListClass, ArrayListCtor);

    for (const auto& DataValue : ValueArray)
    {
        jobject Value = VariantToJavaObject(Env, DataValue);
        Env->CallBooleanMethod(ArrayList, AddMethod, Value);
        Env->DeleteLocalRef(Value);
    }

    return ArrayList;
}

jobject VariantMapToJavaMap(JNIEnv* Env, const TMap<FString, FHelpshiftConfigParameter>& ValueMap)
{
    jclass HashMapClass = FJavaWrapper::FindClass(Env, "java/util/HashMap", false);
    jmethodID HasMapCtor = FJavaWrapper::FindMethod(Env, HashMapClass, "<init>", "()V", false);
    jmethodID PutMethod = FJavaWrapper::FindMethod(Env, HashMapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;", false);
    jobject HashMap = Env->NewObject(HashMapClass, HasMapCtor);

    for (const auto& DataPair : ValueMap)
    {
        jobject Key = Env->NewStringUTF(TCHAR_TO_UTF8(*DataPair.Key));
        jobject Value = VariantToJavaObject(Env, DataPair.Value);
        jobject PrevValue = Env->CallObjectMethod(HashMap, PutMethod, Key, Value);

        if (PrevValue) Env->DeleteLocalRef(PrevValue);
        Env->DeleteLocalRef(Key);
        Env->DeleteLocalRef(Value);
    }

    return HashMap;
}

TArray<FHelpshiftConfigParameter> JavaListToVariantArray(JNIEnv* Env, jobject ListObject)
{
    jclass ListClass = FJavaWrapper::FindClass(Env, "java/util/List", false);
    jmethodID SizeMethod = FJavaWrapper::FindMethod(Env, ListClass, "size", "()I", false);
    jmethodID GeteMethod = FJavaWrapper::FindMethod(Env, ListClass, "get", "(I)Ljava/lang/Object;", false);

    const int Size = Env->CallIntMethod(ListObject, SizeMethod);
    TArray<FHelpshiftConfigParameter> VariantArray;

    for (int i = 0; i < Size; i++)
    {
        jobject ArrayItem = Env->CallObjectMethod(ListObject, GeteMethod, i);
        VariantArray.Add(JavaObjectToVariant(Env, ArrayItem));
        Env->DeleteLocalRef(ArrayItem);
    }

    return VariantArray;
}

TMap<FString, FHelpshiftConfigParameter> JavaMapToVariantMap(JNIEnv* Env, jobject MapObject)
{
    jclass MapClass = FJavaWrapper::FindClass(Env, "java/util/Map", false);
    jmethodID KeySetMethod = FJavaWrapper::FindMethod(Env, MapClass, "keySet", "()Ljava/util/Set;", false);
    jmethodID GetMethod = FJavaWrapper::FindMethod(Env, MapClass, "get", "(Ljava/lang/Object;)Ljava/lang/Object;", false);

    jclass SetClass = FJavaWrapper::FindClass(Env, "java/util/Set", false);
    jmethodID IteratorMethod = FJavaWrapper::FindMethod(Env, SetClass, "iterator", "()Ljava/util/Iterator;", false);

    jclass IteratorClass = FJavaWrapper::FindClass(Env, "java/util/Iterator", false);
    jmethodID HasNextMethod = FJavaWrapper::FindMethod(Env, IteratorClass, "hasNext", "()Z", false);
    jmethodID NextMethod = FJavaWrapper::FindMethod(Env, IteratorClass, "next", "()Ljava/lang/Object;", false);

    jobject KeySet = Env->CallObjectMethod(MapObject, KeySetMethod);
    jobject Iter = Env->CallObjectMethod(KeySet, IteratorMethod);

    TMap<FString, FHelpshiftConfigParameter> VariantMap;
    while (Env->CallBooleanMethod(Iter, HasNextMethod))
    {
        jobject Key = Env->CallObjectMethod(Iter, NextMethod);
        jobject Value = Env->CallObjectMethod(MapObject, GetMethod, Key);

        FHelpshiftConfigParameter Variant = JavaObjectToVariant(Env, Value);

        if (Variant.Type != EHelpshiftConfigParameterValueType::Null)
        {
            VariantMap.Add(FJavaHelper::FStringFromLocalRef(Env, static_cast<jstring>(Key)), Variant);
        }

        Env->DeleteLocalRef(Value);
    }

    Env->DeleteLocalRef(KeySet);
    Env->DeleteLocalRef(Iter);

    return VariantMap;
}

FHelpshiftConfigParameter JavaObjectToVariant(JNIEnv* Env, jobject Object)
{
    FHelpshiftConfigParameter Variant;
    if (Object == nullptr) return Variant;

    jclass IntegerClass = FJavaWrapper::FindClass(Env, "java/lang/Integer", false);
    if (Env->IsInstanceOf(Object, IntegerClass))
    {
        jmethodID GetIntMethod = FJavaWrapper::FindMethod(Env, IntegerClass, "intValue", "()I", false);

        Variant.Type = EHelpshiftConfigParameterValueType::Integer;
        Variant.Value = Env->CallIntMethod(Object, GetIntMethod);
        return Variant;
    }

    jclass LongClass = FJavaWrapper::FindClass(Env, "java/lang/Long", false);
    if (Env->IsInstanceOf(Object, LongClass))
    {
        jmethodID GetLongMethod = FJavaWrapper::FindMethod(Env, LongClass, "longValue", "()J", false);

        Variant.Type = EHelpshiftConfigParameterValueType::Integer;
        Variant.Value = (int32)Env->CallLongMethod(Object, GetLongMethod);
        return Variant;
    }

    jclass FloatClass = FJavaWrapper::FindClass(Env, "java/lang/Float", false);
    if (Env->IsInstanceOf(Object, FloatClass))
    {
        jmethodID GetFloatMethod = FJavaWrapper::FindMethod(Env, FloatClass, "floatValue", "()F", false);

        Variant.Type = EHelpshiftConfigParameterValueType::Float;
        Variant.Value = Env->CallFloatMethod(Object, GetFloatMethod);
        return Variant;
    }

    jclass DoubleClass = FJavaWrapper::FindClass(Env, "java/lang/Double", false);
    if (Env->IsInstanceOf(Object, DoubleClass))
    {
        jmethodID GetDoubleMethod = FJavaWrapper::FindMethod(Env, DoubleClass, "doubleValue", "()D", false);

        Variant.Type = EHelpshiftConfigParameterValueType::Float;
        Variant.Value = (float)Env->CallDoubleMethod(Object, GetDoubleMethod);
        return Variant;
    }

    jclass BooleanClass = FJavaWrapper::FindClass(Env, "java/lang/Boolean", false);
    if (Env->IsInstanceOf(Object, BooleanClass))
    {
        jmethodID GetBoolMethod = FJavaWrapper::FindMethod(Env, BooleanClass, "booleanValue", "()Z", false);

        Variant.Type = EHelpshiftConfigParameterValueType::Bool;
        Variant.Value = (bool)Env->CallBooleanMethod(Object, GetBoolMethod);
        return Variant;
    }

    jclass StringClass = FJavaWrapper::FindClass(Env, "java/lang/String", false);
    if (Env->IsInstanceOf(Object, StringClass))
    {
        Variant.Type = EHelpshiftConfigParameterValueType::String;
        jstring StringObject = static_cast<jstring>(Object);
        const auto chars = Env->GetStringUTFChars(StringObject, 0);
        Variant.Value = FString(UTF8_TO_TCHAR(chars));
        Env->ReleaseStringUTFChars(StringObject, chars);
        return Variant;
    }

    jclass ListClass = FJavaWrapper::FindClass(Env, "java/util/List", false);
    if (Env->IsInstanceOf(Object, ListClass))
    {
        Variant.Type = EHelpshiftConfigParameterValueType::Array;
        Variant.Value = JavaListToVariantArray(Env, Object);
        return Variant;
    }

    jclass HashMapClass = FJavaWrapper::FindClass(Env, "java/util/HashMap", false);
    if (Env->IsInstanceOf(Object, HashMapClass))
    {
        Variant.Type = EHelpshiftConfigParameterValueType::Map;
        Variant.Value = JavaMapToVariantMap(Env, Object);
        return Variant;
    }

    UE_LOG(LogHelpshift, Warning, TEXT("Java class %s cannot be converted to a variant"), *GetJavaObjectClassName(Env, Object));

    return Variant;
}

jobject CifVariantToJavaObject(JNIEnv* Env, const FHelpshiftCustomIssueFieldParameter& Value)
{
    jclass HashMapClass = FJavaWrapper::FindClass(Env, "java/util/HashMap", false);
    jmethodID HasMapCtor = FJavaWrapper::FindMethod(Env, HashMapClass, "<init>", "()V", false);
    jmethodID PutMethod = FJavaWrapper::FindMethod(Env, HashMapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;", false);
    jobject HashMap = Env->NewObject(HashMapClass, HasMapCtor);
    
    jobject Type, JavaValue, TypeKey, ValueKey;
    
    switch (Value.Type)
    {
        case EHelpshiftCustomIssueFieldParameterValueType::SingleLine:
        {
            Type = Env->NewStringUTF(TCHAR_TO_UTF8(*FString("singleline")));
            JavaValue = Env->NewStringUTF(TCHAR_TO_UTF8(*Value.GetValue<FString>()));
            break;
        }
        case EHelpshiftCustomIssueFieldParameterValueType::MultiLine:
        {
            Type = Env->NewStringUTF(TCHAR_TO_UTF8(*FString("multiline")));
            JavaValue = Env->NewStringUTF(TCHAR_TO_UTF8(*Value.GetValue<FString>()));
            break;
        }
        case EHelpshiftCustomIssueFieldParameterValueType::Number:
        {
            FString NumberString = FString::FromInt(Value.GetValue<int>());
            
            Type = Env->NewStringUTF(TCHAR_TO_UTF8(*FString("number")));
            JavaValue = Env->NewStringUTF(TCHAR_TO_UTF8(*NumberString));
            break;
        }
        case EHelpshiftCustomIssueFieldParameterValueType::Dropdown:
        {
            Type = Env->NewStringUTF(TCHAR_TO_UTF8(*FString("dropdown")));
            JavaValue = Env->NewStringUTF(TCHAR_TO_UTF8(*Value.GetValue<FString>()));
            break;
        }
        case EHelpshiftCustomIssueFieldParameterValueType::Date:
        {
            Type = Env->NewStringUTF(TCHAR_TO_UTF8(*FString("date")));
            
            jclass LongClass = FJavaWrapper::FindClass(Env, "java/lang/Long", false);
            jmethodID LongCtor = FJavaWrapper::FindMethod(Env, LongClass, "<init>", "(J)V", false);
            JavaValue = Env->NewObject(LongClass, LongCtor, Value.GetValue<int64>());
            break;
        }
        case EHelpshiftCustomIssueFieldParameterValueType::Checkbox:
        {
            Type = Env->NewStringUTF(TCHAR_TO_UTF8(*FString("checkbox")));
            JavaValue = Env->NewStringUTF(TCHAR_TO_UTF8(*(Value.GetValue<bool>() ? FString("true") : FString("false"))));
            break;
        }
        default:
        {
            return HashMap;
        }
    }
    
    TypeKey = Env->NewStringUTF(TCHAR_TO_UTF8(*FString("type")));
    ValueKey = Env->NewStringUTF(TCHAR_TO_UTF8(*FString("value")));
    
    jobject PrevValue = Env->CallObjectMethod(HashMap, PutMethod, TypeKey, Type);

    if (PrevValue) Env->DeleteLocalRef(PrevValue);
    Env->DeleteLocalRef(TypeKey);
    Env->DeleteLocalRef(Type);
    
    PrevValue = Env->CallObjectMethod(HashMap, PutMethod, ValueKey, JavaValue);

    if (PrevValue) Env->DeleteLocalRef(PrevValue);
    Env->DeleteLocalRef(ValueKey);
    Env->DeleteLocalRef(JavaValue);
    
    return HashMap;
}

jobject CifVariantMapToJavaMap(JNIEnv* Env, const TMap<FString, FHelpshiftCustomIssueFieldParameter>& ValueMap)
{
    jclass HashMapClass = FJavaWrapper::FindClass(Env, "java/util/HashMap", false);
    jmethodID HasMapCtor = FJavaWrapper::FindMethod(Env, HashMapClass, "<init>", "()V", false);
    jmethodID PutMethod = FJavaWrapper::FindMethod(Env, HashMapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;", false);
    jobject HashMap = Env->NewObject(HashMapClass, HasMapCtor);

    for (const auto& DataPair : ValueMap)
    {
        if (DataPair.Value.Type == EHelpshiftCustomIssueFieldParameterValueType::Null)
        {
            continue;
        }
        
        jobject Key = Env->NewStringUTF(TCHAR_TO_UTF8(*DataPair.Key));
        jobject Value = CifVariantToJavaObject(Env, DataPair.Value);
        
        jobject PrevValue = Env->CallObjectMethod(HashMap, PutMethod, Key, Value);

        if (PrevValue) Env->DeleteLocalRef(PrevValue);
        Env->DeleteLocalRef(Key);
        Env->DeleteLocalRef(Value);
    }

    return HashMap;
}

}
