#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sound/SoundAttenuation.h"
#include "VRAudioController.generated.h"

class UImpactAudioData;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRTESTPROJECT_API UVRAudioController : public UActorComponent
{
	GENERATED_BODY()

public:	
	UVRAudioController();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VR Audio Setup")
	USoundAttenuation* VRAttenuation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VR Audio Physics")
	UImpactAudioData* ImpactAudioConfig;

	UPROPERTY()
	UAudioComponent* LoopingAudioComp;

	UFUNCTION()
	void OnOwnerHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);

public:	
	
	UFUNCTION(BlueprintCallable, Category = "VR Audio Actions")
	void PlayOneShot(USoundBase* SoundToPlay);

	UFUNCTION(BlueprintCallable, Category = "VR Audio Actions")
	void StartLoop(USoundBase* LoopSound, float FadeInTime = 0.0f);
	
	UFUNCTION(BlueprintCallable, Category = "VR Audio Actions")
	void StopLoop(float FadeOutTime = 0.0f);
	
	UFUNCTION(BlueprintCallable, Category = "VR Audio Actions")
	void SetLoopParameter(FName ParamName, float Value);

	UFUNCTION(BlueprintCallable, Category = "VR Audio Actions")
	void SetPaused(bool bShouldPause);

	UFUNCTION(BlueprintCallable, Category = "VR Audio Actions")
	void SetVolumeMultiplier(float Multiplier);
};