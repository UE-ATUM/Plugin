// Fill out your copyright notice in the Description page of Project Settings.

#include "AtumGraphUtilities.h"


UClass* UAtumGraphUtilities::GetInputClass(const UEdGraphPin* const FromPin)
{
	if (FromPin == nullptr || FromPin->Direction != EGPD_Input)
		return nullptr;
	
	const TArray<UEdGraphPin*>& LinkedPins = FromPin->LinkedTo;
	const int32 LinkedPinCount = LinkedPins.Num();

	UClass* InputClass = nullptr;
	if (FromPin->DefaultObject && LinkedPinCount == 0)
	{
		InputClass = CastChecked<UClass>(FromPin->DefaultObject.Get());
	}
	else if (const UEdGraphPin* const FirstLinkedPin = LinkedPinCount ? FromPin->LinkedTo[0] : nullptr)
	{
		InputClass = Cast<UClass>(FirstLinkedPin->PinType.PinSubCategoryObject.Get());
	}

	auto* const Blueprint = InputClass ? Cast<const UBlueprint>(InputClass->ClassGeneratedBy) : nullptr;
	UClass* const SkeletonClass = Blueprint ? Blueprint->SkeletonGeneratedClass : nullptr;

	return SkeletonClass ? SkeletonClass : InputClass;
}
