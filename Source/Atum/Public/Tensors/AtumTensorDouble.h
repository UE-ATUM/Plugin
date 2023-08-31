// © 2023 Kaya Adrian.

#pragma once

#include "IAtumTensor.h"

#include "AtumTensorDouble.generated.h"


#define LOCTEXT_NAMESPACE "AtumTensorDouble"

/**
 * Specific tensor implementation featuring double values
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Double Tensor")
class ATUM_API UAtumTensorDouble : public UObject, public IAtumTensor, public TAtumTensor<double>
{
	GENERATED_BODY()
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumTensorDouble() noexcept;
	
protected:
	/**
	 * Blueprint function to get the values and sizes of this tensor
	 * 
	 * @param OutValues Array of values
	 * @param OutSizes Array of sizes
	 */
	UFUNCTION(BlueprintPure, Category = "ATUM|Tensor", DisplayName = "Get Values (Double)", meta = (
		Keywords = "ATUM Tensor Double Get Out Values Sizes"
	))
	FORCEINLINE void K2_GetValues(TArray<double>& OutValues, TArray<int64>& OutSizes) const noexcept
	{ GetValues(OutValues, OutSizes); }
	
	/**
	 * Blueprint function to set the values and sizes of this tensor
	 * 
	 * @param Values Array of new values
	 * @param Sizes Array of new sizes
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor", DisplayName = "Set Values (Double)", meta = (
		Keywords = "ATUM Tensor Double Set Values Sizes"
	))
	FORCEINLINE void K2_SetValues(const TArray<double>& Values, const TArray<int64>& Sizes) noexcept
	{ SetInternalValues(*this, Values, Sizes); }
};

#undef LOCTEXT_NAMESPACE
