// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IAtumTensor.h"

#include "AtumIntTensor.generated.h"


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Int Tensor")
class ATUM_API UAtumIntTensor : public UObject, public IAtumTensor, public TAtumTensorInternal<int32>
{
	GENERATED_BODY()

protected:
	UE_NODISCARD
	virtual EAtumScalarType GetScalarType_Implementation() const noexcept override final;

	UFUNCTION(BlueprintPure, Category = "ATUM|Tensor", DisplayName = "Get Values (Int)", meta = (
		Keywords = "ATUM Int int32 Tensor Get Out Values"
	))
	FORCEINLINE void K2_GetValues(TArray<int32>& OutValues) const noexcept { GetValues(OutValues); }
};
