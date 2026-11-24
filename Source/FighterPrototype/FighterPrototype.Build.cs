// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FighterPrototype : ModuleRules
{
	public FighterPrototype(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.Add("EngineSettings");

		PublicIncludePaths.AddRange(new string[] {
			"FighterPrototype",
			"FighterPrototype/Variant_Platforming",
			"FighterPrototype/Variant_Platforming/Animation",
			"FighterPrototype/Variant_Combat",
			"FighterPrototype/Variant_Combat/AI",
			"FighterPrototype/Variant_Combat/Animation",
			"FighterPrototype/Variant_Combat/Gameplay",
			"FighterPrototype/Variant_Combat/Interfaces",
			"FighterPrototype/Variant_Combat/UI",
			"FighterPrototype/Variant_SideScrolling",
			"FighterPrototype/Variant_SideScrolling/AI",
			"FighterPrototype/Variant_SideScrolling/Gameplay",
			"FighterPrototype/Variant_SideScrolling/Interfaces",
			"FighterPrototype/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
