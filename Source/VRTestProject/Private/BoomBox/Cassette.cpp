#include "BoomBox/Cassette.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"


ACassette::ACassette()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComp;

	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionProfileName(TEXT("PhysicsActor"));

	PrimaryActorTick.bCanEverTick = true;

	AudioCaptureComp = CreateDefaultSubobject<UAudioCaptureComponent>(TEXT("MicCapture"));
	AudioCaptureComp->SetupAttachment(RootComponent);
	AudioCaptureComp->bAutoActivate = false;
}

void ACassette::BeginPlay()
{
	Super::BeginPlay();

	AudioCaptureComp->OnAudioEnvelopeValue.AddDynamic(this, &ACassette::OnAudioEnvelopeValue);
}

void ACassette::SetHeld(bool bNewHeld)
{
	bIsHeld = bNewHeld;

	if (bIsHeld)
	{
		AudioCaptureComp->Start();
	}
	else
	{
		AudioCaptureComp->Stop();
		CurrentMicVolume = 0.0f;
	}
}

void ACassette::OnAudioEnvelopeValue(const float EnvelopeValue)
{
	CurrentMicVolume = EnvelopeValue;
}

void ACassette::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsHeld)
		return;

	if (CurrentMicVolume > BlowThreshold)
	{
		APlayerCameraManager* CamManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
		if (CamManager)
		{
			FVector CamLoc = CamManager->GetCameraLocation();
			FVector CassetteLoc = GetActorLocation();

			
			float Distance = FVector::Dist(CamLoc, CassetteLoc);
			if(GEngine)
				GEngine->AddOnScreenDebugMessage(2, 0.0f, FColor::Cyan, FString::Printf(TEXT("Distance Tête: %.1f"), Distance));
			
			if (Distance < MaxDistanceToFace)
			{
				float CleanSpeed = 0.5f;
				DirtLevel = FMath::Clamp(DirtLevel - (CleanSpeed * DeltaTime), 0.0f, 1.0f);
				
				if (DirtLevel > 0.0f && FMath::RandRange(0, 10) == 0)
				{
					if (DustEffect)
					{
						UNiagaraFunctionLibrary::SpawnSystemAtLocation(
							this, 
							DustEffect, 
							GetActorLocation(), 
							GetActorRotation()
						);
					}
				}

				UE_LOG(LogTemp, Warning, TEXT("Nettoyage... Propreté : %f"), 1.0f - DirtLevel);
			}
		}
	}
}
