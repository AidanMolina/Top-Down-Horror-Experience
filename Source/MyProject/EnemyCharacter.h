// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.h"
#include "EnemyCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamageTaken);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS()
class MYPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	int health;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float attackCooldown;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	bool canAttack;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	bool isDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	int damageToDeal;

	FCollisionShape attackArea;
	FTimerHandle MyTimerHandle;

	UPROPERTY(BlueprintAssignable, Category = "Combat")
	FOnDamageTaken OnDamageTaken;

	UPROPERTY(BlueprintAssignable, Category = "Combat")
	FOnDeath OnDeath;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ResetAttack();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void TakeDamage(int damageToTake);

	UFUNCTION(BlueprintCallable)
	void Attack();
};
