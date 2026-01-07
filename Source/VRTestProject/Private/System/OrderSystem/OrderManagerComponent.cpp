#include "System/OrderSystem/OrderManagerComponent.h"


UOrderManagerComponent::UOrderManagerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    NextOrderID = 0;
    SpawnTimer = 0.f;
}

void UOrderManagerComponent::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("OrderManager initialized. Waiting for first spawn..."));
}

void UOrderManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    SpawnTimer += DeltaTime;
    if (SpawnTimer >= OrderSpawnRate)
    {
        GenerateNewOrder();
        SpawnTimer = 0.f;
    }
    
    for (int32 i = CurrentOrders.Num() - 1; i >= 0; i--)
    {
        CurrentOrders[i].TimeRemaining -= DeltaTime;

        if (CurrentOrders[i].TimeRemaining <= 0.f)
        {
            int32 FailedID = CurrentOrders[i].OrderID;
            UE_LOG(LogTemp, Warning, TEXT("Order #%d FAILED (Timeout)!"), FailedID);
            
            OnOrderFailed.Broadcast(FailedID);
            RemoveOrder(i);
        }
    }
}

void UOrderManagerComponent::GenerateNewOrder()
{
    if (AvailableRecipes.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("GenerateNewOrder Failed: No recipes in AvailableRecipes list!"));
        return;
    }

    int32 RandomIndex = FMath::RandRange(0, AvailableRecipes.Num() - 1);
    UFoodRecipeDA* SelectedRecipe = AvailableRecipes[RandomIndex];

    if (!SelectedRecipe)
    {
        UE_LOG(LogTemp, Error, TEXT("GenerateNewOrder Failed: Selected Recipe at index %d is NULL!"), RandomIndex);
        return;
    }

    FActiveOrder NewOrder;
    NewOrder.OrderID = NextOrderID++;
    NewOrder.RecipeData = SelectedRecipe;
    NewOrder.TotalTime = SelectedRecipe->TimeLimit;
    NewOrder.TimeRemaining = SelectedRecipe->TimeLimit;

    UE_LOG(LogTemp, Log, TEXT("New Order Created - ID: %d | Dish: %s | Time: %f"), NewOrder.OrderID, *SelectedRecipe->DisplayName.ToString(), NewOrder.TotalTime);

    CurrentOrders.Add(NewOrder);
    OnOrderAdded.Broadcast(NewOrder);
}

bool UOrderManagerComponent::TrySubmitDish(UFoodRecipeDA* DishServed)
{
    if (!DishServed)
    {
        UE_LOG(LogTemp, Warning, TEXT("TrySubmitDish: Player tried to submit a NULL dish."));
        return false;
    }

    UE_LOG(LogTemp, Log, TEXT("Player submitting dish: %s. Checking against %d active orders..."), *DishServed->DisplayName.ToString(), CurrentOrders.Num());
    
    for (int32 i = 0; i < CurrentOrders.Num(); i++)
    {
        if (CurrentOrders[i].RecipeData == DishServed)
        {
            int32 CompletedID = CurrentOrders[i].OrderID;

            UE_LOG(LogTemp, Log, TEXT("SUCCESS! Dish matched Order #%d"), CompletedID);
            
            OnOrderCompleted.Broadcast(CompletedID);
            RemoveOrder(i);
            
            return true;
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("FAILURE: Dish %s was submitted but no matching order found."), *DishServed->DisplayName.ToString());

    return false;
}

void UOrderManagerComponent::RemoveOrder(int32 Index)
{
    if (CurrentOrders.IsValidIndex(Index))
    {
        int32 IDRemoved = CurrentOrders[Index].OrderID;
        CurrentOrders.RemoveAt(Index);
        
        UE_LOG(LogTemp, Verbose, TEXT("Order #%d removed from list. Remaining orders: %d"), IDRemoved, CurrentOrders.Num());
    }
}

