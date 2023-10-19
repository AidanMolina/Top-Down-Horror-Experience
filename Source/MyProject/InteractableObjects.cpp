// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObjects.h"
#include "PlayerCharacter.h"
#include "InventoryComponent.h"

// Sets default values
AInteractableObjects::AInteractableObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AInteractableObjects::Use(APlayerCharacter* Character)
{
	if (Character)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Have a player character");
		if (Character->Inventory)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Player character has an inventory");
			Character->Inventory->AddItem(this);
		}
	}
}

// Called when the game starts or when spawned
void AInteractableObjects::BeginPlay()
{
	Super::BeginPlay();
	
}

