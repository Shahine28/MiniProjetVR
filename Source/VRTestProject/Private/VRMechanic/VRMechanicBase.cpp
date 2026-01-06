#include "VRMechanic/VRMechanicBase.h"

UVRMechanicBase::UVRMechanicBase()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentValue = 0.0f;
}

void UVRMechanicBase::BeginPlay()
{
	Super::BeginPlay();
	SetGenerateOverlapEvents(true);
}

void UVRMechanicBase::StartInteraction(USceneComponent* HandComp)
{
	InteractingHand = HandComp;
	SetComponentTickEnabled(true);
}

void UVRMechanicBase::StopInteraction()
{
	InteractingHand = nullptr;
	SetComponentTickEnabled(false);
}