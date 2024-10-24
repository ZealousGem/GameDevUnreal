// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Spawner.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AEnemyBaseCharacter::AEnemyBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	character = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Enemy"));
	check(character != nullptr)

	hat = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyHat"));
	check(hat != nullptr);
	hat->SetupAttachment(character);
	
	fpsWep = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Primary Weapon"));
	check(fpsWep != nullptr);
	fpsWep->SetupAttachment(character);

	secWep = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Secondary Weapon"));
	check(secWep != nullptr);
	secWep->SetupAttachment(character);
	
	character->SetupAttachment(GetCapsuleComponent());

	 //CapsuleComponent = GetCapsuleComponent();
	//CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	
	//GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap); // Allow line trace hits


	fpsexplosion= CreateDefaultSubobject<UParticleSystemComponent>(TEXT(" affect"));
    fpsexplosion->SetupAttachment(secWep);
	check(fpsexplosion != nullptr);

	secExplosion= CreateDefaultSubobject<UParticleSystemComponent>(TEXT(" sec affect"));
	secExplosion->SetupAttachment(secWep);
	check(secExplosion != nullptr);

	
	MaxHealth = 100.0f; // set max health
	CurrentHealth = 90.0f; //initialize current health
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
	if(fpsWep) // sets primary gun on when game runs
	{
		fpsWep->SetVisibility(true);
	}

	if(secWep) // sets secondary gun hidden when game runs
	{
		secWep->SetVisibility(false);
	}
	ammo = 12; 
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

void AEnemyBaseCharacter::RoateToEnemy(AActor* Target)
{
	if(Target)
	{
		FVector DirectionOfTarget = Target->GetActorLocation() - GetActorLocation();
		DirectionOfTarget.Z = 0;
		DirectionOfTarget.Normalize();

		FRotator NewRoation = DirectionOfTarget.Rotation();
		FRotator currentRot = GetActorRotation();

		FRotator FinalRotation = FRotator(currentRot.Pitch, NewRoation.Yaw, currentRot.Roll);
		SetActorRotation(FinalRotation);
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

