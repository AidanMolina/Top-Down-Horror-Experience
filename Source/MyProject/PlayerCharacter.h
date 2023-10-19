// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class MYPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* Inventory;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	bool hasGun;

	UFUNCTION(BlueprintCallable, Category = "Character")
	void CheckInteraction(AActor* target);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AddAmmo(int ammoToAdd);

	UFUNCTION(BlueprintCallable, Category = "Items")
	void UseItem(class AInteractableObjects* Item);

private:
	void LookAtCursor();
	void Shoot();
	void Reload();

	void DisplayMessage(FText message);

	int maxAmmo = 8;
	int currentAmmo = 5;
	int totalAmmo = 0;

};
