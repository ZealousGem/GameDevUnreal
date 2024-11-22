// Fill out your copyright notice in the Description page of Project Settings.


#include "LeaderBoardManager.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "EnemyBaseCharacter.h"
#include "MyCharacter.h"
void ULeaderBoardManager::CreateLeaderBoard(UWorld* World)
{
	if(!World) return;

	LeaderboardStarts.Empty(); // clears any existing entires

	// adds the player inot the leadser board
	APlayerController* Player = World->GetFirstPlayerController();
	if(Player)
	{
		AMyCharacter* PlayerChar = Cast<AMyCharacter>(Player->GetPawn());
		if(PlayerChar)
		{
			LeaderboardStarts.Add(FLeaderboardStart(TEXT("Player"), 0));
		}
	}

	int32 BotAmount = 1;

	for(TActorIterator<AEnemyBaseCharacter> It(World); It; ++It)
	{
		
		AEnemyBaseCharacter* Bot = *It;
		if(Bot)
		{
			FString BotName = FString::Printf(TEXT("Bot"), BotAmount);
			LeaderboardStarts.Add(FLeaderboardStart(BotName, 0));
		}

		if(BotAmount > 5)
		{
			break;
		}
	}

	LeaderboardStarts.Sort([](const FLeaderboardStart& A, const FLeaderboardStart& B)
	{
		return A.Kills > B.Kills;
	});
}

void ULeaderBoardManager::UpdatePlayerKills(int32 KillsNew)
{
	for (FLeaderboardStart& Enter:LeaderboardStarts)
	{
		if(Enter.Player == TEXT("Player"))
		{
			Enter.Kills = KillsNew;
			break;
		}
	}

	LeaderboardStarts.Sort([](const FLeaderboardStart& A, const FLeaderboardStart& B)
	{
		return A.Kills > B.Kills;
	});
}

void ULeaderBoardManager::UpdateBotKillCount(const FString& AiName, int32 KillCount)
{
	for (FLeaderboardStart& Enter:LeaderboardStarts)
	{
		if(Enter.Player == AiName)
		{
			Enter.Kills = KillCount;
			break;
		}
	}

	LeaderboardStarts.Sort([](const FLeaderboardStart& A, const FLeaderboardStart& B)
	{
		return A.Kills > B.Kills;
	});
}

const TArray<FLeaderboardStart>& ULeaderBoardManager::GetLeaderBoard() const
{
	return LeaderboardStarts;
}
