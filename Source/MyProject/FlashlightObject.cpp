// Fill out your copyright notice in the Description page of Project Settings.


#include "FlashlightObject.h"
#include "PlayerCharacter.h"
#include "Components/SpotLightComponent.h"

void AFlashlightObject::Use(APlayerCharacter* Character)
{
	Super::Use(Character);
	if (Character)
	{
		Character->Spotlight->SetVisibility(true);
	}
}
