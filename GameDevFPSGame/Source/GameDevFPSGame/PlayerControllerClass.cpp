// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerClass.h"

#include "K2Node_GetSubsystem.h"
#include "GameFramework/PawnMovementComponent.h"


void APlayerControllerClass::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PlayerCharacter = Cast<AMyCharacter>(InPawn);
	checkf(PlayerCharacter, TEXT("APlayerControllerB derived Class should only posses AMyCharacter derived Pawns"))

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("Uable to find a refernece to the EnchancecLocalPlayerSubsystem"))

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystem, TEXT("Unable to get a reference to the EnhancedPlayerSystem"))


	checkf(InputMappingContext, TEXT("Input Mapping was not Specified"))

	InputSubsystem ->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContext, 0);


	if(ActionMovement)
	{
		EnhancedInputComponent->BindAction(ActionMovement, ETriggerEvent::Triggered, this, &APlayerControllerClass::HandleMove);
	}

	if(ActionLookAround)
	{
		EnhancedInputComponent->BindAction(ActionLookAround, ETriggerEvent::Triggered, this, &APlayerControllerClass::HandleLookAround);
	}

	if(ActionJump)
	{
		EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Triggered, this, &APlayerControllerClass::HandleJump);
	}

	if(ActionCrouch)
	{
		EnhancedInputComponent->BindAction(ActionCrouch, ETriggerEvent::Triggered, this, &APlayerControllerClass::HandleCrouch);
	}

	
	
}

void APlayerControllerClass::OnUnPossess()
{
	EnhancedInputComponent->ClearActionBindings();

	Super::OnUnPossess();
}

void APlayerControllerClass::HandleCrouch()
{
	if(PlayerCharacter->GetMovementBase())
	{

		
     PlayerCharacter->GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
		
		
	}

	PlayerCharacter->GetMovementComponent()->IsCrouching() ? PlayerCharacter->UnCrouch(true) : PlayerCharacter->Crouch(false);
		
		
	
}



void APlayerControllerClass::HandleLookAround(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2d>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void APlayerControllerClass::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2d>();

	if(PlayerCharacter)
	{
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementVector.Y);
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), MovementVector.X);
	}
}

void APlayerControllerClass::HandleJump()
{
	if(PlayerCharacter)
	{
		PlayerCharacter->Jump();
		PlayerCharacter->UnCrouch();
	}
}