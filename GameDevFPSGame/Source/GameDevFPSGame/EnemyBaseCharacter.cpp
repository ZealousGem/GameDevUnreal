// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"


// Sets default values
AEnemyBaseCharacter::AEnemyBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	character = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Enemy"));
	check(character != nullptr)


	fpsWep = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Primary Weapon"));
	check(fpsWep != nullptr);
	fpsWep->SetupAttachment(character);
	
	character->SetupAttachment(GetCapsuleComponent());
	fpsexplosion = CreateDefaultSubobject<UParticleSystemComponent>(TEXT(" affect"));
	fpsexplosion->SetupAttachment(fpsWep);
	check(fpsexplosion != nullptr);

	
	MaxHealth = 100.0f; // set max health
	CurrentHealth = MaxHealth; //initialize current health
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing Component"));
	PawnSensingComp->SetPeripheralVisionAngle(90.f);
	setStim();
}

void AEnemyBaseCharacter::ApplyDamage(float DamageAmount)
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
	

	// Optionally, handle player death
	if (CurrentHealth == 0)
	{
		// Trigger death
	}
}

void AEnemyBaseCharacter::Fire()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Enemy is Shooting")));
}

// Called when the game starts or when spawned
void AEnemyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemyBaseCharacter::PlayerCaught);
	}
	
}

void AEnemyBaseCharacter::PlayerCaught(APawn* Pawn)
{
}

void AEnemyBaseCharacter::setWalkAnimation(bool moving)
{
	UAnimInstance* Inctance = character->GetAnimInstance();
	checkf(Inctance,TEXT("Is not set"));
	if(moving && WalkAnimation && !movement)
	{
		 character->PlayAnimation(WalkAnimation, true);
		movement = true;
		
	}

	else if (!moving && IdleAnimation && movement)
	{
		character->PlayAnimation(IdleAnimation,true);
		movement = false;
		
	}
}

void AEnemyBaseCharacter::setStim()
{
	Stim = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if(Stim)
	{
		Stim->RegisterForSense(TSubclassOf<UAISense>());
		Stim->RegisterWithPerceptionSystem();
	}
}

// Called every frame
void AEnemyBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
  if(GetVelocity().Size() > 0)
  {
	  setWalkAnimation(true);
  }

	else
	{
		setWalkAnimation(false);
	}
	
}

// Called to bind functionality to input
void AEnemyBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

