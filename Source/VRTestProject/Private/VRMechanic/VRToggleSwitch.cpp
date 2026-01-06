#include "VRMechanic/VRToggleSwitch.h"


UVRToggleSwitch::UVRToggleSwitch()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetGenerateOverlapEvents(true);
	
	bIsOn = false;
	OffAngle = -20.0f;
	OnAngle = 20.0f;
	SwitchSpeed = 20.0f;
}

void UVRToggleSwitch::BeginPlay()
{
	Super::BeginPlay();

	InitialRotation = GetRelativeRotation();
	
	TargetRotation = FRotator(OffAngle, 0, 0);
	SetRelativeRotation(TargetRotation);

	OnComponentBeginOverlap.AddDynamic(this, &UVRToggleSwitch::OnOverlapBegin);
}

void UVRToggleSwitch::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner())
		return;

	float TimeNow = GetWorld()->GetTimeSeconds();
	if (TimeNow - LastToggleTime < 0.3f)
		return;
	
	LastToggleTime = TimeNow;
	bIsOn = !bIsOn;
	
	CurrentValue = bIsOn ? 1.0f : 0.0f;

	float TargetPitch = bIsOn ? OnAngle : OffAngle;
	TargetRotation = FRotator(TargetPitch, 0, 0);

	OnValueChanged.Broadcast(CurrentValue);
}

void UVRToggleSwitch::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator NewRot = FMath::RInterpTo(GetRelativeRotation(), TargetRotation, DeltaTime, SwitchSpeed);
	SetRelativeRotation(NewRot);
}