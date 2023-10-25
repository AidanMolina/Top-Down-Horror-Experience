// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "PickUpInterface.h"
#include "InteractableObjects.h"
#include "InventoryComponent.h"
#include "Components/SpotLightComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");

	Spotlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spotlight"));
	Spotlight->SetupAttachment(GetMesh());

	Spotlight->SetVisibility(false);

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
	if (target->GetClass()->ImplementsInterface(UPickUpInterface::StaticClass()))
	{
		IPickUpInterface* interaction = Cast<IPickUpInterface>(target);

		if (target->ActorHasTag("Gun"))
		{
			hasGun = true;
			
		}
		else if (target->ActorHasTag("Ammo"))
		{
			AddAmmo(interaction->Execute_PickUpAmmo(target));
			
		}
		else if (target->ActorHasTag("Message"))
		{
			DisplayMessage(interaction->Execute_PickUpMessage(target));
		}
	}

}

void APlayerCharacter::AddAmmo(int ammoToAdd)
{
	totalAmmo += ammoToAdd;
}

void APlayerCharacter::UseItem(AInteractableObjects* Item)
{
	if (Item)
	{
		Item->Use(this);
		Item->OnUse(this); //Blueprint event
	}
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

void APlayerCharacter::DisplayMessage(FText message)
{
	// Create a new FCanvasTextItem instance to contain the text.
	//FCanvasTextItem TextItem(FVector2D::ZeroVector, TestHUDText, BigFont, FLinearColor::Black);
	// Add the text into the FCanvasTextItem.
	//TextItem.Text = FText::Format(LOCTEXT("ExampleFText", "You currently have {0} health left."), CurrentHealth);
	// Draw the text to the screen with FCanvas::DrawItem.
	//Canvas->DrawItem(TextItem, 10.0f, 10.0f);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, message.ToString());
}
