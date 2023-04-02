// © 2023 Kaya Adrian.

#pragma once

#include "IAtumTensor.h"

#include "AtumTensorDouble.generated.h"


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Double Tensor")
class ATUM_API UAtumTensorDouble : public UObject, public IAtumTensor, public TAtumTensorInternal<double>
{
	GENERATED_BODY()

protected:
	UE_NODISCARD
	virtual EAtumScalarType GetScalarType_Implementation() const noexcept override final;

	UFUNCTION(BlueprintPure, Category = "ATUM|Tensor", DisplayName = "Get Values (Double)", meta = (
		Keywords = "ATUM Tensor Double Get Out Values Sizes"
	))
	FORCEINLINE void K2_GetValues(TArray<double>& OutValues, TArray<int64>& OutSizes) const noexcept
	{ GetValues(OutValues, OutSizes); }

	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor", DisplayName = "Set Values (Double)", meta = (
		Keywords = "ATUM Tensor Double Set Values Sizes"
	))
	FORCEINLINE void K2_SetValues(const TArray<double>& Values, const TArray<int64>& Sizes) noexcept
	{ SetValues_Internal(*this, Values, Sizes); }
};
