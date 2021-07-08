// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorInteractionComponent.generated.h"

class ATriggerBox;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEON_API UDoorInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FRotator DesiredRotation = FRotator::ZeroRotator;
	FRotator Start = FRotator::ZeroRotator;
	FRotator Opened = FRotator::ZeroRotator;
	FRotator Closed = FRotator::ZeroRotator;
	FRotator CurrentRotation = FRotator::ZeroRotator;


	UPROPERTY(EditAnywhere)
	float TimeToRotate;
	float CurrentRotationTime = 0.0f;

	UPROPERTY(EditAnywhere)
	ATriggerBox* TriggerBox;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
