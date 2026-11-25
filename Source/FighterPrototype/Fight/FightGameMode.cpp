#include "FightGameMode.h"
#include "FighterCharacter.h"
#include "Engine/GameInstance.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerStart.h"

namespace
{
	const FName SlotA(TEXT("FighterA"));
	const FName SlotB(TEXT("FighterB"));
}

AFightGameMode::AFightGameMode()
{
	DefaultPawnClass = AFighterCharacter::StaticClass();
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
		return;
	}

	RestartPlayerAtPlayerStart(Controller, Index == 0 ? StartA : StartB);
	Fighter = Cast<AFighterCharacter>(Controller->GetPawn());
	if (Fighter)
	{
		Fighter->AssignSlot(Index == 0 ? SlotA : SlotB);
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
			FighterB->AssignSlot(SlotB);
		}
	}
}
