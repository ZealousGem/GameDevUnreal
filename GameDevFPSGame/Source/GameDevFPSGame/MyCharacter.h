// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUDDisplayClass.h"
#include "Observer.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

// sets all the characters meshes and weapons in this class
UCLASS()
class GAMEDEVFPSGAME_API AMyCharacter : public ACharacter, public IObserverWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	// Boolean to track if the player has picked up the secondary weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	bool bHasPickedUpSecondWeapon;

	
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent; // fps camera

	UPROPERTY(VisibleDefaultsOnly, Category= Mesh) // adding the gun mesh to player
	USkeletalMeshComponent* fpsGun;

	UPROPERTY(VisibleDefaultsOnly, Category= Mesh) // adds the seconadary gun mesh to player
	USkeletalMeshComponent* secGun;

	UPROPERTY(VisibleDefaultsOnly, Category= Mesh) // adds the epic gun effect to the primary gun
	UParticleSystemComponent* fpsAffect;

	UPROPERTY(VisibleDefaultsOnly, Category= Mesh) // adds the epic gun affect to the secondary gun
	UParticleSystemComponent* secAffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Mesh") // the ammo variable that will be affected once the secondary weapon is shot
	int32 ammo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	bool Change;

	// function to apply damage
	UFUNCTION(BlueprintCallable, Category = "Health")
	void ApplyDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category ="Health")
	void Heal(float HealAmount);

	

	// line of code

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void newWeapon() override;

	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
