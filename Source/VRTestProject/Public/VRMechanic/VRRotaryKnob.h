#pragma once
#include "CoreMinimal.h"
#include "VRMechanicBase.h"
#include "VRRotaryKnob.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VRTESTPROJECT_API UVRRotaryKnob : public UVRMechanicBase
{
	GENERATED_BODY()

public:
	UVRRotaryKnob();

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void UpdateInteraction(FVector HandLocation) override;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float MinAngle = -135.0f;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float MaxAngle = 135.0f;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float HapticInterval = 0.1f;

	float LastHapticValue;

	float CurrentRotationAngle;
};