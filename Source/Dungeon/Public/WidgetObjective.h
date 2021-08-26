// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetObjective.generated.h"

class UTextBlock;
UCLASS()
class DUNGEON_API UWidgetObjective : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateObjectiveText(uint32 ObjectivesCompleted, uint32 TotalObjectives);
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Objective;
};
