#pragma once

#include "Camera/CameraActor.h"
#include "FightCameraActor.generated.h"

UCLASS()
class FIGHTERPROTOTYPE_API AFightCameraActor : public ACameraActor
{
	GENERATED_BODY()

public:
	AFightCameraActor();
	void FrameFighters(const FVector& A, const FVector& B);
};
