// © 2023 Kaya Adrian.

#pragma once

#include "AtumOptimizerBaseOptions.generated.h"

class IAtumTensor;


#define LOCTEXT_NAMESPACE "AtumOptimizerBaseOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Optimizer Base Options")
struct ATUM_API FAtumOptimizerBaseOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<TScriptInterface<IAtumTensor>> Parameters;
};

#undef LOCTEXT_NAMESPACE
