// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "DrawDebugHelpers.h"
#include "EnhancedInputSubsystems.h"
#include "WeaponHandling.h"


#include "MyCharacter.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputDeveloperSettings.h"
#include "EnhancedInputSubsystems.h"
#include  "EnhancedInputComponent.h"
#include "HUDDisplayClass.h"
#include "InputActionValue.h"
#include "InputAction.h"

#include "PlayerControllerClass.generated.h"

/**
 * 
 */

// handles all the player inputs in the program
UCLASS(Abstract)
class GAMEDEVFPSGAME_API APlayerControllerClass : public APlayerController
{
public: 

	// this allows us to add the input actions in the controller class
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Movement")
	UInputAction* ActionMovement = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Movement")
	UInputAction* ActionLookAround = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Movement")
	UInputAction* ActionJump = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Movement")
	UInputAction* ActionCrouch = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Movement")
	UInputAction* ActionSprint = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Movement")
	UInputAction* ActionSwitch = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Movement")
	UInputAction* ActionFire = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Movement")
	TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | System")
	UInputAction* ActionPause = nullptr;

	


protected:

	virtual  void OnPossess(APawn* InPawn) override; // overrides the default pawn the with mycharacter class

	virtual void OnUnPossess() override;

	void HandleLookAround(const FInputActionValue& InputActionValue);

	void HandleMove(const FInputActionValue& InputActionValue);

	void HandleJump();

	void HandleCrouch();

	void HandleSprintOn();

	void HandleSprintOff();

	void HandleSwitch(); // switches the primary and secondary weapon
	
	void HandleFire(); // activates the tracing method through the keybinding

	void Released(); // will stop ammo counter to decreases

	void HandleEscape();
	
	
private:

	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr; // used to allow the keybind function to become usable

	UPROPERTY()
	AMyCharacter* PlayerCharacter = nullptr; // creates a mycharacter object

	UPROPERTY()
	AHUDDisplayClass* display = nullptr; // creates a hud object

	UPROPERTY()
	UWeaponHandling* WeaponHandle;



	bool fireinframe = false; // use detect a shot has been made by a weapon

	bool spint = false;

	float IncSpeed = 1000.0f;

	
 
	
	
	GENERATED_BODY()
     
};
