// Fill out your copyright notice in the Description page of Project Settings.


#include "StatePattern.h"

#include "EnemyBaseCharacter.h"

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
