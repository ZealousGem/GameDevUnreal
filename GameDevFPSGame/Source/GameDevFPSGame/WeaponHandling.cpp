﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponHandling.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"


UWeaponHandling::UWeaponHandling() : PlayerCharacter(nullptr), display(nullptr)
{
}

void UWeaponHandling::Activate(AMyCharacter* isPlayerCharacter, AHUDDisplayClass* DisplayHUD)
{
	PlayerCharacter = isPlayerCharacter;
	display = DisplayHUD;
}

void UWeaponHandling::Tracing()
{

	if(PlayerCharacter) // look at secondaryweapon code to understand how this works
	{
		FVector startPoint;
        if(PlayerCharacter->fpsGun->IsVisible())
       {
        	
        	FHitResult EndHit; // this will be the endpoint of the line trace that will be set once a collision is made
	        startPoint = PlayerCharacter->fpsGun->GetComponentLocation();
        	FVector ForwardPoint = PlayerCharacter->FPSCameraComponent->GetForwardVector();
        	FVector EndPoint = ((ForwardPoint * 1000.f) + startPoint);
        	FCollisionQueryParams ColParams;
       
        	if(PlayerCharacter->fpsAffect)
        	{
        		PlayerCharacter->fpsAffect->Deactivate();
        		PlayerCharacter->fpsAffect->Activate();
        		
        	}
        	
        	//DrawDebugLine(GetWorld(), startPoint, EndPoint, FColor::Red, false, 1, 0, 1);
        	if(GetWorld()->LineTraceSingleByChannel(EndHit, startPoint, EndPoint, ECC_Visibility, ColParams))
        	{
        		if (EndHit.bBlockingHit)
        		{
        		//	display->hit = true;
        			
        			if(display) // make sure the display object has been set
        			{
        				//display->getCrossDamage()->SetVisibility(ESlateVisibility::Visible);
                         
        				display->HideCorssDamage(true); // calls the public method to unhid the cross damage ui
        				display->hit = true; // this is useless i should delete this lol
        				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Visible"))); // debug to check if it working
        				GetWorld()->GetTimerManager().ClearTimer(TimerHandle_HideWidget); // clears any timer  if the player is hitting an actor costantnly
        				GetWorld()->GetTimerManager().SetTimer(TimerHandle_HideWidget, this, &UWeaponHandling::HideWidget, 0.5f ,false); // if the player isn't colliding with actors constaly, the timer will be made to hide the widget for 0.5 seconds, after it reaches 0.5 seconds it will call a method to hide the crossdamage ui
        			}
        			if (GEngine)
        			{
        				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s , this has caused 3 damage"), *EndHit.GetActor()->GetName()));
        			}
        		}
        	}
        	
        }
		else if(PlayerCharacter->secGun->IsVisible()) // will only activate if the secondary weapon is displayed
		{
			if(PlayerCharacter->ammo > 0 && !FireInFrame) // checks if ammo is less than 0 and if it has not fireed yet
			{
				FHitResult EndHit; 
				PlayerCharacter->ammo--;
				display->UpdateAmmo(PlayerCharacter->ammo);// decreases ammo 
				startPoint = PlayerCharacter->secGun->GetComponentLocation(); // gets location of weapon where line will start
				FVector ForwardPoint = PlayerCharacter->FPSCameraComponent->GetForwardVector(); // will be used to move the line torwards the middle of the camera
				FVector EndPoint = ((ForwardPoint * 500.f) + startPoint); // increases the distance of the line from the camera
				FCollisionQueryParams ColParams;

				
				if(PlayerCharacter->secAffect) // turns on gun blasting particles
				{
					PlayerCharacter->secAffect->Deactivate();
					PlayerCharacter->secAffect->Activate();
					
        		
				}
				
				//DrawDebugLine(GetWorld(), startPoint, EndPoint, FColor::Red, false, 1, 0, 1);
				
				//FString message = FString::Printf(TEXT("Ammo: %d"), PlayerCharacter->ammo);
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, message);
				if(GetWorld()->LineTraceSingleByChannel(EndHit, startPoint, EndPoint, ECC_Visibility, ColParams)) // will activate if enpoint of line collides with an actor
				{
					if (EndHit.bBlockingHit)
					{
						if(display) // look at fps code to figure out how this works
						{
							//display->getCrossDamage()->SetVisibility(ESlateVisibility::Visible);
                         
							display->HideCorssDamage(true);
							display->hit = true;
							//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Visible")));
							GetWorld()->GetTimerManager().ClearTimer(TimerHandle_HideWidget);
							GetWorld()->GetTimerManager().SetTimer(TimerHandle_HideWidget, this, &UWeaponHandling::HideWidget, 0.5f ,false);
						}
						if (GEngine)
						{
							GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s , this has cased 12 damage"), *EndHit.GetActor()->GetName()));
						}
					}
				}
				
				
			
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("you have run out of ammo")));
			}
			FireInFrame = true; // sets it to true to stop ammo from decreasing more than once
		}
	}
	
}

void UWeaponHandling::HandleFire()
{
	Tracing();
}

void UWeaponHandling::Released()
{
	FireInFrame = false;
}

void UWeaponHandling::HideWidget()
{
	if(display)
	{
		display->HideCorssDamage(false);
		display->hit = false;
	}
}

void UWeaponHandling::SwitchWeapon()
{
	if(PlayerCharacter) 
	{
		
		if(PlayerCharacter->fpsGun->IsVisible() && PlayerCharacter->Change) // sets secondary gun visible once input is done
		{
			PlayerCharacter->fpsGun->SetVisibility(false);
			PlayerCharacter->secGun->SetVisibility(true);
			display->AmmoDisplay();
			display->SecWeapon();
		}

		else if(PlayerCharacter->secGun->IsVisible()) // sets primary gun visible one input is done
		{

			PlayerCharacter->fpsGun->SetVisibility(true);
			PlayerCharacter->secGun->SetVisibility(false);
			display->AmmoHide();
			display->MainWeapon();
		}
	} 
}
