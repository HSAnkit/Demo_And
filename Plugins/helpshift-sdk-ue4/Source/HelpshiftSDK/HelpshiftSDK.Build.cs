// Copyright (c) 2021 Helpshift

using System.IO;
using UnrealBuildTool;
using Tools.DotNETCommon;

public class HelpshiftSDK : ModuleRules
{
	public HelpshiftSDK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "Json",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
        string PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);

             // Additional routine for Android
             if (Target.Platform == UnrealTargetPlatform.Android)
             {
                 PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Android"));
                 PublicDependencyModuleNames.Add("Launch");

                 AdditionalPropertiesForReceipt.Add("AndroidPlugin", Path.Combine(PluginPath, "HelpshiftSDK_Android_UPL.xml"));
             }

             // Additional routine for iOS
             if (Target.Platform == UnrealTargetPlatform.IOS)
             {
                PublicFrameworks.AddRange (
                    new string[]
                    {
                        "UserNotifications"
                    }
                );
                 PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/IOS"));

                 PublicAdditionalFrameworks.Add(new Framework("HelpshiftX_Static", "../ThirdParty/IOS/HelpshiftX_Static.embeddedframework.zip", "HelpshiftX_Static_Resources.bundle"));

                 PrivateDependencyModuleNames.Add("Launch");
                 AdditionalPropertiesForReceipt.Add("IOSPlugin", Path.Combine(PluginPath, "HelpshiftSDK_IOS_UPL.xml"));
             }
	}
}
