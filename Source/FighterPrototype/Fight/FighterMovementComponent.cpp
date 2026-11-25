#include "FighterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"

UFighterMovementComponent::UFighterMovementComponent()
{
	SetPlaneConstraintNormal(FVector::RightVector);
	SetPlaneConstraintOrigin(FVector::ZeroVector);
	SetPlaneConstraintEnabled(true);
	bSnapToPlaneAtStart = true;
}

void UFighterMovementComponent::SetStageFaces(double LeftX, double RightX)
{
	check(LeftX < RightX);
	StageFaces.Emplace(LeftX, RightX);
}

bool UFighterMovementComponent::MoveUpdatedComponentImpl(const FVector& Delta, const FQuat& NewRotation,
	bool bSweep, FHitResult* OutHit, ETeleportType Teleport)
{
	FVector BoundedDelta = Delta;
	if (StageFaces.IsSet() && UpdatedComponent && CharacterOwner)
	{
		const double Radius = CharacterOwner->GetCapsuleComponent()->GetScaledCapsuleRadius();
		const double X = UpdatedComponent->GetComponentLocation().X;
		BoundedDelta.X = FMath::Clamp(X + Delta.X, StageFaces->X + Radius, StageFaces->Y - Radius) - X;
	}
	return Super::MoveUpdatedComponentImpl(BoundedDelta, NewRotation, bSweep, OutHit, Teleport);
}

void UFighterMovementComponent::OnMovementUpdated(float DeltaSeconds, const FVector& OldLocation, const FVector& OldVelocity)
{
	Super::OnMovementUpdated(DeltaSeconds, OldLocation, OldVelocity);
	Velocity.Y = 0.0;
	if (UpdatedComponent && !FMath::IsNearlyZero(UpdatedComponent->GetComponentLocation().Y))
	{
		SnapUpdatedComponentToPlane();
	}
}
