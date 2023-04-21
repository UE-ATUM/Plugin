// © 2023 Kaya Adrian.

#pragma once

#include "IAtumTensor.h"

#include "AtumTensorLong.generated.h"


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Long Tensor")
class ATUM_API UAtumTensorLong : public UObject, public IAtumTensor, public TAtumTensor<int64>
{
	GENERATED_BODY()

protected:
	UE_NODISCARD
	virtual EAtumScalarType GetScalarType() const noexcept override final;

	UFUNCTION(BlueprintPure, Category = "ATUM|Tensor", DisplayName = "Get Values (Long)", meta = (
		Keywords = "ATUM Tensor Long int64 Get Out Values Sizes"
	))
	FORCEINLINE void K2_GetValues(TArray<int64>& OutValues, TArray<int64>& OutSizes) const noexcept
	{ GetValues(OutValues, OutSizes); }

	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor", DisplayName = "Set Values (Long)", meta = (
		Keywords = "ATUM Tensor Long int64 Set Values Sizes"
	))
	FORCEINLINE void K2_SetValues(const TArray<int64>& Values, const TArray<int64>& Sizes) noexcept
	{ SetInternalValues(*this, Values, Sizes); }
};
