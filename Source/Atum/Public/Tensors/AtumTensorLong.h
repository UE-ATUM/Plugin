// © 2023 Kaya Adrian.

#pragma once

#include "IAtumTensor.h"

#include "AtumTensorLong.generated.h"


#define LOCTEXT_NAMESPACE "AtumTensorLong"

/**
 * Specific tensor implementation featuring long values
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Long Tensor")
class ATUM_API UAtumTensorLong : public UObject, public IAtumTensor, public TAtumTensor<int64>
{
	GENERATED_BODY()
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumTensorLong() noexcept;
	
protected:
	/**
	 * Blueprint function to get the values and sizes of this tensor
	 * 
	 * @param OutValues Array of values
	 * @param OutSizes Array of sizes
	 */
	UFUNCTION(BlueprintPure, Category = "ATUM|Tensor", DisplayName = "Get Values (Long)", meta = (
		Keywords = "ATUM Tensor Long int64 Get Out Values Sizes"
	))
	FORCEINLINE void K2_GetValues(TArray<int64>& OutValues, TArray<int64>& OutSizes) const noexcept
	{ GetValues(OutValues, OutSizes); }
	
	/**
	 * Blueprint function to set the values and sizes of this tensor
	 * 
	 * @param Values Array of new values
	 * @param Sizes Array of new sizes
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor", DisplayName = "Set Values (Long)", meta = (
		Keywords = "ATUM Tensor Long int64 Set Values Sizes"
	))
	FORCEINLINE void K2_SetValues(const TArray<int64>& Values, const TArray<int64>& Sizes) noexcept
	{ SetInternalValues(*this, Values, Sizes); }
};

#undef LOCTEXT_NAMESPACE
