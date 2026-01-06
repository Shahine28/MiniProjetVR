#include "VRAudioController.h"

#include "VRAudioManagerSubsystem.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"


UVRAudioController::UVRAudioController()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UVRAudioController::BeginPlay()
{
    Super::BeginPlay();
    
    AActor* Owner = GetOwner();
    if (Owner)
    {
        LoopingAudioComp = NewObject<UAudioComponent>(Owner);
        LoopingAudioComp->SetupAttachment(Owner->GetRootComponent());
        LoopingAudioComp->RegisterComponent();
        
        if (VRAttenuation)
        {
            LoopingAudioComp->AttenuationSettings = VRAttenuation;
        }
    }

    if (UWorld* World = GetWorld())
    {
        if (UVRAudioManagerSubsystem* AudioSys = World->GetSubsystem<UVRAudioManagerSubsystem>())
        {
            AudioSys->RegisterController(this);
        }
    }
}

void UVRAudioController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (UWorld* World = GetWorld())
    {
        if (UVRAudioManagerSubsystem* AudioSys = World->GetSubsystem<UVRAudioManagerSubsystem>())
        {
            AudioSys->UnregisterController(this);
        }
    }
    
    Super::EndPlay(EndPlayReason);
}

void UVRAudioController::PlayOneShot(USoundBase* SoundToPlay)
{
    if (!SoundToPlay)
        return;
    
    UGameplayStatics::PlaySoundAtLocation(
        this,
        SoundToPlay,
        GetOwner()->GetActorLocation(),
        1.0f,
        1.0f,
        0.0f,
        VRAttenuation
    );
}

void UVRAudioController::StartLoop(USoundBase* LoopSound, float FadeInTime)
{
    if (!LoopingAudioComp || !LoopSound)
        return;

    if (LoopingAudioComp->Sound == LoopSound && LoopingAudioComp->IsPlaying())
        return;

    LoopingAudioComp->SetSound(LoopSound);
    LoopingAudioComp->FadeIn(FadeInTime);
}

void UVRAudioController::StopLoop(float FadeOutTime)
{
    if (LoopingAudioComp && LoopingAudioComp->IsPlaying())
    {
        LoopingAudioComp->FadeOut(FadeOutTime, 0.0f);
    }
}

void UVRAudioController::SetLoopParameter(FName ParamName, float Value)
{
    if (LoopingAudioComp)
    {
        LoopingAudioComp->SetFloatParameter(ParamName, Value);
    }
}

void UVRAudioController::SetPaused(bool bShouldPause)
{
    if (LoopingAudioComp)
    {
        LoopingAudioComp->SetPaused(bShouldPause);
    }
}

void UVRAudioController::SetVolumeMultiplier(float Multiplier)
{
    if (LoopingAudioComp)
    {
        LoopingAudioComp->SetVolumeMultiplier(Multiplier);
    }
}
