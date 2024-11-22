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

	UPROPERTY(VisibleAnywhere, Category= HatMesh)
	UStaticMeshComponent* hat;
	
	UPROPERTY(VisibleDefaultsOnly, Category= CharacterMesh) // adds the epic gun effect to the primary gun
	UParticleSystemComponent* fpsexplosion;

	UPROPERTY(VisibleDefaultsOnly, Category= Mesh) // adding the gun mesh to player
	USkeletalMeshComponent* fpsWep;

	UPROPERTY(VisibleDefaultsOnly, Category= Mesh) // adds the epic gun affect to the secondary gun
	UParticleSystemComponent* secExplosion;

	UPROPERTY(VisibleDefaultsOnly, Category= Mesh) // adds the seconadary gun mesh to player
	USkeletalMeshComponent* secWep;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float CurrentHealth;

	UPROPERTY(BlueprintReadWrite, Category = "Bot")
	FString Botname;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void ApplyDamage(float DamageAmount);

	UPROPERTY(EditAnywhere, Category= "AI")
	UBehaviorTree* BehaviourTree;
	
    UPROPERTY(VisibleAnywhere, Category="AI")
	UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Mesh") // the ammo variable that will be affected once the secondary weapon is shot
	int32 ammo;

	UFUNCTION(BlueprintCallable, Category = "Health")
	//void Heal(float HealAmount);

	void Fire();

	void RoateToEnemy(AActor* Target);
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void PlayerCaught(APawn* Pawn);

	UPROPERTY(EditAnywhere, Category= "Animations") // animation sequence for the character
	UAnimSequence* WalkAnimation;

	UPROPERTY(EditAnywhere, Category= "Animations") // animation sequence for the character
	UAnimSequence* IdleAnimation;

	void setWalkAnimation(bool moving); // handles animations

	bool movement; // checks if ai is moving

	class UAIPerceptionStimuliSourceComponent* Stim; // sets the perception system on the enemy character

	void setStim();

	
	

public:
	// Called every frame

	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
