// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"


// Sets default values
AMyCharacter::AMyCharacter()
{

	bHasPickedUpSecondWeapon = false;  // Player hasn't picked up the weapon yet

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
	fpsGun->CastShadow = false; // gets rid of showdows from mesh to not ruin the illusion 

	// creates gun affect particle component for the primary gun
	fpsAffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Primary affect"));
	check(fpsAffect != nullptr);
	fpsAffect-> SetOnlyOwnerSee(true); // only the player can see this mesh 
	fpsAffect->SetupAttachment(FPSCameraComponent); // attaches the mesh to the camera component

	// creates secondary weapon mesh component for the player
	secGun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Secondary Gun"));
	check(secGun != nullptr);
	secGun-> SetOnlyOwnerSee(true); // only the player can see this mesh 
	secGun->SetupAttachment(FPSCameraComponent); // attaches the mesh to the camera component
	secGun->CastShadow = false; // same thing be gone shadow!!!!

	// creates gun affect particle component for the secondary gun
	secAffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Secondary affect"));
	check(secAffect != nullptr);
	secAffect-> SetOnlyOwnerSee(true); // only the player can see this mesh 
	secAffect->SetupAttachment(FPSCameraComponent); // attaches the mesh to the camera component

	

	GetMesh()->SetOnlyOwnerSee(true); // player doesn't see third person mesh
	
	

	MaxHealth = 100.0f; // set max health
	CurrentHealth = 90.0f; //initialize current health
	

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
    fpsAffect->SetActive(false); // turns off gun affect once the game starts
	secAffect->SetActive(false);
	ammo = 12; // sets the ammo to 12 
	if(fpsGun) // sets primary gun on when game runs
	{
		fpsGun->SetVisibility(true);
	}

	if(secGun) // sets secondary gun hidden when game runs
	{
		secGun->SetVisibility(false);
	}
	ApplyDamage(0);
	newWeapon();
	
}



// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  
	
}

void AMyCharacter::newWeapon()
{
	Change = false;
}



// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
void AMyCharacter::ApplyDamage(float DamageAmount)
{
	CurrentHealth -= DamageAmount;

	// Ensure health doesn't go below 0
	if (CurrentHealth < 0)
	{
		CurrentHealth = 0;
	}

	// Calculate health percentage
	float HealthPercentage = CurrentHealth / MaxHealth;

	// Update the health bar in HUD
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	AHUDDisplayClass* HUD = Cast<AHUDDisplayClass>(PlayerController->GetHUD());
	if (HUD)
	{
		HUD->UpdateHealthBar(HealthPercentage);
		HUD->UpdateAmmo(ammo);
	}

	// Optionally, handle player death
	if (CurrentHealth == 0)
	{
		// Trigger death
	}
}
void AMyCharacter::Heal(float HealAmount)
{
	CurrentHealth += HealAmount;

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Character healed")));

	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}




