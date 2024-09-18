// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"


UCLASS()
class GAMEDEVFPSGAME_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	
	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent; // fps camera

	UPROPERTY(VisibleDefaultsOnly, Category= Mesh) // adding the gun mesh to player
	USkeletalMeshComponent* fpsGun;

	UPROPERTY(VisibleDefaultsOnly, Category= Mesh)
	USkeletalMeshComponent* secGun;

	UPROPERTY(VisibleDefaultsOnly, Category= Mesh)
	UParticleSystemComponent* fpsAffect;

	UPROPERTY(VisibleDefaultsOnly, Category= Mesh)
	UParticleSystemComponent* secAffect;

	// line of code

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
