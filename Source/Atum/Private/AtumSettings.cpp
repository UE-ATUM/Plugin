// Fill out your copyright notice in the Description page of Project Settings.

#include "AtumSettings.h"


#define LOCTEXT_NAMESPACE "UAtumSettings"

UAtumSettings::UAtumSettings()
{
	CategoryName = TEXT("Plugins");
	SectionName = TEXT("LibTorch");
}

void UAtumSettings::PostInitProperties()
{
	Super::PostInitProperties();

#if WITH_EDITOR
	if (IsTemplate())
	{
		ImportConsoleVariableValues();
	}
#endif
}

#if WITH_EDITOR
void UAtumSettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	ExportValuesToConsoleVariables(PropertyChangedEvent.Property);
}
#endif

#undef LOCTEXT_NAMESPACE
