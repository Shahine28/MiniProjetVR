#pragma once
#include "CoreMinimal.h"
#include "VRAudioController.h"
#include "GameFramework/Actor.h"
#include "BoomBox.generated.h"

class UVRToggleSwitch;
class UVRRotaryKnob;
class UVRMomentaryButton;
class UVRLatchingButton;


UENUM(BlueprintType)
enum class ERadioState : uint8
{
	Stopped,
	Playing,
	Paused
};

UCLASS()
class VRTESTPROJECT_API ABoomBox : public AActor
{
	GENERATED_BODY()

public:
	ABoomBox();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	// ====== Components ======
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComp;

	// PLAY
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controls")
	UVRLatchingButton* ButtonPlay; 

	// PAUSE 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controls")
	UVRLatchingButton* ButtonPause;

	// STOP
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controls")
	UVRMomentaryButton* ButtonStop;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controls")
	UVRToggleSwitch* PowerSwitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controls")
	UVRRotaryKnob* VolumeKnob;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
	UVRAudioController* AudioController;

	// ====== Settings ======

	UPROPERTY(EditAnywhere, Category = "Audio Content")
	USoundBase* MusicSound;

	UPROPERTY(EditAnywhere, Category = "Audio Content")
	USoundBase* ClickSound;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	ERadioState CurrentState;

	bool bIsOn;

public:
	UFUNCTION(BlueprintCallable)
	void OnPowerSwitchChanged(float NewValue);

	// Bouton Play
	UFUNCTION(BlueprintCallable)
	void OnPlayStateChanged(float NewValue);

	// Bouton Pause
	UFUNCTION(BlueprintCallable)
	void OnPauseStateChanged(float NewValue);

	// Bouton Stop
	UFUNCTION(BlueprintCallable)
	void OnStopPressed(float NewValue);

	UFUNCTION()
	void OnVolumeChanged(float NewVolume);
};
