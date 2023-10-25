// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObjects.h"
#include "FlashlightObject.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AFlashlightObject : public AInteractableObjects
{
	GENERATED_BODY()
	
protected:

	virtual void Use(class APlayerCharacter* Character) override;
};
