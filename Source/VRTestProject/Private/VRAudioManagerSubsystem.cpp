#include "VRAudioManagerSubsystem.h"
#include "VRAudioController.h"


void UVRAudioManagerSubsystem::RegisterController(UVRAudioController* Controller)
{
	if (Controller)
	{
		ActiveControllers.AddUnique(Controller);
	}
}

void UVRAudioManagerSubsystem::UnregisterController(UVRAudioController* Controller)
{
	if (Controller)
	{
		ActiveControllers.Remove(Controller);
	}
}

void UVRAudioManagerSubsystem::SetAllAudioPaused(bool bPaused)
{
	for (UVRAudioController* Controller : ActiveControllers)
	{
		if (IsValid(Controller))
		{
			Controller->SetPaused(bPaused);
		}
	}
}

void UVRAudioManagerSubsystem::SetGlobalVolumeMultiplier(float NewVolume)
{
	for (UVRAudioController* Controller : ActiveControllers)
	{
		if (IsValid(Controller))
		{
			Controller->SetVolumeMultiplier(NewVolume);
		}
	}
}