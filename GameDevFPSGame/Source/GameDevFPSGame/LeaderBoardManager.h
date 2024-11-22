// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EnemyBaseCharacter.h"
#include "LeaderBoardManager.generated.h"

/**
 * 
 */

USTRUCT()
struct GAMEDEVFPSGAME_API FLeaderboardStart
{
	GENERATED_BODY()

public:
	UPROPERTY(Blueprintable)
	FString Player;

	UPROPERTY(Blueprintable)
	int32 Kills;

	FLeaderboardStart()
		: Player(TEXT("No Name")), Kills(0){}

	FLeaderboardStart(const FString& PlayerName, int32 KillCount) :
	Player(PlayerName), Kills(KillCount){}
	
};

UCLASS(Blueprintable)
class GAMEDEVFPSGAME_API ULeaderBoardManager : public UObject
{
	GENERATED_BODY()

private:

	TArray<FLeaderboardStart> LeaderboardStarts;

public:
	void CreateLeaderBoard(UWorld* World);
	void UpdatePlayerKills(int32 KillsNew);
	void UpdateBotKillCount(const FString& AiName, int32 KillCount);
	const TArray<FLeaderboardStart>& GetLeaderBoard() const;
	
};
