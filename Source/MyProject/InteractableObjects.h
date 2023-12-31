// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObjects.generated.h"

UCLASS(Abstract, BlueprintType, Blueprintable, DefaultToInstanced)
class MYPROJECT_API AInteractableObjects : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObjects();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	class UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FText ItemDescription;

	UPROPERTY()
	class UInventoryComponent* PlayerInventory;

	UPROPERTY(Transient)
	class UWorld* World;

	virtual void Use(class APlayerCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
	void OnUse(class APlayerCharacter* Character);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
