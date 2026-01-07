#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FoodRecipeDA.generated.h"



UCLASS()
class VRTESTPROJECT_API UFoodRecipeDA : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recipe")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recipe")
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recipe")
	float TimeLimit = 60.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recipe")
	int32 ScoreReward = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recipe")
	TArray<FName> RequiredIngredients;
};
