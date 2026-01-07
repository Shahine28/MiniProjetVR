#include "BoomBox/BoomBox.h"

#include "BoomBox/CassetteSlotComponent.h"
#include "VRMechanic/VRLatchingButton.h"
#include "VRMechanic/VRMomentaryButton.h"
#include "VRMechanic/VRRotaryKnob.h"
#include "VRMechanic/VRToggleSwitch.h"


ABoomBox::ABoomBox()
{
	PrimaryActorTick.bCanEverTick = false; 

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComp;

	// Play
	ButtonPlay = CreateDefaultSubobject<UVRLatchingButton>(TEXT("Btn_Play"));
	ButtonPlay->SetupAttachment(RootComponent);

	// Pause
	ButtonPause = CreateDefaultSubobject<UVRLatchingButton>(TEXT("Btn_Pause"));
	ButtonPause->SetupAttachment(RootComponent);

	// Stop
	ButtonStop = CreateDefaultSubobject<UVRMomentaryButton>(TEXT("Btn_Stop"));
	ButtonStop->SetupAttachment(RootComponent);

	// Power
	PowerSwitch = CreateDefaultSubobject<UVRToggleSwitch>(TEXT("PowerSwitch"));
	PowerSwitch->SetupAttachment(RootComponent);

	// Volume
	VolumeKnob = CreateDefaultSubobject<UVRRotaryKnob>(TEXT("VolumeKnob"));
	VolumeKnob->SetupAttachment(RootComponent);

	// Cassette
	CassetteSlot = CreateDefaultSubobject<UCassetteSlotComponent>(TEXT("CassetteSlot"));
	CassetteSlot->SetupAttachment(MeshComp);

	AudioController = CreateDefaultSubobject<UVRAudioController>(TEXT("AudioController"));
	
	bIsOn = false;
	CurrentState = ERadioState::Stopped;
}

void ABoomBox::BeginPlay()
{
	Super::BeginPlay();

	if (ButtonPlay)
		ButtonPlay->OnValueChanged.AddDynamic(this, &ABoomBox::OnPlayStateChanged);
	
	if (ButtonPause)
		ButtonPause->OnValueChanged.AddDynamic(this, &ABoomBox::OnPauseStateChanged);
	
	if (ButtonStop)
		ButtonStop->OnValueChanged.AddDynamic(this, &ABoomBox::OnStopPressed);
	
	if (PowerSwitch)
		PowerSwitch->OnValueChanged.AddDynamic(this, &ABoomBox::OnPowerSwitchChanged);

	if (VolumeKnob)
		VolumeKnob->OnValueChanged.AddDynamic(this, &ABoomBox::OnVolumeChanged);

	if (CassetteSlot)
		CassetteSlot->OnCassetteLoaded.AddDynamic(this, &ABoomBox::OnCassetteChanged);
}

// Bouton POWER
void ABoomBox::OnPowerSwitchChanged(float NewValue)
{
	bool bSwitchIsOn = NewValue > 0.5f;

	if (bIsOn == bSwitchIsOn)
		return;

	bIsOn = bSwitchIsOn;
	AudioController->PlayOneShot(ClickSound);

	if (!bIsOn)
	{
		AudioController->StopLoop(0.1f);
        
		if (ButtonPlay && ButtonPlay->IsPressed())
		{
			ButtonPlay->ReleaseButton();
		}
        
		CurrentState = ERadioState::Stopped;
	}
}

// Bouton PLAY
void ABoomBox::OnPlayStateChanged(float NewValue)
{
	if (!bIsOn)
		return; 

	bool bIsDown = NewValue > 0.5f;

	if (bIsDown)
	{
		AudioController->PlayOneShot(ClickSound);
		
		USoundBase* TapeMusic = CassetteSlot->GetCurrentMusic();
		if (TapeMusic)
		{
			if (CurrentState == ERadioState::Paused)
			{
				AudioController->SetPaused(false);
			}
			else
			{
				AudioController->StartLoop(TapeMusic, 0.5f);
			}
			
			CurrentState = ERadioState::Playing;
		}
		else
		{

			// AudioController->StartLoop(EmptyMotorSound);
			UE_LOG(LogTemp, Warning, TEXT("Aucune cassette insérée !"));
		}
	}
	else
	{
		if (CurrentState != ERadioState::Stopped)
		{
			AudioController->StopLoop(0.2f);
			CurrentState = ERadioState::Stopped;
		}
	}
}

// Bouton PAUSE
void ABoomBox::OnPauseStateChanged(float NewValue)
{
	if (!bIsOn)
		return;

	bool bIsDown = NewValue > 0.5f;

	if (!ButtonPlay->IsPressed()) 
	{
		if(bIsDown)
			ButtonPause->ReleaseButton();
		
		return;
	}

	AudioController->PlayOneShot(ClickSound);

	if (bIsDown)
	{
		AudioController->SetPaused(true);
	}
	else
	{
		AudioController->SetPaused(false);
	}
}

// Bouton STOP
void ABoomBox::OnStopPressed(float NewValue)
{
	if (NewValue < 0.5f)
		return;

	if (!bIsOn)
		return;

	AudioController->PlayOneShot(ClickSound);
	
	bool bSomethingPopped = false;

	if (ButtonPlay && ButtonPlay->IsPressed())
	{
		ButtonPlay->ReleaseButton();
		bSomethingPopped = true;
	}

	if (ButtonPause && ButtonPause->IsPressed())
	{
		ButtonPause->ReleaseButton();
		bSomethingPopped = true;
	}

	if (!bSomethingPopped && CurrentState == ERadioState::Stopped)
	{
		CassetteSlot->EjectCassette();
	}

	if (!bSomethingPopped)
	{
		AudioController->StopLoop(0.1f);
		CurrentState = ERadioState::Stopped;
	}
}

// Volume
void ABoomBox::OnVolumeChanged(float NewVolume)
{
	if (AudioController)
	{
		AudioController->SetVolumeMultiplier(NewVolume);
	}
}

void ABoomBox::OnCassetteChanged(USoundBase* NewMusic)
{
	if (NewMusic == nullptr && CurrentState == ERadioState::Playing)
	{
		// On arrête tout brutalement (ou avec un son de scratch !)
		AudioController->StopLoop(0.1f);
        
		if (ButtonPlay && ButtonPlay->IsPressed())
		{
			ButtonPlay->ReleaseButton();
		}
		CurrentState = ERadioState::Stopped;
	}
}
