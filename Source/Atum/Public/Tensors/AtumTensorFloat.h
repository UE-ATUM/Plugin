// © 2023 Kaya Adrian.

#pragma once

#include "IAtumTensor.h"

#include "AtumTensorFloat.generated.h"


#define LOCTEXT_NAMESPACE "AtumTensorFloat"

/**
 * Specific tensor implementation featuring float values
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Float Tensor")
class ATUM_API UAtumTensorFloat : public UObject, public IAtumTensor, public TAtumTensor<float>
{
	GENERATED_BODY()
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumTensorFloat() noexcept;
	
protected:
	/**
	 * Blueprint function to get the values and sizes of this tensor
	 * 
	 * @param OutValues Array of values
	 * @param OutSizes Array of sizes
	 */
	UFUNCTION(BlueprintPure, Category = "ATUM|Tensor", DisplayName = "Get Values (Float)", meta = (
		Keywords = "ATUM Tensor Float Get Out Values Sizes"
	))
	FORCEINLINE void K2_GetValues(TArray<float>& OutValues, TArray<int64>& OutSizes) const noexcept
	{ GetValues(OutValues, OutSizes); }
	
	/**
	 * Blueprint function to set the values and sizes of this tensor
	 * 
	 * @param Values Array of new values
	 * @param Sizes Array of new sizes
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor", DisplayName = "Set Values (Float)", meta = (
		Keywords = "ATUM Tensor Float Set Values Sizes"
	))
	FORCEINLINE void K2_SetValues(const TArray<float>& Values, const TArray<int64>& Sizes) noexcept
	{ SetInternalValues(*this, Values, Sizes); }
};

#undef LOCTEXT_NAMESPACE
