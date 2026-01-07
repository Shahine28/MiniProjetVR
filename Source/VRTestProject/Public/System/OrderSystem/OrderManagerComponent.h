#pragma once
#include "CoreMinimal.h"
#include "FoodRecipeDA.h"
#include "Components/ActorComponent.h"
#include "OrderManagerComponent.generated.h"


UENUM(BlueprintType)
enum class EOrderStatus : uint8
{
	Pending,
	Completed,
	Failed
};

USTRUCT(BlueprintType)
struct FActiveOrder
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 OrderID;

	UPROPERTY(BlueprintReadOnly)
	UFoodRecipeDA* RecipeData;

	UPROPERTY(BlueprintReadOnly)
	float TimeRemaining;

	UPROPERTY(BlueprintReadOnly)
	float TotalTime;

	FActiveOrder()
	{
		OrderID = -1;
		RecipeData = nullptr;
		TimeRemaining = 0.f;
		TotalTime = 0.f;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOrderAdded, const FActiveOrder&, NewOrder);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOrderCompleted, int32, OrderID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOrderFailed, int32, OrderID);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VRTESTPROJECT_API UOrderManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UOrderManagerComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// --- CONFIGURATION ---
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	TArray<UFoodRecipeDA*> AvailableRecipes;

	UPROPERTY(EditAnywhere, Category = "Config")
	float OrderSpawnRate = 10.0f;
    
	UPROPERTY(BlueprintReadOnly, Category = "State")
	TArray<FActiveOrder> CurrentOrders;

	// --- EVENTS ---
    
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnOrderAdded OnOrderAdded;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnOrderCompleted OnOrderCompleted;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnOrderFailed OnOrderFailed;

	// --- FONCTIONS ---

	UFUNCTION(BlueprintCallable, Category = "Orders")
	void GenerateNewOrder();

	UFUNCTION(BlueprintCallable, Category = "Orders")
	bool TrySubmitDish(UFoodRecipeDA* DishServed);

private:
	float SpawnTimer;
	int32 NextOrderID;
    
	void RemoveOrder(int32 Index);
};
