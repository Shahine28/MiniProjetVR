#include "VRMechanic/VRMomentaryButton.h"


UVRMomentaryButton::UVRMomentaryButton()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetGenerateOverlapEvents(true);
}

void UVRMomentaryButton::BeginPlay()
{
	Super::BeginPlay();
	InitialLocalLocation = GetRelativeLocation();
	TargetLocation = InitialLocalLocation;

	OnComponentBeginOverlap.AddDynamic(this, &UVRMomentaryButton::OnOverlapBegin);
	OnComponentEndOverlap.AddDynamic(this, &UVRMomentaryButton::OnOverlapEnd);
}

void UVRMomentaryButton::UpdateInteraction(FVector HandLocation) 
{
}

void UVRMomentaryButton::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner())
		return;

	CurrentValue = 1.0f;
	TargetLocation = InitialLocalLocation + FVector(0, 0, PressDepth);
	OnValueChanged.Broadcast(CurrentValue);
}

void UVRMomentaryButton::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == GetOwner())
		return;

	CurrentValue = 0.0f;
	TargetLocation = InitialLocalLocation;
	OnValueChanged.Broadcast(CurrentValue);
}

void UVRMomentaryButton::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	FVector NewLoc = FMath::VInterpTo(GetRelativeLocation(), TargetLocation, DeltaTime, ReturnSpeed);
	SetRelativeLocation(NewLoc);
}