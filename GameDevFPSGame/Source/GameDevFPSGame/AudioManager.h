// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Sound/SoundCue.h"
#include "UObject/NoExportTypes.h"
#include "AudioManager.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVFPSGAME_API UAudioManager : public UObject
{
	GENERATED_BODY()

private:
	static UAudioManager* Instance;

	UAudioManager();

	// Map to hold sound cues by name
	TMap<FString, USoundCue*> SoundMap;

	// Ensure sounds are only registered once
	bool bIsInitialized;

	// Register all sounds (called internally)
	void RegisterAllSounds();


public:
	static UAudioManager* GetInstance();

	// Register a sound to the manager
	void RegisterSound(const FString& SoundName, USoundCue* SoundCue);

	

	// Play a registered sound by name
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlaySound2DByName(const FString& SoundName, float Volume = 0.10f);

	// Play a 3D sound at a location
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlaySoundAtLocation(const FString& SoundName, UObject* WorldContextObject, FVector Location, float Volume = 1.0f);


	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlayGameTheme(const FString& SoundName, UObject* WorldContextObject, float Volume = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void StopGameTheme();
};
