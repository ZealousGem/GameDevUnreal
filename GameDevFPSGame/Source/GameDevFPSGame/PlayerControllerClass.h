// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DrawDebugHelpers.h"
#include "EnhancedInputSubsystems.h"
//#include "Engine/Source/Runtime/EnhancedInput/Public/EnhancedInputComponent.h"
#include "MyCharacter.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputDeveloperSettings.h"
#include "EnhancedInputSubsystems.h"
#include  "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "PlayerControllerClass.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class GAMEDEVFPSGAME_API APlayerControllerClass : public APlayerController
{
public: 

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

	


protected:

	virtual  void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

	void HandleLookAround(const FInputActionValue& InputActionValue);

	void HandleMove(const FInputActionValue& InputActionValue);

	void HandleJump();

	void HandleCrouch();

	void HandleSwitch();

	void Tracing();
	
	
private:

	UPROPERTY()
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	UPROPERTY()
	AMyCharacter* PlayerCharacter = nullptr;

	
	GENERATED_BODY()
     
};
