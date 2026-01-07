#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioCaptureComponent.h"
#include "NiagaraSystem.h"
#include "Cassette.generated.h"


UCLASS()
class VRTESTPROJECT_API ACassette : public AActor
{
	GENERATED_BODY()
	
public:	
	ACassette();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Cassette Data")
	USoundBase* MusicTrack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Cassette Data")
	FString TapeName;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Microphone")
	UAudioCaptureComponent* AudioCaptureComp;

	UPROPERTY(EditAnywhere, Category = "Settings|Effects")
	UNiagaraSystem* DustEffect;
	
	UPROPERTY(EditAnywhere, Category = "Settings|Cleaning")
	float MaxDistanceToFace = 25.0f;

	UPROPERTY(EditAnywhere, Category = "Settings|Cleaning")
	float BlowThreshold = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings|Cleaning")
	float DirtLevel = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bIsHeld;
	
	float CurrentMicVolume;

	UFUNCTION()
	void OnAudioEnvelopeValue(const float EnvelopeValue);

public:

	UFUNCTION(BlueprintCallable)
	void SetHeld(bool bNewHeld);

	UFUNCTION(BlueprintPure)
	bool IsClean() const { return DirtLevel <= 0.1f; }
	
	USoundBase* GetMusic() const { return MusicTrack; }
};