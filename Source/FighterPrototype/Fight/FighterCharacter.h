#pragma once

#include "GameFramework/Character.h"
#include "FighterCharacter.generated.h"

class USharedFighterStats;

UCLASS()
class FIGHTERPROTOTYPE_API AFighterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFighterCharacter();
	void AssignSlot(FName Slot);

private:
	UPROPERTY(VisibleInstanceOnly, Category = "Fighter")
	FName FighterSlot;

	UPROPERTY(VisibleDefaultsOnly, Category = "Fighter")
	TObjectPtr<USharedFighterStats> SharedStats;

	UPROPERTY()
	TObjectPtr<USceneComponent> CapsuleVisual;
};
