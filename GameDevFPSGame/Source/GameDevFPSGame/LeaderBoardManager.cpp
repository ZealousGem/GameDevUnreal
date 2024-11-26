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
	APlayerController* Player = World->GetFirstPlayerController(); // instantites the player
	if(Player)
	{
		AMyCharacter* PlayerChar = Cast<AMyCharacter>(Player->GetPawn());
		if(PlayerChar)
		{
			LeaderboardStarts.Add(FLeaderboardStart(TEXT("You"), 0)); // creates a row containing the player
		}
	}

	int32 BotAmount = 1;

	for(TActorIterator<AEnemyBaseCharacter> It(World); It; ++It) // finds any ainstnatiated bot in the map 
	{
		
		AEnemyBaseCharacter* Bot = *It; //instanties a single bot
		if(Bot)
		{
			FString BotName = FString::Printf(TEXT("Bot %d"), BotAmount);
			Bot->Botname = BotName;// adds the bots state to the leader board
			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("Leaderboard made for %s"), *Bot->Botname));
			LeaderboardStarts.Add(FLeaderboardStart(BotName, 0));
			BotAmount += 1;
		}

		//if(BotAmount > 5)
		//{
	//		break; // will break once the counter has gone over bots in the world
	//	}
	}

	LeaderboardStarts.Sort([](const FLeaderboardStart& A, const FLeaderboardStart& B)
	{
		return A.Kills > B.Kills; // will sort from highest to lowest kills
	});
}

void ULeaderBoardManager::UpdatePlayerKills(int32 KillsNew)
{
	for (FLeaderboardStart& Enter:LeaderboardStarts)
	{
		if(Enter.Player == TEXT("You"))
		{
			Enter.Kills += KillsNew; // adds new kill value to leaderboard
			break;
		}
	}

	LeaderboardStarts.Sort([](const FLeaderboardStart& A, const FLeaderboardStart& B)
	{
		return A.Kills > B.Kills;  // will resort table if kills of that player has gone up
	});
}

void ULeaderBoardManager::UpdateBotKills(int32 KillsNew)
{
	for (FLeaderboardStart& Enter:LeaderboardStarts)
	{
		if(Enter.Player == TEXT("Bot 1"))
		{
			Enter.Kills += KillsNew; // adds new kill value to leaderboard
			break;
		}
	}

	LeaderboardStarts.Sort([](const FLeaderboardStart& A, const FLeaderboardStart& B)
	{
		return A.Kills > B.Kills;  // will resort table if kills of that player has gone up
	});
}

void ULeaderBoardManager::UpdateBotKillCount(const FString& AiName, int32 KillCount)
{
	for (FLeaderboardStart& Enter:LeaderboardStarts)
	{
		if(Enter.Player == AiName)
		{
			Enter.Kills += KillCount;  // adds new kill value to leaderboard
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
