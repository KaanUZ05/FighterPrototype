#include "FightGameMode.h"
#include "FightCameraActor.h"
#include "FightPlayerController.h"
#include "FighterCharacter.h"
#include "FighterMovementComponent.h"
#include "Engine/GameInstance.h"
#include "Engine/GameViewportClient.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerStart.h"

namespace
{
	const FName SlotA(TEXT("FighterA"));
	const FName SlotB(TEXT("FighterB"));
	const FName LeftBoundTag(TEXT("FightStageLeftBound"));
	const FName RightBoundTag(TEXT("FightStageRightBound"));
}

void AFightGameMode::InitializeFighter(AFighterCharacter& Fighter, FName Slot) const
{
	Fighter.AssignSlot(Slot);
	TOptional<double> LeftFace;
	TOptional<double> RightFace;
	for (TActorIterator<AActor> Actor(GetWorld()); Actor; ++Actor)
	{
		const bool bLeft = Actor->ActorHasTag(LeftBoundTag);
		if (bLeft || Actor->ActorHasTag(RightBoundTag))
		{
			FVector Center;
			FVector Extent;
			Actor->GetActorBounds(true, Center, Extent);
			if (bLeft)
			{
				LeftFace = Center.X + Extent.X;
			}
			else
			{
				RightFace = Center.X - Extent.X;
			}
		}
	}
	if (LeftFace.IsSet() && RightFace.IsSet() && *LeftFace < *RightFace)
	{
		CastChecked<UFighterMovementComponent>(Fighter.GetCharacterMovement())->SetStageFaces(*LeftFace, *RightFace);
	}
}

AFightGameMode::AFightGameMode()
{
	DefaultPawnClass = AFighterCharacter::StaticClass();
	PlayerControllerClass = AFightPlayerController::StaticClass();
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.TickGroup = TG_PostPhysics;
}

APlayerStart* AFightGameMode::FindSlotStart(FName Slot) const
{
	for (TActorIterator<APlayerStart> Start(GetWorld()); Start; ++Start)
	{
		if (Start->PlayerStartTag == Slot)
		{
			return *Start;
		}
	}
	return nullptr;
}

void AFightGameMode::RestartPlayer(AController* NewPlayer)
{
	APlayerStart* StartA = FindSlotStart(SlotA);
	APlayerStart* StartB = FindSlotStart(SlotB);
	if (!StartA || !StartB)
	{
		Super::RestartPlayer(NewPlayer);
		return;
	}

	APlayerController* Controller = Cast<APlayerController>(NewPlayer);
	const int32 Index = Controller ? GetGameInstance()->GetLocalPlayers().IndexOfByKey(Controller->GetLocalPlayer()) : INDEX_NONE;
	if (Index != 0 && Index != 1)
	{
		return;
	}

	TObjectPtr<AFighterCharacter>& Fighter = Index == 0 ? FighterA : FighterB;
	if (IsValid(Fighter))
	{
		if (Controller->GetPawn() != Fighter)
		{
			Controller->Possess(Fighter);
		}
		SetSharedView(*Controller);
		return;
	}

	RestartPlayerAtPlayerStart(Controller, Index == 0 ? StartA : StartB);
	Fighter = Cast<AFighterCharacter>(Controller->GetPawn());
	if (Fighter)
	{
		InitializeFighter(*Fighter, Index == 0 ? SlotA : SlotB);
		SetSharedView(*Controller);
	}
}

void AFightGameMode::StartPlay()
{
	Super::StartPlay();

	APlayerStart* StartB = FindSlotStart(SlotB);
	if (!FighterB && StartB && FindSlotStart(SlotA))
	{
		FActorSpawnParameters Spawn;
		Spawn.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
		FighterB = GetWorld()->SpawnActor<AFighterCharacter>(DefaultPawnClass, StartB->GetActorTransform(), Spawn);
		if (FighterB)
		{
			InitializeFighter(*FighterB, SlotB);
		}
	}

	if (FighterA && FighterB)
	{
		FightCamera = GetWorld()->SpawnActor<AFightCameraActor>();
		UpdateFightView();
		SetActorTickEnabled(true);
		if (UGameViewportClient* Viewport = GetWorld()->GetGameViewport())
		{
			bPreviousSplitScreenOverride = Viewport->IsSplitscreenForceDisabled();
			Viewport->SetForceDisableSplitscreen(true);
			bChangedSplitScreenOverride = true;
		}
		for (FConstPlayerControllerIterator Controller = GetWorld()->GetPlayerControllerIterator(); Controller; ++Controller)
		{
			if (APlayerController* Player = Controller->Get())
			{
				SetSharedView(*Player);
			}
		}
	}
}

void AFightGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateFightView();
}

void AFightGameMode::UpdateFightView()
{
	if (IsValid(FighterA) && IsValid(FighterB))
	{
		FighterA->FaceOpponent(*FighterB);
		FighterB->FaceOpponent(*FighterA);
		if (FightCamera)
		{
			FightCamera->FrameFighters(FighterA->GetActorLocation(), FighterB->GetActorLocation());
		}
	}
}

void AFightGameMode::SetSharedView(APlayerController& Controller) const
{
	if (FightCamera && Controller.IsLocalController())
	{
		Controller.bAutoManageActiveCameraTarget = false;
		Controller.SetViewTarget(FightCamera);
	}
}

void AFightGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (bChangedSplitScreenOverride)
	{
		if (UGameViewportClient* Viewport = GetWorld()->GetGameViewport())
		{
			Viewport->SetForceDisableSplitscreen(bPreviousSplitScreenOverride);
		}
	}
	Super::EndPlay(EndPlayReason);
}
