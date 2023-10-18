// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObjects.h"
#include "MessageObject.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMessageObject : public AInteractableObjects
{
	GENERATED_BODY()
	
protected:

	virtual void Use(class APlayerCharacter* Character) override;

	
};
