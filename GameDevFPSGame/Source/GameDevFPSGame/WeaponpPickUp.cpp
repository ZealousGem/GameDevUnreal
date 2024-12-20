﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponpPickUp.h"


// Sets default values
AWeaponpPickUp::AWeaponpPickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWeaponpPickUp::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AWeaponpPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponpPickUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	// overides parents overlap function
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		
		if(!PlayerCharacter->Change) // if cast is done correclty once collision is made the boolean will be set to true which will allow the player to access the second gun
		{
			PickitUp();
			newWeapon();
			PlayerCharacter->Change = change;
			
		}
	}

	Destroy(); // destroys pickup
	
}

void AWeaponpPickUp::PickitUp()
{
//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Shot Gun Picked Up")));
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	AHUDDisplayClass* HUD = Cast<AHUDDisplayClass>(PlayerController->GetHUD());
	FTimerHandle TimerHandle;
	const FString ammo = "wep";
	HUD->AmmoDisplay(true,ammo);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, HUD, &AHUDDisplayClass::AmmoHidden, 1.0f, false);
	
}

void AWeaponpPickUp::newWeapon()
{
	change = true;
}
	

