// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

// Pointer to the currently playing theme audio


UAudioManager* UAudioManager::Instance = nullptr;

static UAudioComponent* GameThemeAudioComponent = nullptr;

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
	// Adjust the file paths to match your new sounds
	USoundCue* FootstepSound = LoadObject<USoundCue>(nullptr, TEXT("/Game/Audio/FootSteps_Cue.FootSteps_Cue"));
	USoundCue* PrimaryGunSound = LoadObject<USoundCue>(nullptr, TEXT("/Game/Audio/PrimaryGunSound_Cue.PrimaryGunSound_Cue"));
	USoundCue* ShotgunSound = LoadObject<USoundCue>(nullptr, TEXT("/Game/Audio/ShotGunSound_Cue.ShotGunSound_Cue"));
	USoundCue* SwitchWeaponSound = LoadObject<USoundCue>(nullptr, TEXT("/Game/Audio/SwitchWeapons_Cue.SwitchWeapons_Cue"));
	USoundCue* GameThemeSound = LoadObject<USoundCue>(nullptr, TEXT("/Game/Audio/GameTheme_Cue.GameTheme_Cue"));
	
	// Add sounds to the map
	if (FootstepSound) SoundMap.Add("Footstep", FootstepSound);
	if (PrimaryGunSound) SoundMap.Add("PrimaryGun", PrimaryGunSound);
	if (ShotgunSound) SoundMap.Add("Shotgun", ShotgunSound);
	if (SwitchWeaponSound) SoundMap.Add("SwitchWeapon", SwitchWeaponSound);
	if (GameThemeSound) SoundMap.Add("GameTheme", GameThemeSound);

	// Debug messages
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("AudioManager: Sounds Registered!"));

}

void UAudioManager::PlayGameTheme(const FString& SoundName, UObject* WorldContextObject, float Volume)
{

	if (SoundMap.Contains(SoundName))
	{

		if (GameThemeAudioComponent && GameThemeAudioComponent->IsPlaying())
		{
			GameThemeAudioComponent->Stop();

		}
		GameThemeAudioComponent = UGameplayStatics::SpawnSound2D(WorldContextObject, SoundMap[SoundName], Volume, 1.0f, 0.0f, nullptr, true);


	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Sound '%s' not found!"), *SoundName));


	}

}

void UAudioManager::StopGameTheme()
{
	if (GameThemeAudioComponent && GameThemeAudioComponent->IsPlaying())
	{
		GameThemeAudioComponent->Stop();
		GameThemeAudioComponent = nullptr;

	}

}


