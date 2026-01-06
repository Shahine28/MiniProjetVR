#pragma once
#include "CoreMinimal.h"
#include "VRMechanicBase.h"
#include "VRToggleSwitch.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRTESTPROJECT_API UVRToggleSwitch : public UVRMechanicBase
{
	GENERATED_BODY()

public:
	UVRToggleSwitch();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void UpdateInteraction(FVector HandLocation) override {};
	
	UPROPERTY(EditAnywhere, Category = "VR Switch")
	float OffAngle = -20.0f;

	UPROPERTY(EditAnywhere, Category = "VR Switch")
	float OnAngle = 20.0f;

	UPROPERTY(EditAnywhere, Category = "VR Switch")
	float SwitchSpeed = 15.0f;

	FRotator InitialRotation;
	FRotator TargetRotation;
	bool bIsOn;

	float LastToggleTime;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};