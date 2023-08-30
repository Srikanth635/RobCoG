// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class UProtobuf : ModuleRules
{
    private string LibProtoForWinPathR
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/lib/Release/libprotobuf.lib")); }
    }

    private string LibProtoForLinuxPathR
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/lib/Release/libprotobuf.a")); }
    }

    private string HeaderPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/include")); }
    }

    public UProtobuf(ReadOnlyTargetRules Target) : base(Target)
	{
		// We are just setting up paths for pre-compiled binaries.
		//Type = ModuleType.External;

		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		bEnableUndefinedIdentifierWarnings = false;
		//bEnableShadowVariableWarnings = false;
        ShadowVariableWarningLevel = WarningLevel.Warning;
		//bEnableExceptions = true;

		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
                HeaderPath
            }
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
                // ... add other private include paths required here ...
                HeaderPath
            }
			);
			
		
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
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicAdditionalLibraries.Add(LibProtoForWinPathR);
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            PublicAdditionalLibraries.Add(LibProtoForLinuxPathR);
        }

    }
}
