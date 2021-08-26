// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageHandlerComponent.h"
#include "GameFramework/Character.h"
#include "DungeonPlayerCharacter.generated.h"

class UHealthComponent;
UCLASS()
class DUNGEON_API ADungeonPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADungeonPlayerCharacter();

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleSystemComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnDeath(bool IsFellOut);

	UPROPERTY(EditAnywhere)
	UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere)
	UDamageHandlerComponent* DamageHandlerComponent;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

	virtual void SetOnFire(float BaseDamage, float DamageTotalTime, float TakeDamageInterval);
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
