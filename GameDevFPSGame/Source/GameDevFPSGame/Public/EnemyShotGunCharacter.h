// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameDevFPSGame/EnemyBaseCharacter.h"
#include "EnemyShotGunCharacter.generated.h"

UCLASS()
class GAMEDEVFPSGAME_API AEnemyShotGunCharacter : public AEnemyBaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyShotGunCharacter();

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
	bool Change;

	// function to apply damage
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
