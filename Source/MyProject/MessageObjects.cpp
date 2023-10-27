// Fill out your copyright notice in the Description page of Project Settings.


#include "MessageObjects.h"
#include "PlayerCharacter.h"

void AMessageObjects::Use(APlayerCharacter* Character)
{
	if (Character)
	{
		Character->GetLocalViewingPlayerController()->SetInputMode(FInputModeUIOnly());
	}
}