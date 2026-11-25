#pragma once

#include "GameFramework/GameModeBase.h"
#include "FightGameMode.generated.h"

class AFighterCharacter;
class APlayerStart;

UCLASS()
class FIGHTERPROTOTYPE_API AFightGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFightGameMode();
	void StartPlay() override;
	void RestartPlayer(AController* NewPlayer) override;

private:
	APlayerStart* FindSlotStart(FName Slot) const;
	void InitializeFighter(AFighterCharacter& Fighter, FName Slot) const;

	UPROPERTY(Transient)
	TObjectPtr<AFighterCharacter> FighterA;

	UPROPERTY(Transient)
	TObjectPtr<AFighterCharacter> FighterB;
};
