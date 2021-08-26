// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HAL/CriticalSection.h"
#include "Misc/Optional.h"
#include "DamageHandlerComponent.generated.h"

class ADungeonPlayerCharacter;
class UParticleSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUNGEON_API UDamageHandlerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageHandlerComponent(const FObjectInitializer& ObjectInitializer);

	UParticleSystem* GetFireTemplate() { return FireTemplate; }

	void TakeFireDamage(float BaseDamage, float DamageTotalTime, float TakeDamageInterval);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class UParticleSystem* FireTemplate;

	struct FDamageInfo
	{
		float BaseDamage = 0.0f;
		float AccumulatedTime = 0.0f;
		float CurrentIntervalTime = 0.0f;
		float IntervalTime = 0.0f;
		float LifeTime = 0.0f;
	};

	TOptional<FDamageInfo> ActiveDamageInfo;

	ADungeonPlayerCharacter* PlayerCharacter = nullptr;

	FCriticalSection CriticalSection;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
