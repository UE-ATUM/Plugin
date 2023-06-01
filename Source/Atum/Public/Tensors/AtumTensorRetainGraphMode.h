// © 2023 Kaya Adrian.

#pragma once

#include "AtumTensorRetainGraphMode.generated.h"


#define LOCTEXT_NAMESPACE "AtumTensorRetainGraphMode"

// Represents what to do with the graph from the IAtumTensor::Backward method
UENUM(BlueprintType, Category = "ATUM|Tensor", DisplayName = "ATUM Tensor Retain Graph Mode", meta = (
	Keywords = "ATUM Tensor Retain Graph Mode"
))
enum class EAtumTensorRetainGraphMode : uint8
{
	IfCreated UMETA(DisplayName = "If Created"), // Retains the graph only if it was created
	Never UMETA(DisplayName = "Never"), // Does not retain the graph, even if created
	Always UMETA(DisplayName = "Always") // Will try to retain the graph, even if not created
};

#undef LOCTEXT_NAMESPACE
