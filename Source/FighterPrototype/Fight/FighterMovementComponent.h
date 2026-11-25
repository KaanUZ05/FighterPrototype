#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "FighterMovementComponent.generated.h"

UCLASS()
class FIGHTERPROTOTYPE_API UFighterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UFighterMovementComponent();
	void SetStageFaces(double LeftX, double RightX);

protected:
	bool MoveUpdatedComponentImpl(const FVector& Delta, const FQuat& NewRotation, bool bSweep,
		FHitResult* OutHit, ETeleportType Teleport) override;
	void OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity) override;

private:
	TOptional<FVector2D> StageFaces;
};
