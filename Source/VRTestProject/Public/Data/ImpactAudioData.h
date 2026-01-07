#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "ImpactAudioData.generated.h"


USTRUCT(BlueprintType)
struct FSurfaceSoundPair
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UPhysicalMaterial* SurfaceMaterial;

	UPROPERTY(EditAnywhere)
	USoundBase* ImpactSound;
};


UCLASS()
class VRTESTPROJECT_API UImpactAudioData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Impacts")
	USoundBase* DefaultImpactSound;

	UPROPERTY(EditAnywhere, Category = "Impacts")
	float MinVelocityToPlay = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Impacts")
	float VolumeMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Impacts")
	TArray<FSurfaceSoundPair> SurfaceSounds;

	USoundBase* GetSoundForSurface(UPhysicalMaterial* Surface) const
	{
		for (const auto& Pair : SurfaceSounds)
		{
			if (Pair.SurfaceMaterial == Surface)
				return Pair.ImpactSound;
		}
		
		return DefaultImpactSound;
	}
};