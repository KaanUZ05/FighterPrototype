#pragma once

#include "GameFramework/GameModeBase.h"
#include "FightGameMode.generated.h"

class AFighterCharacter;
class AFightCameraActor;
class APlayerStart;

UCLASS()
class FIGHTERPROTOTYPE_API AFightGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFightGameMode();
	void StartPlay() override;
	void RestartPlayer(AController* NewPlayer) override;
	void Tick(float DeltaSeconds) override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	APlayerStart* FindSlotStart(FName Slot) const;
	void InitializeFighter(AFighterCharacter& Fighter, FName Slot) const;
	void UpdateFightView();
	void SetSharedView(APlayerController& Controller) const;

	UPROPERTY(Transient)
	TObjectPtr<AFighterCharacter> FighterA;

	UPROPERTY(Transient)
	TObjectPtr<AFighterCharacter> FighterB;

	UPROPERTY(Transient)
	TObjectPtr<AFightCameraActor> FightCamera;

	bool bChangedSplitScreenOverride = false;
	bool bPreviousSplitScreenOverride = false;
};
