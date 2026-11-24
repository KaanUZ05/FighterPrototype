#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR

#include "FighterPrototypeCharacter.h"
#include "FighterPrototypeGameMode.h"
#include "FighterPrototypePlayerController.h"
#include "GameMapsSettings.h"
#include "Misc/AutomationTest.h"
#include "Misc/PackageName.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FThirdPersonBaselineTest,
	"FighterPrototype.Smoke.ThirdPersonBaseline",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FThirdPersonBaselineTest::RunTest(const FString& Parameters)
{
	const FString ExpectedMap = TEXT("/Game/ThirdPerson/Lvl_ThirdPerson");
	const FString ExpectedGameMode = TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonGameMode.BP_ThirdPersonGameMode_C");
	const UGameMapsSettings* MapsSettings = GetDefault<UGameMapsSettings>();

	TestEqual(TEXT("Editor startup map"), MapsSettings->EditorStartupMap.GetLongPackageName(), ExpectedMap);
	TestEqual(TEXT("Game default map"), UGameMapsSettings::GetGameDefaultMap(), ExpectedMap);
	TestTrue(TEXT("ThirdPerson map package exists"), FPackageName::DoesPackageExist(ExpectedMap));

	const FString ConfiguredGameMode = UGameMapsSettings::GetGlobalDefaultGameMode();
	TestEqual(TEXT("Global default GameMode"), ConfiguredGameMode, ExpectedGameMode);
	const UClass* GameModeClass = LoadClass<AGameModeBase>(nullptr, *ConfiguredGameMode);
	if (!TestNotNull(TEXT("Configured GameMode loads"), GameModeClass))
	{
		return false;
	}

	TestTrue(TEXT("Template GameMode inherits the native ThirdPerson GameMode"),
		GameModeClass->IsChildOf(AFighterPrototypeGameMode::StaticClass()));
	const AGameModeBase* GameMode = GameModeClass->GetDefaultObject<AGameModeBase>();
	TestTrue(TEXT("Template GameMode uses a ThirdPerson pawn"),
		GameMode->DefaultPawnClass && GameMode->DefaultPawnClass->IsChildOf(AFighterPrototypeCharacter::StaticClass()));
	TestTrue(TEXT("Template GameMode uses a ThirdPerson controller"),
		GameMode->PlayerControllerClass && GameMode->PlayerControllerClass->IsChildOf(AFighterPrototypePlayerController::StaticClass()));
	return !HasAnyErrors();
}

#endif
