#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioManager.generated.h"


UCLASS()
class VRTESTPROJECT_API AAudioManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AAudioManager();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio VR")
	class USoundAttenuation* DefaultVRAttenuation;
	
	UFUNCTION(BlueprintCallable, Category = "Audio VR")
	void PlaySound3D(USoundBase* SoundToPlay, FVector Location, float Volume = 1.0f);
	
	UFUNCTION(BlueprintCallable, Category = "Audio VR")
	void SetSoundClassVolume(USoundClass* TargetClass, float NewVolume);

	UFUNCTION(BlueprintCallable, Category = "Audio VR")
	UAudioComponent* SpawnSound3D(USoundBase* SoundToPlay, FVector Location);

	UFUNCTION(BlueprintCallable, Category = "Audio VR")
	void PlayMusic(USoundBase* Music, float FadeInDuration = 2.0f);

	UFUNCTION(BlueprintCallable, Category = "Audio VR")
	void SetSoundFloatParameter(UAudioComponent* TargetSound, FName ParameterName, float Value);

private:
	UPROPERTY()
	UAudioComponent* CurrentMusicComponent;

};
