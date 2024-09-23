// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerClass.h" 

#include <string>

#include "K2Node_GetSubsystem.h"
#include "GameFramework/PawnMovementComponent.h"


void APlayerControllerClass::OnPossess(APawn* InPawn)
{


	Super::OnPossess(InPawn);

	PlayerCharacter = Cast<AMyCharacter>(InPawn);
	checkf(PlayerCharacter, TEXT("APlayerControllerB derived Class should only posses AMyCharacter derived Pawns"))
	




	display = Cast<AHUDDisplayClass>(GetWorld()->GetFirstPlayerController()->GetHUD());
	checkf(display, TEXT("not able to find the inteded HUD Class"))
	

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("Uable to find a refernece to the EnchancecLocalPlayerSubsystem"))

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystem, TEXT("Unable to get a reference to the EnhancedPlayerSystem"))


	checkf(InputMappingContext, TEXT("Input Mapping was not Specified"))

	InputSubsystem ->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContext, 0);


	// conncets all the player inputs to the intended functions
	if(ActionMovement)
	{
		EnhancedInputComponent->BindAction(ActionMovement, ETriggerEvent::Triggered, this, &APlayerControllerClass::HandleMove);
	}

	if(ActionLookAround)
	{
		EnhancedInputComponent->BindAction(ActionLookAround, ETriggerEvent::Triggered, this, &APlayerControllerClass::HandleLookAround);
	}

	if(ActionJump)
	{
		EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Triggered, this, &APlayerControllerClass::HandleJump);
	}

	if(ActionCrouch)
	{
		EnhancedInputComponent->BindAction(ActionCrouch, ETriggerEvent::Triggered, this, &APlayerControllerClass::HandleCrouch);
	}

	if(ActionSwitch)
	{
		EnhancedInputComponent->BindAction(ActionSwitch, ETriggerEvent::Triggered, this, &APlayerControllerClass::HandleSwitch);
	}

	if(ActionFire)
	{
		EnhancedInputComponent->BindAction(ActionFire, ETriggerEvent::Started, this, &APlayerControllerClass::HandleFire); // will activate the handle fire method once keybidning is set
		EnhancedInputComponent->BindAction(ActionFire, ETriggerEvent::Completed, this, &APlayerControllerClass::Released); // will actvate the realease method once fire method has been implemented to not let ammo decrease more than once 
		
	}

	
	
}

void APlayerControllerClass::OnUnPossess() // will unposses character once program ends or changes scene
{
	EnhancedInputComponent->ClearActionBindings();

	Super::OnUnPossess();
}

void APlayerControllerClass::HandleCrouch()
{
	if(PlayerCharacter->GetMovementBase())
	{

		
     PlayerCharacter->GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
		
		
	}

	PlayerCharacter->GetMovementComponent()->IsCrouching() ? PlayerCharacter->UnCrouch(true) : PlayerCharacter->Crouch(false);
		
		
	
}



void APlayerControllerClass::HandleLookAround(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2d>();

	AddYawInput(LookAxisVector.X); // i dont understand this shit, I am retarded, thanks sir for the code :)
	AddPitchInput(LookAxisVector.Y);
}

void APlayerControllerClass::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2d>();

	if(PlayerCharacter)
	{
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementVector.Y); // will add a movement transformation to make the player go forward by setting the vector variable
		PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), MovementVector.X); // will add a movement transformation to make the player go side to side by setting the vector variable
	}
}

void APlayerControllerClass::HandleJump()
{
	if(PlayerCharacter)
	{
		PlayerCharacter->Jump(); // uses jump function to lift player 
		PlayerCharacter->UnCrouch(); //automatically uncrouches player if the pawn is set on crouch
	}
}

void APlayerControllerClass::HandleSwitch()
{
	
	if(PlayerCharacter) //-> bHasPickedUpSecondWeapon)
	{
		
		if(PlayerCharacter->fpsGun->IsVisible()) // sets secondary gun visible once input is done
		{
			PlayerCharacter->fpsGun->SetVisibility(false);
			PlayerCharacter->secGun->SetVisibility(true);
		}

		else if(PlayerCharacter->secGun->IsVisible()) // sets primary gun visible one input is done
		{

			PlayerCharacter->fpsGun->SetVisibility(true);
			PlayerCharacter->secGun->SetVisibility(false);	
		}
	}
	else
	{
		// If the player hasn't picked up the second weapon, keep only the primary weapon visible
		//PlayerCharacter->fpsGun->SetVisibility(true);
		//PlayerCharacter->secGun->SetVisibility(false);  // Ensure the secondary weapon stays hidden

	}
}

void APlayerControllerClass::Tracing()
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
        				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Visible"))); // debug to check if it working
        				GetWorld()->GetTimerManager().ClearTimer(TimerHandle_HideWidget); // clears any timer  if the player is hitting an actor costantnly
        				GetWorld()->GetTimerManager().SetTimer(TimerHandle_HideWidget, this, &APlayerControllerClass::HidedamageWidget, 0.5f ,false); // if the player isn't colliding with actors constaly, the timer will be made to hide the widget for 0.5 seconds, after it reaches 0.5 seconds it will call a method to hide the crossdamage ui
        			}
        			if (GEngine)
        			{
        				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s , this has cased 10 damage"), *EndHit.GetActor()->GetName()));
        			}
        		}
        	}
        	
        }
		else if(PlayerCharacter->secGun->IsVisible()) // will only activate if the secondary weapon is displayed
		{
			
			if(PlayerCharacter->ammo > 0 && !fireinframe) // checks if ammo is less than 0 and if it has not fireed yet
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
				
				FString message = FString::Printf(TEXT("Ammo: %d"), PlayerCharacter->ammo);
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, message);
				if(GetWorld()->LineTraceSingleByChannel(EndHit, startPoint, EndPoint, ECC_Visibility, ColParams)) // will activate if enpoint of line collides with an actor
				{
					if (EndHit.bBlockingHit)
					{
						if(display) // look at fps code to figure out how this works
						{
							//display->getCrossDamage()->SetVisibility(ESlateVisibility::Visible);
                         
							display->HideCorssDamage(true);
							display->hit = true;
							GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Visible")));
							GetWorld()->GetTimerManager().ClearTimer(TimerHandle_HideWidget);
							GetWorld()->GetTimerManager().SetTimer(TimerHandle_HideWidget, this, &APlayerControllerClass::HidedamageWidget, 0.5f ,false);
						}
						if (GEngine)
						{
							GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("You are hitting: %s , this has cased 50 damage"), *EndHit.GetActor()->GetName()));
						}
					}
				}
				
				
			
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("you have run out of ammo")));
			}
			fireinframe = true; // sets it to true to stop ammo from decreasing more than once
			
		}
		
		
	}
	
}

void APlayerControllerClass::HandleFire()
{
	Tracing(); // calls the tracing function once the action binding is made
}

void APlayerControllerClass::Released()
{
	fireinframe = false; // resets everytime key is hit
}

void APlayerControllerClass::HidedamageWidget()
{
	if(display) // checks if the display object has been set
	{
		display->HideCorssDamage(false); // will hide the crossdamage ui
		display->hit = false; // again this thing is useless
		
	}
}
