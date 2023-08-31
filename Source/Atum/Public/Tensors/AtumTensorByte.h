// © 2023 Kaya Adrian.

#pragma once

#include "IAtumTensor.h"

#include "AtumTensorByte.generated.h"


#define LOCTEXT_NAMESPACE "AtumTensorByte"

/**
 * Specific tensor implementation featuring byte values
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Byte Tensor")
class ATUM_API UAtumTensorByte : public UObject, public IAtumTensor, public TAtumTensor<uint8>
{
	GENERATED_BODY()
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumTensorByte() noexcept;
	
protected:
	/**
	 * Blueprint function to get the values and sizes of this tensor
	 * 
	 * @param OutValues Array of values
	 * @param OutSizes Array of sizes
	 */
	UFUNCTION(BlueprintPure, Category = "ATUM|Tensor", DisplayName = "Get Values (Byte)", meta = (
		Keywords = "ATUM Tensor Byte uint8 Get Out Values Sizes"
	))
	FORCEINLINE void K2_GetValues(TArray<uint8>& OutValues, TArray<int64>& OutSizes) const noexcept
	{ GetValues(OutValues, OutSizes); }
	
	/**
	 * Blueprint function to set the values and sizes of this tensor
	 * 
	 * @param Values Array of new values
	 * @param Sizes Array of new sizes
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor", DisplayName = "Set Values (Byte)", meta = (
		Keywords = "ATUM Tensor Byte uint8 Set Values Sizes"
	))
	FORCEINLINE void K2_SetValues(const TArray<uint8>& Values, const TArray<int64>& Sizes) noexcept
	{ SetInternalValues(*this, Values, Sizes); }
};

#undef LOCTEXT_NAMESPACE
