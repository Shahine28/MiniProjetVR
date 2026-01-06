#pragma once
#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "VRAudioManagerSubsystem.generated.h"

class UVRAudioController;


UCLASS()
class VRTESTPROJECT_API UVRAudioManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	void RegisterController(UVRAudioController* Controller);

	void UnregisterController(UVRAudioController* Controller);
	
	UFUNCTION(BlueprintCallable, Category = "Global VR Audio")
	void SetAllAudioPaused(bool bPaused);

	UFUNCTION(BlueprintCallable, Category = "Global VR Audio")
	void SetGlobalVolumeMultiplier(float NewVolume);

private:
	UPROPERTY()
	TArray<UVRAudioController*> ActiveControllers;
};