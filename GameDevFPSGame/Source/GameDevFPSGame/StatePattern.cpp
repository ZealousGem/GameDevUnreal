// Fill out your copyright notice in the Description page of Project Settings.


#include "StatePattern.h"

#include "EnemyBaseCharacter.h"
#include "MyCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerControllerClass.h"


void UStateIdle::CreateState(UObject* object) // creates idle state
{
	//Super::CreateState(object);
	if(AEnemyBaseCharacter* Char = Cast<AEnemyBaseCharacter>(object))
	{
		//UAnimInstance* Instance = Char->GetMesh()->GetAnimInstance();
		Char->character->PlayAnimation(Char->GetIdleAnimation(), true);
	}
}

void UStateIdle::UpdateState(UObject* Object) // manages speed of idle state
{
	Super::UpdateState(Object);
}

void UStateIdle::EndState(UObject* object)
{
	if(AEnemyBaseCharacter* Char = Cast<AEnemyBaseCharacter>(object))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Idle Animation is finished"), *Char->GetName());
	}
//	Super::EndState(object);
}

void UStateWalk::CreateState(UObject* object) // creates walking animation state 
{
	if(AEnemyBaseCharacter* Char = Cast<AEnemyBaseCharacter>(object))
	{
		//UAnimInstance* Instance = Char->GetMesh()->GetAnimInstance();
		Char->character->PlayAnimation(Char->GetWalkAnimation(), true);
	}
}

void UStateWalk::UpdateState(UObject* Object) // walk state speed
{
	Super::UpdateState(Object);
}

void UStateWalk::EndState(UObject* object) // ends the walk animation state creating a ease transition
{
	if(AEnemyBaseCharacter* Char = Cast<AEnemyBaseCharacter>(object))
	{
		//UAnimInstance* Instance = Char->GetMesh()->GetAnimInstance();
		UE_LOG(LogTemp, Warning, TEXT("%s Walk Animation is finished"), *Char->GetName());
	}
}

void UStateCrouch::CreateState(UObject* object)
{
//	Super::CreateState(object);
	if(AMyCharacter* Player = Cast<AMyCharacter>(object))
	{
		Player->GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	}
}

void UStateCrouch::EndState(UObject* object)
{
	if(AMyCharacter* Player = Cast<AMyCharacter>(object))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Player has stopped crouching"), *Player->GetName());
	}
	
}

void UStateUnCrouch::CreateState(UObject* object)
{
	if(AMyCharacter* Player = Cast<AMyCharacter>(object))
	{
		Player->GetMovementComponent()->IsCrouching() ? Player->UnCrouch(true) : Player->Crouch(false);
	}
}

void UStateUnCrouch::EndState(UObject* object)
{
	if(AMyCharacter* Player = Cast<AMyCharacter>(object))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Player is crouching"), *Player->GetName());
	}
}

void UStateSprint::CreateState(UObject* object)
{
//	Super::CreateState(object);
	if(AMyCharacter* Player = Cast<AMyCharacter>(object))
	{
		Player->GetCharacterMovement()->MaxWalkSpeed = 1000.0f;
	}
}

void UStateSprint::EndState(UObject* object)
{
	if(AMyCharacter* Player = Cast<AMyCharacter>(object))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Player has stopped sprinting"), *Player->GetName());
	}
}

void UStateNoSprint::CreateState(UObject* object)
{
	if(AMyCharacter* Player = Cast<AMyCharacter>(object))
	{
		Player->GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	}
}

void UStateNoSprint::EndState(UObject* object)
{
	if(AMyCharacter* Player = Cast<AMyCharacter>(object))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Player is Sprinting"), *Player->GetName());
	}
}

void UStateJump::CreateState(UObject* object)
{
	if(AMyCharacter* Player = Cast<AMyCharacter>(object))
	{
		Player->Jump(); // uses jump function to lift player 
		Player->UnCrouch();
		
		
	}

	
	
}

void UStateJump::EndState(UObject* object)
{
	if(AMyCharacter* Player = Cast<AMyCharacter>(object))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Player has stoped jumping"), *Player->GetName());
	}
	//Super::EndState(object);
}

