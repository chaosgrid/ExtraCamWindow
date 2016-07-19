
using UnrealBuildTool;

public class ExtraCamWindow : ModuleRules
{
	public ExtraCamWindow(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Slate", "SlateCore", "UMG" });

        //Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");
        //if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
        //{
        //    if (UEBuildConfiguration.bCompileSteamOSS == true)
        //    {
        //        DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
        //    }
        //}
    }
}
