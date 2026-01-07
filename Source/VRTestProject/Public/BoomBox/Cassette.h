#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Cassette.generated.h"


UCLASS()
class VRTESTPROJECT_API ACassette : public AActor
{
	GENERATED_BODY()
	
public:	
	ACassette();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cassette Data")
	USoundBase* MusicTrack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cassette Data")
	FString TapeName;

public:
	USoundBase* GetMusic() const { return MusicTrack; }
};