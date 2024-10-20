// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyShotGunCharacter.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AEnemyShotGunCharacter::AEnemyShotGunCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	fpsGun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Primary Gun"));
	check(fpsGun != nullptr);
	fpsGun->SetupAttachment(character);
	 // only the player can see this mesh 
	 // attaches the mesh to the camera component
	; // gets rid of showdows from mesh to not ruin the illusion 

	// creates gun affect particle component for the primary gun
	fpsAffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Primary affect"));
	check(fpsAffect != nullptr);
	 // only the player can see this mesh 
	

	// creates secondary weapon mesh component for the player
	secGun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Secondary Gun"));
	check(secGun != nullptr);
	secGun-> SetOnlyOwnerSee(true); // only the player can see this mesh 
	
	secGun->CastShadow = false; // same thing be gone shadow!!!!

	// creates gun affect particle component for the secondary gun
	secAffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Secondary affect"));
	check(secAffect != nullptr);
	 // only the player can see this mesh 


}

// Called when the game starts or when spawned
void AEnemyShotGunCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyShotGunCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyShotGunCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

