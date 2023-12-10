// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageObjects.h"
#include "PlayerCharacter.h"
#include "InventoryComponent.h"

void AMessageObjects::Use(APlayerCharacter* Character)
{
	if (Character)
	{
		Character->GetLocalViewingPlayerController()->SetInputMode(FInputModeUIOnly());
		if (!ItemName.IsEmpty())
		{
			if (Character->Inventory)
			{
				Character->Inventory->AddItem(this);
			}
		}
	}
}