// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioManager.h"
#include "Kismet/GameplayStatics.h"



UAudioManager* UAudioManager::Instance = nullptr;

UAudioManager::UAudioManager()
	: bIsInitialized(false)
{

}


UAudioManager* UAudioManager::GetInstance()
{
	if (!Instance)
	{
		Instance = NewObject<UAudioManager>();
		Instance->AddToRoot(); // Prevent garbage collection

		Instance->RegisterAllSounds(); // Ensure sounds are registered when instance is created
	}
	return Instance;

}

void UAudioManager::RegisterSound(const FString& SoundName, USoundCue* SoundCue)
{
	if (SoundCue)
	{
		SoundMap.Add(SoundName, SoundCue);
	}
}

void UAudioManager::PlaySound2DByName(const FString& SoundName, float Volume)
{
	if (SoundMap.Contains(SoundName))
	{
		UGameplayStatics::PlaySound2D(GWorld, SoundMap[SoundName], Volume);
	}
	else
	{

		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Sound '%s' not found!"), *SoundName));

	}
}

void UAudioManager::PlaySoundAtLocation(const FString& SoundName, UObject* WorldContextObject, FVector Location, float Volume)
{
	if (SoundMap.Contains(SoundName))
	{
		UGameplayStatics::PlaySoundAtLocation(WorldContextObject, SoundMap[SoundName], Location, Volume);

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Sound '%s' not found!"), *SoundName));

	}
}

void UAudioManager::RegisterAllSounds()
{

	if (bIsInitialized) return;

	bIsInitialized = true;

	USoundCue* ExplosionSound = LoadObject<USoundCue>(nullptr, TEXT("/Game/StarterContent/Audio/Explosion_Cue.Explosion_Cue"));
	USoundCue* GunshotSound = LoadObject<USoundCue>(nullptr, TEXT("/Game/StarterContent/Audio/Fire01_Cue.Fire01_Cue"));
	USoundCue* FootstepSound = LoadObject<USoundCue>(nullptr, TEXT("/Game/StarterContent/Audio/Footstep_Cue.Footstep_Cue"));

	// Add sounds to the map
	if (ExplosionSound) SoundMap.Add("Explosion", ExplosionSound);
	if (GunshotSound) SoundMap.Add("Gunshot", GunshotSound);
	if (FootstepSound) SoundMap.Add("Footstep", FootstepSound);

	// Debug messages
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("AudioManager: Sounds Registered!"));

}


