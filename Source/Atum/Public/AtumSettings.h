// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AtumSettings.generated.h"


UCLASS(Config = "Atum", Blueprintable, BlueprintType, DisplayName = "ATUM Settings")
class ATUM_API UAtumSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UAtumSettings();
	
	virtual void PostInitProperties() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
