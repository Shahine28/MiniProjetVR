#pragma once
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Cassette.h"
#include "CassetteSlotComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCassetteChanged, USoundBase*, NewMusic);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VRTESTPROJECT_API UCassetteSlotComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UCassetteSlotComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* DetectionZone;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "State")
	ACassette* CurrentCassette;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(BlueprintAssignable, Category = "Cassette System")
	FOnCassetteChanged OnCassetteLoaded;

	bool HasCassette() const { return CurrentCassette != nullptr; }

	UFUNCTION(BlueprintCallable, Category = "Cassette System")
	USoundBase* GetCurrentMusic() const;

	UFUNCTION(BlueprintCallable, Category = "Cassette System")
	ACassette* GetCurrentCassette();

	UFUNCTION(BlueprintCallable, Category = "Cassette System")
	void EjectCassette();
};