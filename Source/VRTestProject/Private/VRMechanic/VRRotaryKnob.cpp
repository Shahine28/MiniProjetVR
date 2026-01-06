#include "VRMechanic/VRRotaryKnob.h"


UVRRotaryKnob::UVRRotaryKnob()
{
	CurrentRotationAngle = MinAngle;
}

void UVRRotaryKnob::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (InteractingHand)
	{
		UpdateInteraction(InteractingHand->GetComponentLocation());
	}
}

void UVRRotaryKnob::UpdateInteraction(FVector HandLocation)
{
	FVector LocalHandPos = GetComponentTransform().InverseTransformPosition(HandLocation);
	
	float RawAngle = FMath::RadiansToDegrees(FMath::Atan2(LocalHandPos.Z, LocalHandPos.Y));
	float ClampedAngle = FMath::Clamp(RawAngle, MinAngle, MaxAngle);


	SetRelativeRotation(FRotator(ClampedAngle, 0, 0));


	float Range = MaxAngle - MinAngle;
	float NewValue = (ClampedAngle - MinAngle) / Range;

	if (NewValue != CurrentValue)
	{
		CurrentValue = NewValue;
		OnValueChanged.Broadcast(CurrentValue);
	}
}