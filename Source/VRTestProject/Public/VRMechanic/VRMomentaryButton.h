#pragma once
#include "CoreMinimal.h"
#include "VRMechanicBase.h"
#include "VRMomentaryButton.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRTESTPROJECT_API UVRMomentaryButton : public UVRMechanicBase
{
	GENERATED_BODY()

public:
	UVRMomentaryButton();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void UpdateInteraction(FVector HandLocation) override;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float PressDepth = -1.0f;

	UPROPERTY(EditAnywhere, Category = "Settings")
	float ReturnSpeed = 10.0f;

	FVector InitialLocalLocation;
	FVector TargetLocation;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};