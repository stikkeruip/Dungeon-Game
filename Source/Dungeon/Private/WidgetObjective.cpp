// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetObjective.h"
#include "Components/TextBlock.h"

void UWidgetObjective::UpdateObjectiveText(uint32 ObjectivesCompleted, uint32 TotalObjectives)
{
	if (Objective)
	{	
		Objective->SetText(FText::Format(FTextFormat::FromString("{0} / {1}"), ObjectivesCompleted, TotalObjectives));
	}
}


