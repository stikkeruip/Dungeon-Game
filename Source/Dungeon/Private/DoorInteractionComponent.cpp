// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorInteractionComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Engine/LocalPlayer.h"


// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	Start = GetOwner()->GetActorRotation();
	Opened = GetOwner()->GetActorRotation() + DesiredRotation;
	CurrentRotationTime = 0.0f;

	// ...
	
}


// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	CurrentRotation = GetOwner()->GetActorRotation();
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (TriggerBox && GetWorld() && GetWorld()->GetFirstLocalPlayerFromController())
	{
		APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (PlayerPawn && TriggerBox->IsOverlappingActor(PlayerPawn))
		{
			CurrentRotationTime += DeltaTime;
			const float RotationAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
			const FRotator CurrentRotation = FMath::Lerp(CurrentRotation, Opened, RotationAlpha);
			GetOwner()->SetActorRotation(CurrentRotation);
		}
		else if (PlayerPawn && !TriggerBox->IsOverlappingActor(PlayerPawn) && GetOwner()->GetActorRotation() != Start)
		{
			CurrentRotationTime += DeltaTime;
			const float RotationAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.0f, 1.0f);
			const FRotator CurrentRotation = FMath::Lerp(CurrentRotation, Closed, RotationAlpha);
			GetOwner()->SetActorRotation(CurrentRotation);
		}
	}
	// ...
}

