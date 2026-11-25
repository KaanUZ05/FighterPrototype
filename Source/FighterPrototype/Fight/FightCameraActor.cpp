#include "FightCameraActor.h"
#include "Camera/CameraComponent.h"

AFightCameraActor::AFightCameraActor()
{
	UCameraComponent* View = GetCameraComponent();
	View->ProjectionMode = ECameraProjectionMode::Orthographic;
	View->SetAspectRatio(16.0f / 9.0f);
	View->bConstrainAspectRatio = true;
}

void AFightCameraActor::FrameFighters(const FVector& A, const FVector& B)
{
	UCameraComponent* View = GetCameraComponent();
	const double Width = FMath::Max3(940.0, FMath::Abs(A.X - B.X) + 340.0,
		(FMath::Abs(A.Z - B.Z) + 300.0) * View->AspectRatio);
	View->SetOrthoWidth(static_cast<float>(Width));

	const FVector Midpoint = (A + B) * 0.5;
	SetActorLocationAndRotation(FVector(Midpoint.X, 1800.0, Midpoint.Z + 50.0), FRotator(0.0, -90.0, 0.0));
}
