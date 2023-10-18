// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "InteractableObjects.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UInventoryComponent::AddItem(AInteractableObjects* Item)
{
	if (!Item)
	{
		return false;
	}
	Item->PlayerInventory = this;
	Item->World = GetWorld();
	Items.Add(Item);

	OnInventoryUpdated.Broadcast();
	return true;
}

bool UInventoryComponent::RemoveItem(AInteractableObjects* Item)
{
	if (Item)
	{
		Item->PlayerInventory = nullptr;
		Item->World = nullptr;
		Items.RemoveSingle(Item);
		OnInventoryUpdated.Broadcast();
		return true;
	}
	return false;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

