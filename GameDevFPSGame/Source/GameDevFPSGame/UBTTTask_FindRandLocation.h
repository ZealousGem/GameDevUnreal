﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "UBTTTask_FindRandLocation.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVFPSGAME_API UUBTTTask_FindRandLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	explicit UUBTTTask_FindRandLocation(FObjectInitializer const & ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "AI", meta=(AllowPrivateAccess= "true"))
	float SearchRadius = 1500.f;
};
