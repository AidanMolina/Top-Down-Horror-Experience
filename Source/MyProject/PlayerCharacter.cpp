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
