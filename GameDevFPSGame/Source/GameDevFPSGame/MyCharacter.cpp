// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// creates the camera component
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	// attaches the camera to the character pawn
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// Camera Position components
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f,  BaseEyeHeight));

	FPSCameraComponent->bUsePawnControlRotation = true;

	// creates primary weapon mesh component for the player
	fpsGun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Primary Gun"));
	check(fpsGun != nullptr);
	fpsGun-> SetOnlyOwnerSee(true); // only the player can see this mesh 
	fpsGun->SetupAttachment(FPSCameraComponent); // attaches the mesh to the camera component

	fpsAffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Primary affect"));
	check(fpsAffect != nullptr);
	fpsAffect-> SetOnlyOwnerSee(true); // only the player can see this mesh 
	fpsAffect->SetupAttachment(FPSCameraComponent); // attaches the mesh to the camera component


	secGun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Secondary Gun"));
	check(secGun != nullptr);
	secGun-> SetOnlyOwnerSee(true); // only the player can see this mesh 
	secGun->SetupAttachment(FPSCameraComponent); // attaches the mesh to the camera component


	secAffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Secondary affect"));
	check(secAffect != nullptr);
	secAffect-> SetOnlyOwnerSee(true); // only the player can see this mesh 
	secAffect->SetupAttachment(FPSCameraComponent); // attaches the mesh to the camera component

	

	GetMesh()->SetOnlyOwnerSee(true); // player doesn't see third person mesh

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
    fpsAffect->SetActive(false);
	secAffect->SetActive(false);
	if(fpsGun) // sets primary gun on when game runs
	{
		fpsGun->SetVisibility(true);
	}

	if(secGun)
	{
		secGun->SetVisibility(false);
	}
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  
	
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

