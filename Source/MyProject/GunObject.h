// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObjects.h"
#include "GunObject.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AGunObject : public AInteractableObjects
{
	GENERATED_BODY()
	
	virtual void Use(class APlayerCharacter* Character) override;
};
