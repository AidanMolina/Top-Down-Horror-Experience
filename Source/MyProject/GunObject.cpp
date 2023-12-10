// Fill out your copyright notice in the Description page of Project Settings.


#include "GunObject.h"
#include "PlayerCharacter.h"

void AGunObject::Use(APlayerCharacter* Character)
{
	Super::Use(Character);
	if (Character)
	{
		Character->hasGun = true;
	}
}
