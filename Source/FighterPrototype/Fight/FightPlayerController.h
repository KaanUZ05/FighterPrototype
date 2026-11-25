#pragma once

#include "GameFramework/PlayerController.h"
#include "FightPlayerController.generated.h"

class UEnhancedInputLocalPlayerSubsystem;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class FIGHTERPROTOTYPE_API AFightPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AFightPlayerController();

protected:
	void SetupInputComponent() override;
	void ReceivedPlayer() override;
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void HandleMove(const FInputActionValue& Value);
	void HandleJump(const FInputActionValue& Value);
	void HandleCrouch(const FInputActionValue& Value);

	UPROPERTY()
	TObjectPtr<UInputMappingContext> KeyboardContext;

	UPROPERTY()
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY()
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY()
	TObjectPtr<UInputAction> CrouchAction;

	TWeakObjectPtr<UEnhancedInputLocalPlayerSubsystem> KeyboardSubsystem;
};
