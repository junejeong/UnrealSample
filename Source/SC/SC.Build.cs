// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SC : ModuleRules
{
    public SC(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(
            new string[]
            {
                "SC",
            });

        PublicDependencyModuleNames.AddRange(
            new string[]
            {

                "Core",
                "CoreOnline",
                "CoreUObject",
                "Engine",
                "InputCore",
                "OpenSSL",
                "Niagara",
                "SignificanceManager",
                "AIModule"

            });

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Slate",
                "SlateCore",
                "OnlineSubsystem",
                "Networking",
                "Sockets",
                "EnhancedInput",
                "AudioModulation"
            });

    }
}
