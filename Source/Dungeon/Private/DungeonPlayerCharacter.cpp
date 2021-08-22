// Fill out your copyright notice in the Description page of Project Settings.

#include "DungeonPlayerCharacter.h"

class APlayerController;

// Sets default values
ADungeonPlayerCharacter::ADungeonPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADungeonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADungeonPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADungeonPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADungeonPlayerCharacter::FellOutOfWorld(const class UDamageType& dmgType)
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		PlayerController->RestartLevel();
	}
}