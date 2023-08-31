// © 2023 Kaya Adrian.

#pragma once

#include "IAtumTensor.h"

#include "AtumTensorInt.generated.h"


#define LOCTEXT_NAMESPACE "AtumTensorInt"

/**
 * Specific tensor implementation featuring integer values
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Int Tensor")
class ATUM_API UAtumTensorInt : public UObject, public IAtumTensor, public TAtumTensor<int32>
{
	GENERATED_BODY()
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumTensorInt() noexcept;
	
protected:
	/**
	 * Blueprint function to get the values and sizes of this tensor
	 * 
	 * @param OutValues Array of values
	 * @param OutSizes Array of sizes
	 */
	UFUNCTION(BlueprintPure, Category = "ATUM|Tensor", DisplayName = "Get Values (Int)", meta = (
		Keywords = "ATUM Tensor Int int32 Get Out Values Sizes"
	))
	FORCEINLINE void K2_GetValues(TArray<int32>& OutValues, TArray<int64>& OutSizes) const noexcept
	{ GetValues(OutValues, OutSizes); }
	
	/**
	 * Blueprint function to set the values and sizes of this tensor
	 * 
	 * @param Values Array of new values
	 * @param Sizes Array of new sizes
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor", DisplayName = "Set Values (Int)", meta = (
		Keywords = "ATUM Tensor Int int32 Set Values Sizes"
	))
	FORCEINLINE void K2_SetValues(const TArray<int32>& Values, const TArray<int64>& Sizes) noexcept
	{ SetInternalValues(*this, Values, Sizes); }
};

#undef LOCTEXT_NAMESPACE
