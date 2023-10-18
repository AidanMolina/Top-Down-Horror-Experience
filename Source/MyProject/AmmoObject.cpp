// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoObject.h"
#include "PlayerCharacter.h"

void AAmmoObject::Use(class APlayerCharacter* Character)
{
	if (Character)
	{
		Character->AddAmmo(ammoAmount);
	}
}