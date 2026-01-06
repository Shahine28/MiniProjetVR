#include "VRMechanic/VRLatchingButton.h"


UVRLatchingButton::UVRLatchingButton()
{
	PressDepth = -1.5f;
	AnimationSpeed = 15.0f;
}

void UVRLatchingButton::BeginPlay()
{
	Super::BeginPlay();

	InitialLocalLocation = GetRelativeLocation();
	TargetLocation = InitialLocalLocation;

	OnComponentBeginOverlap.AddDynamic(this, &UVRLatchingButton::OnOverlapBegin);
}

void UVRLatchingButton::UpdateInteraction(FVector HandLocation)
{
}

void UVRLatchingButton::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner())
		return; 

	float TimeNow = GetWorld()->GetTimeSeconds();
	if (TimeNow - LastToggleTime < 0.2f)
		return;
	
	LastToggleTime = TimeNow;

	
	float NewValue = (CurrentValue > 0.5f) ? 0.0f : 1.0f;
	CurrentValue = NewValue;

	if (IsPressed())
	{
		FVector DepthVector = FVector(0, 0, PressDepth); 
		TargetLocation = InitialLocalLocation + DepthVector;
	}
	else
	{
		TargetLocation = InitialLocalLocation;
	}
	
	OnValueChanged.Broadcast(CurrentValue);
}

void UVRLatchingButton::ReleaseButton()
{
	if (IsPressed())
	{
		CurrentValue = 0.0f;
		TargetLocation = InitialLocalLocation;
		
		OnValueChanged.Broadcast(CurrentValue);
	}
}

void UVRLatchingButton::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector NewLoc = FMath::VInterpTo(GetRelativeLocation(), TargetLocation, DeltaTime, AnimationSpeed);
	SetRelativeLocation(NewLoc);
}
