// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	canAttack = true;
	isDead = false;
	attackArea = FCollisionShape::MakeBox(FVector(100, 100, 50));
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::TakeDamage(int damageToTake)
{
	health -= damageToTake;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Enemy has taken damage"));
	if (health <= 0)
	{
		isDead = true;
		canAttack = false;
		OnDeath.Broadcast();
	}
}

void AEnemyCharacter::Attack()
{
	if (canAttack)
	{
		canAttack = false;

		FHitResult SweepResult;
		FCollisionQueryParams CollisionParameters;
		CollisionParameters.AddIgnoredActor(this);

		if (GetWorld()->SweepSingleByChannel(SweepResult, this->GetActorLocation(), this->GetActorLocation(), FQuat::Identity, ECC_Pawn, attackArea, CollisionParameters))
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Some debug message!"));
			if (APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(SweepResult.GetActor()))
			{
				playerCharacter->TakeDamage(damageToDeal);
			}
		}

		GetWorld()->GetTimerManager().SetTimer(MyTimerHandle, this, &AEnemyCharacter::ResetAttack, attackCooldown, false);
	}
}

void AEnemyCharacter::ResetAttack()
{
	canAttack = true;
	GetWorld()->GetTimerManager().ClearTimer(MyTimerHandle);
}

