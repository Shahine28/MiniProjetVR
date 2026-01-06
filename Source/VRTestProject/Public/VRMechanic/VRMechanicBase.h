#pragma once
#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "VRMechanicBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMechanicValueChanged, float, NewValue);


UCLASS(Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VRTESTPROJECT_API UVRMechanicBase : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UVRMechanicBase();

	UPROPERTY(BlueprintAssignable, Category = "VR Interaction")
	FOnMechanicValueChanged OnValueChanged;

	UPROPERTY(BlueprintReadOnly, Category = "VR Interaction")
	USceneComponent* InteractingHand;

protected:
	virtual void BeginPlay() override;

	virtual void UpdateInteraction(FVector HandLocation) PURE_VIRTUAL(UVRMechanicBase::UpdateInteraction, );

	float CurrentValue;

public:
	UFUNCTION(BlueprintCallable, Category = "VR Interaction")
	virtual void StartInteraction(USceneComponent* HandComp);

	UFUNCTION(BlueprintCallable, Category = "VR Interaction")
	virtual void StopInteraction();
};