#pragma once

#include "GameFramework/Character.h"
#include "FighterCharacter.generated.h"

class USharedFighterStats;

UCLASS()
class FIGHTERPROTOTYPE_API AFighterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFighterCharacter(const FObjectInitializer& ObjectInitializer);
	void AssignSlot(FName Slot);
	void FaceOpponent(const AFighterCharacter& Opponent);
	void MoveHorizontal(float WorldX);

protected:
	void BeginPlay() override;
	void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;

private:
	UPROPERTY(VisibleInstanceOnly, Category = "Fighter")
	FName FighterSlot;

	UPROPERTY(VisibleDefaultsOnly, Category = "Fighter")
	TObjectPtr<USharedFighterStats> SharedStats;

	UPROPERTY()
	TObjectPtr<USceneComponent> CapsuleVisual;
};
