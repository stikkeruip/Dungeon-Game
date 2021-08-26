// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageHandlerComponent.h"
#include "DungeonPlayerCharacter.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"
#include "Misc/ScopeLock.h"

// Sets default values for this component's properties
UDamageHandlerComponent::UDamageHandlerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<ADungeonPlayerCharacter>(GetOwner());
	// ...
	
}


void UDamageHandlerComponent::TakeFireDamage(float BaseDamage, float DamageTotalTime, float TakeDamageInterval)
{
	FScopeLock Lock(&CriticalSection);
	if (ActiveDamageInfo.IsSet())
	{
		ActiveDamageInfo.GetValue().BaseDamage = FMath::Max(ActiveDamageInfo.GetValue().BaseDamage, BaseDamage);
		ActiveDamageInfo.GetValue().IntervalTime = ActiveDamageInfo.GetValue().IntervalTime;
	}
	else
	{
		ActiveDamageInfo.Emplace();
		ActiveDamageInfo.GetValue().BaseDamage = BaseDamage;
		ActiveDamageInfo.GetValue().IntervalTime = TakeDamageInterval;
		ActiveDamageInfo.GetValue().LifeTime = DamageTotalTime;

		if (FireTemplate && PlayerCharacter->ParticleSystemComponent)
		{
			PlayerCharacter->ParticleSystemComponent->SetTemplate(FireTemplate);
			PlayerCharacter->ParticleSystemComponent->Activate(true);
		}
	}
}


// Called every frame
void UDamageHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PlayerCharacter)
	{
		FScopeLock Lock(&CriticalSection);
		if (ActiveDamageInfo.IsSet())
		{
			if (ActiveDamageInfo.GetValue().AccumulatedTime > ActiveDamageInfo.GetValue().LifeTime)
			{
				if (PlayerCharacter->ParticleSystemComponent)
				{
					PlayerCharacter->ParticleSystemComponent->Deactivate();
					PlayerCharacter->ParticleSystemComponent->SetTemplate(nullptr);
				}
				ActiveDamageInfo.Reset();
			}
			else
			{
				ActiveDamageInfo.GetValue().AccumulatedTime += DeltaTime;
				ActiveDamageInfo.GetValue().CurrentIntervalTime += DeltaTime;
				if (ActiveDamageInfo.GetValue().CurrentIntervalTime > ActiveDamageInfo.GetValue().IntervalTime)
				{
					float ModifiedDamage = ActiveDamageInfo.GetValue().BaseDamage / (ActiveDamageInfo.GetValue().LifeTime / ActiveDamageInfo.GetValue().IntervalTime);
					TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
					FDamageEvent DamageEvent(ValidDamageTypeClass);
					PlayerCharacter->TakeDamage(ModifiedDamage, DamageEvent, nullptr, GetOwner());
					ActiveDamageInfo.GetValue().CurrentIntervalTime = 0.0f;
				}
			}
		}
	}
}

