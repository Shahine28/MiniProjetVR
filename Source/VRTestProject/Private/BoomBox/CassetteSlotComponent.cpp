#include "BoomBox/CassetteSlotComponent.h"


UCassetteSlotComponent::UCassetteSlotComponent()
{
	DetectionZone = CreateDefaultSubobject<UBoxComponent>(TEXT("DetectionZone"));
	DetectionZone->SetupAttachment(this);
	
	DetectionZone->SetBoxExtent(FVector(5.0f, 3.0f, 1.0f)); 
	DetectionZone->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void UCassetteSlotComponent::BeginPlay()
{
	Super::BeginPlay();
	DetectionZone->OnComponentBeginOverlap.AddDynamic(this, &UCassetteSlotComponent::OnOverlapBegin);
}

void UCassetteSlotComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CurrentCassette != nullptr)
		return;

	ACassette* IncomingCassette = Cast<ACassette>(OtherActor);
	if (!IncomingCassette)
		return;

	CurrentCassette = IncomingCassette;

	UPrimitiveComponent* CassetteMesh = Cast<UPrimitiveComponent>(CurrentCassette->GetRootComponent());
	if (CassetteMesh)
	{
		CassetteMesh->SetSimulatePhysics(false);
	}

	CurrentCassette->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	CurrentCassette->SetActorRelativeLocation(FVector::ZeroVector);
	CurrentCassette->SetActorRelativeRotation(FRotator::ZeroRotator);
	OnCassetteLoaded.Broadcast(CurrentCassette->GetMusic());
}

void UCassetteSlotComponent::EjectCassette()
{
	if (!CurrentCassette)
		return;

	CurrentCassette->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	UPrimitiveComponent* CassetteMesh = Cast<UPrimitiveComponent>(CurrentCassette->GetRootComponent());
	if (CassetteMesh)
	{
		CassetteMesh->SetSimulatePhysics(true);
		CassetteMesh->AddImpulse(GetUpVector() * 200.0f, NAME_None, true);
	}

	CurrentCassette = nullptr;
	OnCassetteLoaded.Broadcast(nullptr);
}

USoundBase* UCassetteSlotComponent::GetCurrentMusic() const
{
	if (CurrentCassette)
		return CurrentCassette->GetMusic();
	
	return nullptr;
}

ACassette* UCassetteSlotComponent::GetCurrentCassette()
{
	if (CurrentCassette)
		return CurrentCassette;

	return nullptr;
}
