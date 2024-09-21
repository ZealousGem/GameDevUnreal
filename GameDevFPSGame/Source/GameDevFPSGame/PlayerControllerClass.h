// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "DrawDebugHelpers.h"
#include "EnhancedInputSubsystems.h"
//#include "Engine/Source/Runtime/EnhancedInput/Public/EnhancedInputComponent.h"
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
	UInputAction* ActionSwitch = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Movement")
	UInputAction* ActionFire = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Movement")
	TObjectPtr<UInputMappingContext> InputMappingContext = nullptr;

	// Health properties
	

	


protected:

	virtual  void OnPossess(APawn* InPawn) override; // overrides the default pawn the with mycharacter class

	virtual void OnUnPossess() override;

	void HandleLookAround(const FInputActionValue& InputActionValue);

	void HandleMove(const FInputActionValue& InputActionValue);

	void HandleJump();

	void HandleCrouch();

	void HandleSwitch(); // switches the primary and secondary weapon

	void Tracing(); // creates the line trace and makes the gun go "pew" "pew"

	void HandleFire(); // activates the tracing method through the keybinding

	void Released(); // will stop ammo counter to decreases

	
	
	
private:

	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr; // used to allow the keybind function to become usable

	UPROPERTY()
	AMyCharacter* PlayerCharacter = nullptr; // creates a mycharacter object

	AHUDDisplayClass* display = nullptr; // creates a hud object

	bool fireinframe = false; // use detect a shot has been made by a weapon

	
 FTimerHandle TimerHandle_HideWidget; // a timer used for the crossdamage widget which will stay active until 0.5 seconds
	void HidedamageWidget(); // calls the hud corssdamage function to make the bool false
	
	
	GENERATED_BODY()
     
};
