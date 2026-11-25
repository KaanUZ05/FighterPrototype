#include "FightPlayerController.h"
#include "FighterCharacter.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "UObject/ConstructorHelpers.h"

AFightPlayerController::AFightPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> Context(TEXT("/Game/Fight/Input/IMC_FightKeyboard.IMC_FightKeyboard"));
	static ConstructorHelpers::FObjectFinder<UInputAction> Move(TEXT("/Game/Fight/Input/IA_FightMoveHorizontal.IA_FightMoveHorizontal"));
	static ConstructorHelpers::FObjectFinder<UInputAction> Jump(TEXT("/Game/Fight/Input/IA_FightJump.IA_FightJump"));
	static ConstructorHelpers::FObjectFinder<UInputAction> Crouch(TEXT("/Game/Fight/Input/IA_FightCrouch.IA_FightCrouch"));
	KeyboardContext = Context.Object;
	MoveAction = Move.Object;
	JumpAction = Jump.Object;
	CrouchAction = Crouch.Object;
}

void AFightPlayerController::ReceivedPlayer()
{
	Super::ReceivedPlayer();
	if (KeyboardContext && IsPrimaryPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(KeyboardContext, 0);
			KeyboardSubsystem = Subsystem;
		}
	}
}

void AFightPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
		Input && IsPrimaryPlayer() && MoveAction && JumpAction && CrouchAction)
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFightPlayerController::HandleMove);
		Input->BindAction(JumpAction, ETriggerEvent::Started, this, &AFightPlayerController::HandleJump);
		Input->BindAction(JumpAction, ETriggerEvent::Completed, this, &AFightPlayerController::HandleJump);
		Input->BindAction(JumpAction, ETriggerEvent::Canceled, this, &AFightPlayerController::HandleJump);
		Input->BindAction(CrouchAction, ETriggerEvent::Started, this, &AFightPlayerController::HandleCrouch);
		Input->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AFightPlayerController::HandleCrouch);
		Input->BindAction(CrouchAction, ETriggerEvent::Canceled, this, &AFightPlayerController::HandleCrouch);
	}
}

void AFightPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = KeyboardSubsystem.Get())
	{
		Subsystem->RemoveMappingContext(KeyboardContext);
	}
	Super::EndPlay(EndPlayReason);
}

void AFightPlayerController::HandleMove(const FInputActionValue& Value)
{
	if (AFighterCharacter* Fighter = GetPawn<AFighterCharacter>())
	{
		Fighter->MoveHorizontal(Value.Get<float>());
	}
}

void AFightPlayerController::HandleJump(const FInputActionValue& Value)
{
	if (AFighterCharacter* Fighter = GetPawn<AFighterCharacter>())
	{
		if (Value.Get<bool>())
		{
			Fighter->Jump();
		}
		else
		{
			Fighter->StopJumping();
		}
	}
}

void AFightPlayerController::HandleCrouch(const FInputActionValue& Value)
{
	if (AFighterCharacter* Fighter = GetPawn<AFighterCharacter>())
	{
		if (Value.Get<bool>())
		{
			Fighter->Crouch();
		}
		else
		{
			Fighter->UnCrouch();
		}
	}
}
