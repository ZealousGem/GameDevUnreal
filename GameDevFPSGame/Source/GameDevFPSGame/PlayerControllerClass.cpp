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

	if(ActionSwitch)
	{
		EnhancedInputComponent->BindAction(ActionSwitch, ETriggerEvent::Triggered, this, &APlayerControllerClass::HandleSwitch);
	}

	if(ActionFire)
	{
		EnhancedInputComponent->BindAction(ActionFire, ETriggerEvent::Triggered, this, &APlayerControllerClass::Tracing);
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

void APlayerControllerClass::HandleSwitch()
{
	
	if(PlayerCharacter)
	{
		
		if(PlayerCharacter->fpsGun->IsVisible()) // sets secondary gun visible once input is done
		{
			PlayerCharacter->fpsGun->SetVisibility(false);
			PlayerCharacter->secGun->SetVisibility(true);
		}

		else if(PlayerCharacter->secGun->IsVisible()) // sets primary gun visible one input is done
		{

			PlayerCharacter->fpsGun->SetVisibility(true);
			PlayerCharacter->secGun->SetVisibility(false);	
		}
	}
}

void APlayerControllerClass::Tracing()
{
	if(PlayerCharacter)
	{
		FVector startPoint;
        if(PlayerCharacter->fpsGun->IsVisible())
       {
	     startPoint = PlayerCharacter->fpsGun->GetComponentLocation();
        }
		else if(PlayerCharacter->secGun->IsVisible())
		{
			startPoint = PlayerCharacter->secGun->GetComponentLocation();
		}
		
		FVector ForwardPoint = PlayerCharacter->FPSCameraComponent->GetForwardVector();
		FVector EndPoint = ((ForwardPoint * 1000.f) + startPoint);
		FCollisionQueryParams ColParams;

		DrawDebugLine(GetWorld(), startPoint, EndPoint, FColor::Red, false, 1, 0, 1);

		/* if (EndHit.bBlockingHit)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s"), *EndHit.GetActor()->GetName()));
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Impact Point: %s"), *EndHit.ImpactPoint.ToString()));
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Normal Point: %s"), *EndHit.ImpactNormal.ToString()));
			}
		}*/
	}
	//FHitResult EndHit;
	



/*	if(GetWorld()->LineTraceSingleByChannel(EndHit, startPoint, EndPoint, ECC_Visibility, ColParams))
	{
		
	} */
}


