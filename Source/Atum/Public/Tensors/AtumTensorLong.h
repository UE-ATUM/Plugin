// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IAtumTensor.h"

#include "AtumTensorLong.generated.h"


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Long Tensor")
class ATUM_API UAtumTensorLong : public UObject, public IAtumTensor, public TAtumTensorInternal<int64>
{
	GENERATED_BODY()

protected:
	UE_NODISCARD
	virtual EAtumScalarType GetScalarType_Implementation() const noexcept override final;

	UFUNCTION(BlueprintPure, Category = "ATUM|Tensor", DisplayName = "Get Values (Long)", meta = (
		Keywords = "ATUM Tensor Long int64 Get Out Values Sizes"
	))
	FORCEINLINE void K2_GetValues(TArray<int64>& OutValues, TArray<int64>& OutSizes) const noexcept
	{ GetValues(OutValues, OutSizes); }

	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor", DisplayName = "Set Values (Long)", meta = (
		Keywords = "ATUM Tensor Long int64 Set Values Sizes"
	))
	FORCEINLINE void K2_SetValues(const TArray<int64>& Values, const TArray<int64>& Sizes) noexcept
	{ SetValues_Internal(*this, Values, Sizes); }
};
