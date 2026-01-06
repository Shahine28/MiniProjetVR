#include "AudioManager.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"


AAudioManager::AAudioManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAudioManager::BeginPlay()
{
	Super::BeginPlay();
}

void AAudioManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AAudioManager::PlaySound3D(USoundBase* SoundToPlay, FVector Location, float Volume)
{
	if (!SoundToPlay)
		return;

	USoundAttenuation* AttenuationToUse = DefaultVRAttenuation ? DefaultVRAttenuation : nullptr;

	UGameplayStatics::PlaySoundAtLocation(this, SoundToPlay, Location, Volume, 1.0f, 0.0f, AttenuationToUse);
}

void AAudioManager::SetSoundClassVolume(USoundClass* TargetClass, float NewVolume)
{
	if (!TargetClass)
		return;

	TargetClass->Properties.Volume = NewVolume;
}

UAudioComponent* AAudioManager::SpawnSound3D(USoundBase* SoundToPlay, FVector Location)
{
	if (!SoundToPlay)
		return nullptr;

	USoundAttenuation* Attenuation = DefaultVRAttenuation ? DefaultVRAttenuation : nullptr;

	UAudioComponent* NewComp = UGameplayStatics::SpawnSoundAtLocation(
		this, 
		SoundToPlay, 
		Location, 
		FRotator::ZeroRotator, 
		1.0f, 
		1.0f, 
		0.0f, 
		Attenuation
	);

	return NewComp;
}

void AAudioManager::PlayMusic(USoundBase* Music, float FadeInDuration)
{
	if (CurrentMusicComponent && CurrentMusicComponent->IsPlaying())
	{
		CurrentMusicComponent->FadeOut(1.0f, 0.0f); 
	}

	if (Music)
	{
		CurrentMusicComponent = UGameplayStatics::SpawnSound2D(this, Music);
		if (CurrentMusicComponent)
		{
			CurrentMusicComponent->FadeIn(FadeInDuration);
		}
	}
}

void AAudioManager::SetSoundFloatParameter(UAudioComponent* TargetSound, FName ParameterName, float Value)
{
	if (TargetSound)
	{
		TargetSound->SetFloatParameter(ParameterName, Value);
	}
}

