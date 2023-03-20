// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "AtumGraphUtilities.generated.h"

class UEdGraphPin;


UCLASS(Abstract, Blueprintable, BlueprintType, MinimalAPI)
class UAtumGraphUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UE_NODISCARD
	static UClass* GetInputClass(const UEdGraphPin* FromPin);
};
