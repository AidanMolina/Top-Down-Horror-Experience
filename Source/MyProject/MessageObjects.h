// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObjects.h"
#include "MessageObjects.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMessageObjects : public AInteractableObjects
{
	GENERATED_BODY()

protected:

	virtual void Use(class APlayerCharacter* Character) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = true))
	FText message;

};
