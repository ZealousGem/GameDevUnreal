// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerClass.h" 

#include <string>

#include "K2Node_GetSubsystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PawnMovementComponent.h"


void APlayerControllerClass::OnPossess(APawn* InPawn)
{


	Super::OnPossess(InPawn);

	PlayerCharacter = Cast<AMyCharacter>(InPawn); // overrides the default to our desired character pawn 
	checkf(PlayerCharacter, TEXT("APlayerControllerB derived Class should only posses AMyCharacter derived Pawns"))
	

	WeaponHandle = NewObject<UWeaponHandling>(this); // creates the weapons object
	checkf(WeaponHandle, TEXT("weapon isnt loaded"))

	


	display = Cast<AHUDDisplayClass>(GetWorld()->GetFirstPlayerController()->GetHUD()); // creates the hud object
	checkf(display, TEXT("not able to find the inteded HUD Class"))


	WeaponHandle->Activate(PlayerCharacter,display); // instantiates the character and hud class into the weapon class to activate weapon logic
	
	

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent); // instantiates the enchanced object
	checkf(EnhancedInputComponent, TEXT("Uable to find a refernece to the EnchancecLocalPlayerSubsystem"))

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()); // detectes the inputmapping used in the editor
	checkf(InputSubsystem, TEXT("Unable to get a reference to the EnhancedPlayerSystem"))


	checkf(InputMappingContext, TEXT("Input Mapping was not Specified"))

	InputSubsystem ->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContext, 0);


	// connects all the player inputs to the intended functions
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

	if(ActionSprint)
	{
		EnhancedInputComponent->BindAction(ActionSprint, ETriggerEvent::Started, this, &APlayerControllerClass::HandleSprintOn);
		EnhancedInputComponent->BindAction(ActionSprint, ETriggerEvent::Completed, this, &APlayerControllerClass::HandleSprintOff);
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
		EnhancedInputComponent->BindAction(ActionFire, ETriggerEvent::Started, this, &APlayerControllerClass::HandleFire); // will activate the handle fire method once keybidning is set
		EnhancedInputComponent->BindAction(ActionFire, ETriggerEvent::Completed, this, &APlayerControllerClass::Released); // will actvate the realease method once fire method has been implemented to not let ammo decrease more than once 
		
	}

	if(ActionShowLeaderBoard)
	{
		EnhancedInputComponent->BindAction(ActionShowLeaderBoard, ETriggerEvent::Started, this, &APlayerControllerClass::ShowLeaderBoard); // will activate the handle fire method once keybidning is set
		EnhancedInputComponent->BindAction(ActionShowLeaderBoard, ETriggerEvent::Completed, this, &APlayerControllerClass::HideLeaderBoard);
	}

	if(ActionPauseGame)
	{
		
		EnhancedInputComponent->BindAction(ActionPauseGame, ETriggerEvent::Triggered, this, &APlayerControllerClass::PauseGame);
	}

	
	
}

void APlayerControllerClass::OnUnPossess() // will unposses character once program ends or changes scene
{
	EnhancedInputComponent->ClearActionBindings();

	Super::OnUnPossess();
}

void APlayerControllerClass::HandleCrouch() // uses the movementbase function to set the crouch to true if the movmentbase is set
{
	if(PlayerCharacter->GetMovementBase())
	{

		
     PlayerCharacter->GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
		
		
	}

	PlayerCharacter->GetMovementComponent()->IsCrouching() ? PlayerCharacter->UnCrouch(true) : PlayerCharacter->Crouch(false);
		// will set the crouch to false if the player is using the crouching funbction
		
	
}

void APlayerControllerClass::HandleSprintOn()
{
if(PlayerCharacter && PlayerCharacter->GetCharacterMovement()) // changes the character's movemnt speed to Increspeed which is 1000 F
{
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = IncSpeed;
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("on")));
}

	spint = true; 
	
}

void APlayerControllerClass::HandleSprintOff()
{
if(PlayerCharacter && PlayerCharacter->GetCharacterMovement()) // changes the character speed back to normal character speed once unpressed
{
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("off")));
}
	spint = false;
	
}


void APlayerControllerClass::HandleLookAround(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2d>();

	AddYawInput(LookAxisVector.X); // uses a 2d vector axis to allow the player to look around
	AddPitchInput(LookAxisVector.Y);
}

void APlayerControllerClass::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	if(PlayerCharacter)
	{
		float increaseSpeed = spint ? IncSpeed : 1.0f;
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementVector.Y); // will add a movement transformation to make the player go forward by setting the vector variable
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), MovementVector.X); // will add a movement transformation to make the player go side to side by setting the vector variable
		
	} 

	
}

void APlayerControllerClass::HandleJump()
{
	if(PlayerCharacter)
	{
		PlayerCharacter->Jump(); // uses jump function to lift player 
		PlayerCharacter->UnCrouch(); //automatically uncrouches player if the pawn is set on crouch
	}
}

void APlayerControllerClass::HandleSwitch()
{
	
	WeaponHandle->SwitchWeapon(); // activate the switch function in the weaponhandling class
	
	
}

void APlayerControllerClass::HandleFire()
{

	
	WeaponHandle->HandleFire();// activate the LineTracing function in the weaponhandling class

}

void APlayerControllerClass::Released()
{

WeaponHandle->Released(); // will switch off the fireing in the weaponhandling class
	
	
}

void APlayerControllerClass::ShowLeaderBoard()
{
	display->ShowLeaderBoard();
}

void APlayerControllerClass::HideLeaderBoard()
{
	display->HideLeaderBoard();
}

void APlayerControllerClass::PauseGame()
{
	display->PauseGame();
}


