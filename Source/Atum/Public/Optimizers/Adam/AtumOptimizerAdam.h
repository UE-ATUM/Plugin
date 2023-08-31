// © 2023 Kaya Adrian.

#pragma once

#include "AtumOptimizerAdamOptions.h"
#include "Macros/AtumMacrosOptimizer.h"
#include "Optimizers/IAtumOptimizer.h"

#include "AtumOptimizerAdam.generated.h"


#define LOCTEXT_NAMESPACE "AtumOptimizerAdam"

/**
 * Adam optimiser implementation
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Adam Optimizer")
class ATUM_API UAtumOptimizerAdam : public UObject, public IAtumOptimizer
{
	GENERATED_BODY()
	GENERATED_ATUM_OPTIMIZER(FAtumOptimizerAdamOptions)
	
protected:
	/**
	 * Structure containing this instance's options
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumOptimizerAdamOptions Options;
};

#undef LOCTEXT_NAMESPACE
