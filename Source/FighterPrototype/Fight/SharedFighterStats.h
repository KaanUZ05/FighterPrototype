#pragma once

#include "Engine/DataAsset.h"
#include "SharedFighterStats.generated.h"

UCLASS()
class FIGHTERPROTOTYPE_API USharedFighterStats : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, Category = "Fighter")
	float CapsuleRadius = 38.0f;

	UPROPERTY(VisibleDefaultsOnly, Category = "Fighter")
	float StandingHalfHeight = 90.0f;

	UPROPERTY(VisibleDefaultsOnly, Category = "Fighter")
	float CrouchingHalfHeight = 52.0f;

	UPROPERTY(VisibleDefaultsOnly, Category = "Fighter")
	float ForwardWalkSpeed = 450.0f;

	UPROPERTY(VisibleDefaultsOnly, Category = "Fighter")
	float BackwardWalkSpeed = 340.0f;

	UPROPERTY(VisibleDefaultsOnly, Category = "Fighter")
	float GroundAcceleration = 2200.0f;

	UPROPERTY(VisibleDefaultsOnly, Category = "Fighter")
	float JumpApex = 140.0f;

	UPROPERTY(VisibleDefaultsOnly, Category = "Fighter")
	int32 MaxHealth = 1000;
};
