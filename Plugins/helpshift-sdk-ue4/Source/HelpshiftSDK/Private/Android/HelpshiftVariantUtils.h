// Copyright (c) 2021 Helpshift

#pragma once

#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"

#include "HelpshiftConfigParameter.h"
#include "HelpshiftCustomIssueFieldParameter.h"

namespace HelpshiftVariantUtils
{
jobject VariantArrayToJavaList(JNIEnv* Env, const TArray<FHelpshiftConfigParameter>& ValueArray);
jobject VariantMapToJavaMap(JNIEnv* Env, const TMap<FString, FHelpshiftConfigParameter>& ValueMap);
jobject VariantToJavaObject(JNIEnv* Env, const FHelpshiftConfigParameter& Value);

TArray<FHelpshiftConfigParameter> JavaListToVariantArray(JNIEnv* Env, jobject ListObject);
TMap<FString, FHelpshiftConfigParameter> JavaMapToVariantMap(JNIEnv* Env, jobject MapObject);
FHelpshiftConfigParameter JavaObjectToVariant(JNIEnv* Env, jobject Object);

jobject CifVariantMapToJavaMap(JNIEnv* Env, const TMap<FString, FHelpshiftCustomIssueFieldParameter>& ValueMap);
jobject CifVariantToJavaObject(JNIEnv* Env, const FHelpshiftCustomIssueFieldParameter& Value);
}
