// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "Perception/PawnSensingComponent.h"
#include "Animation/AnimSequence.h"
#include "EnemyBaseCharacter.generated.h"

UCLASS()
class GAMEDEVFPSGAME_API AEnemyBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBaseCharacter();

	UPROPERTY(VisibleAnywhere, Category= CharatcerMesh)
	USkeletalMeshComponent* character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float CurrentHealth;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void ApplyDamage(float DamageAmount);

	UPROPERTY(EditAnywhere, Category= "AI")
	UBehaviorTree* BehaviourTree;
	
    UPROPERTY(VisibleAnywhere, Category="AI")
	UPawnSensingComponent* PawnSensingComp;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void PlayerCaught(APawn* Pawn);

	UPROPERTY(EditAnywhere, Category= "Animations") // animation sequence for the character
	UAnimSequence* WalkAnimation;

	UPROPERTY(EditAnywhere, Category= "Animations") // animation sequence for the character
	UAnimSequence* IdleAnimation;

	void setWalkAnimation(bool moving);

	bool movement;
	

public:
	// Called every frame

	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
