// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EnemyBaseCharacter.h"
#include "LeaderBoardManager.generated.h"

/**
 * 
 */

USTRUCT() // made to contain the data in the structure
struct GAMEDEVFPSGAME_API FLeaderboardStart
{
	GENERATED_BODY()

public:
	UPROPERTY(Blueprintable)
	FString Player; // variables

	UPROPERTY(Blueprintable)
	int32 Kills;

	FLeaderboardStart() // Default Constructor
		: Player(TEXT("No Name")), Kills(0){} // default values when game loads

	FLeaderboardStart(const FString& PlayerName, int32 KillCount) :
	Player(PlayerName), Kills(KillCount){} // this will be the contrcutor that will create the names and killcount through the instanition 
	
};

UCLASS(Blueprintable)
class GAMEDEVFPSGAME_API ULeaderBoardManager : public UObject
{
	GENERATED_BODY()

private:

	TArray<FLeaderboardStart> LeaderboardStarts; // array containing the player and kill count 

public:
	void CreateLeaderBoard(UWorld* World); // creates the leaderboard in the world
	void UpdatePlayerKills(int32 KillsNew); // will update player's killcount
	void UpdateBotKills(int32 KillsNew); 
	void UpdateBotKillCount(const FString& AiName, int32 KillCount); // will update bots kill count
	const TArray<FLeaderboardStart>& GetLeaderBoard() const; // will retrieve the leader through the accessor
	
};
