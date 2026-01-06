#pragma once
#include "CoreMinimal.h"
#include "VRMechanicBase.h"
#include "VRLatchingButton.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRTESTPROJECT_API UVRLatchingButton : public UVRMechanicBase
{
	GENERATED_BODY()

public:
	UVRLatchingButton();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void UpdateInteraction(FVector HandLocation) override;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float PressDepth;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float AnimationSpeed;

	FVector InitialLocalLocation;
	FVector TargetLocation;
	
	float LastToggleTime;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UFUNCTION(BlueprintCallable, Category = "VR Interaction")
	void ReleaseButton();

	UFUNCTION(BlueprintPure, Category = "VR Interaction")
	bool IsPressed() const { return CurrentValue > 0.5f; }
};