// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAmmoUIUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthUIUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShoot);

UCLASS()
class MYPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Light")
	class USpotLightComponent* Spotlight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	bool hasGun;

	UPROPERTY(BlueprintReadWrite, Category = "Character")
	int currentAmmo = 5;

	UPROPERTY(BlueprintReadWrite, Category = "Character")
	int ammoLeft = 0;

	UPROPERTY(EditAnywhere, Category = "Character")
	float fireRate = 0.5f;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnAmmoUIUpdated OnAmmoUIUpdated;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnHealthUIUpdated OnHealthUIUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Character")
	FOnShoot OnShoot;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FOnPlayerDeath OnPlayerDeath;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	bool isDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	int health = 5;

	UPROPERTY(BlueprintReadWrite, Category = "Character")
	int maxHealth = 5;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void TakeDamage(int DamageTaken);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void HealDamage(int DamageHealed);

private:
	void LookAtCursor();
	void Shoot();
	void Reload();
	void CanFireAgain();

	bool canFire = true;

	int maxAmmo = 8;

	FTimerHandle FireRateTimerHandle;

};
