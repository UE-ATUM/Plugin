// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AtumGraphUtilities.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType, MinimalAPI)
class UAtumGraphUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static inline const FName ResultPinName = TEXT("Result");
	static inline const FName TargetPinName = TEXT("Target");
	
	UE_NODISCARD
	static UClass* GetInputClass(const UEdGraphPin* FromPin);
};
