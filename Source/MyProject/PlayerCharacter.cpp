// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LookAtCursor();

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerCharacter::Shoot);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCharacter::Reload);

}

void APlayerCharacter::LookAtCursor()
{
	FVector mouseLocation, mouseDirection;
	APlayerController* playerController = (APlayerController*)GetWorld()->GetFirstPlayerController();

	playerController->DeprojectMousePositionToWorld(mouseLocation, mouseDirection);
	FHitResult intersection;
	FCollisionQueryParams CollisionParameters;
	if (GetWorld()->LineTraceSingleByObjectType(intersection, mouseLocation, (mouseDirection * 10000) + mouseLocation, ECC_WorldStatic, CollisionParameters))
	{
		if (intersection.GetActor())
		{
			FRotator currentCharacterRotation = this->GetActorRotation();
			FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), intersection.ImpactPoint);
			FRotator newRotation = FRotator(currentCharacterRotation.Pitch, targetRotation.Yaw, currentCharacterRotation.Roll);
			this->SetActorRotation(newRotation);
		}
	}
}

void APlayerCharacter::CheckInteraction(AActor* target)
{
	TArray<FName> tags = target->Tags;

	if (target->ActorHasTag("Gun"))
	{
		hasGun = true;
	}
	else if (target->ActorHasTag("Ammo"))
	{
		AddAmmo(5);
	}
}

void APlayerCharacter::AddAmmo(int ammoToAdd)
{
	totalAmmo += ammoToAdd;
}

void APlayerCharacter::Shoot()
{
	if (hasGun)
	{
		if (currentAmmo > 0)
		{
			currentAmmo -= 1;

			FVector directionToShoot = GetActorForwardVector();
			FVector start = GetActorLocation();
			FVector end = start + (directionToShoot * 1000);

			FHitResult enemy;
			FCollisionQueryParams CollisionParameters;
			CollisionParameters.AddIgnoredActor(this);

			if (GetWorld()->LineTraceSingleByChannel(enemy, start, end, ECC_Pawn, CollisionParameters))
			{
				DrawDebugLine(GetWorld(), start, end, FColor::Red, false, 2.0f, 0.0f, 10.0f);
			}
		}
		else
		{
			//Play click sound to signify no ammo
		}

	}
}

void APlayerCharacter::Reload()
{
	if (totalAmmo >= maxAmmo)
	{
		int ammoToAdd = maxAmmo - currentAmmo;
		totalAmmo -= ammoToAdd;
		currentAmmo += ammoToAdd;
	}
	else
	{
		currentAmmo += totalAmmo;
		totalAmmo = 0;
	}
}
