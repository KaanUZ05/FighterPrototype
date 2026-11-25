#include "FighterCharacter.h"
#include "FighterMovementComponent.h"
#include "SharedFighterStats.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"

AFighterCharacter::AFighterCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UFighterMovementComponent>(CharacterMovementComponentName))
{
	SharedStats = GetMutableDefault<USharedFighterStats>();
	const float Radius = SharedStats->CapsuleRadius;
	const float HalfHeight = SharedStats->StandingHalfHeight;
	GetCapsuleComponent()->InitCapsuleSize(Radius, HalfHeight);
	GetCapsuleComponent()->CanCharacterStepUpOn = ECB_No;
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->bRunPhysicsWithNoController = true;
	Movement->MaxWalkSpeed = SharedStats->ForwardWalkSpeed;
	Movement->MaxAcceleration = SharedStats->GroundAcceleration;
	Movement->SetCrouchedHalfHeight(SharedStats->CrouchingHalfHeight);
	Movement->GetNavAgentPropertiesRef().bCanCrouch = true;
	bUseControllerRotationYaw = false;

	CapsuleVisual = CreateDefaultSubobject<USceneComponent>(TEXT("CapsuleVisual"));
	CapsuleVisual->SetupAttachment(GetCapsuleComponent());

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cylinder(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	const float DiameterScale = Radius / 50.0f;
	const float CapOffset = HalfHeight - Radius;
	const auto AddVisualPart = [this, DiameterScale](FName Name, UStaticMesh* VisualMesh, float Z, float HeightScale)
	{
		UStaticMeshComponent* Part = CreateDefaultSubobject<UStaticMeshComponent>(Name);
		Part->SetupAttachment(CapsuleVisual);
		Part->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Part->SetGenerateOverlapEvents(false);
		Part->SetCanEverAffectNavigation(false);
		Part->SetStaticMesh(VisualMesh);
		Part->SetRelativeLocation(FVector(0.0, 0.0, Z));
		Part->SetRelativeScale3D(FVector(DiameterScale, DiameterScale, HeightScale));
	};
	AddVisualPart(TEXT("CapsuleBody"), Cylinder.Object, 0.0f, CapOffset / 50.0f);
	AddVisualPart(TEXT("CapsuleTop"), Sphere.Object, CapOffset, DiameterScale);
	AddVisualPart(TEXT("CapsuleBottom"), Sphere.Object, -CapOffset, DiameterScale);
}

void AFighterCharacter::AssignSlot(FName Slot)
{
	FighterSlot = Slot;
}

void AFighterCharacter::FaceOpponent(const AFighterCharacter& Opponent)
{
	const double DeltaX = Opponent.GetActorLocation().X - GetActorLocation().X;
	if (FMath::Abs(DeltaX) > 1.0 && DeltaX * GetActorForwardVector().X < 0.0)
	{
		SetActorRotation(FRotator(0.0, DeltaX > 0.0 ? 0.0 : 180.0, 0.0));
	}
}

void AFighterCharacter::BeginPlay()
{
	Super::BeginPlay();
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->JumpZVelocity = FMath::Sqrt(2.0f * FMath::Abs(Movement->GetGravityZ()) * SharedStats->JumpApex);
}

void AFighterCharacter::MoveHorizontal(float WorldX)
{
	const bool bForward = WorldX * GetActorForwardVector().X > 0.0;
	GetCharacterMovement()->MaxWalkSpeed = bForward ? SharedStats->ForwardWalkSpeed : SharedStats->BackwardWalkSpeed;
	AddMovementInput(FVector::ForwardVector, WorldX);
}

void AFighterCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	const float Ratio = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight() / SharedStats->StandingHalfHeight;
	CapsuleVisual->SetRelativeScale3D(FVector(1.0, 1.0, Ratio));
}

void AFighterCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	CapsuleVisual->SetRelativeScale3D(FVector::OneVector);
}
