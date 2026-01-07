#include "VRMechanic/VRMechanicBase.h"
#include "Kismet/GameplayStatics.h"


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

void UVRMechanicBase::PlayHapticFeedback(USceneComponent* HandComp, float IntensityScale)
{
	if (!HapticEffect || !HandComp)
		return;

    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (PC)
    {
        EControllerHand HandToVibrate = EControllerHand::Right;
    
        FString CompName = HandComp->GetName();
        if (CompName.Contains(TEXT("Left")) || CompName.Contains(TEXT("Gaucher")))
        {
        	HandToVibrate = EControllerHand::Left;
        }

        PC->PlayHapticEffect(HapticEffect, HandToVibrate, IntensityScale);
    }
}

