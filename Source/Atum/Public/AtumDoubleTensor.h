// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IAtumTensor.h"

#include "AtumDoubleTensor.generated.h"


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Double Tensor")
class ATUM_API UAtumDoubleTensor : public UObject, public IAtumTensor, public TAtumTensorInternal<double>
{
	GENERATED_BODY()

protected:
	UE_NODISCARD
	virtual EAtumScalarType GetScalarType_Implementation() const noexcept override final;

	UFUNCTION(BlueprintPure, Category = "ATUM|Tensor", DisplayName = "Get Values (Double)", meta = (
		Keywords = "ATUM Double Tensor Get Out Values Sizes"
	))
	FORCEINLINE void K2_GetValues(TArray<double>& OutValues, TArray<int64>& OutSizes) const noexcept
	{ GetValues(OutValues, OutSizes); }

	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor", DisplayName = "Set Values (Double)", meta = (
		Keywords = "ATUM Double Tensor Set Values Sizes"
	))
	FORCEINLINE void K2_SetValues(const TArray<double>& Values, const TArray<int64>& Sizes) noexcept
	{ SetValues_Internal(*this, Values, Sizes); }
};
