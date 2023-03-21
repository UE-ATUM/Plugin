// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IAtumTensor.h"

#include "AtumFloatTensor.generated.h"


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Float Tensor")
class ATUM_API UAtumFloatTensor : public UObject, public IAtumTensor, public TAtumTensorInternal<float>
{
	GENERATED_BODY()

protected:
	UE_NODISCARD
	virtual EAtumScalarType GetScalarType_Implementation() const noexcept override final;

	UFUNCTION(BlueprintPure, Category = "ATUM|Tensor", DisplayName = "Get Values (Float)", meta = (
		Keywords = "ATUM Float Tensor Get Out Values"
	))
	FORCEINLINE void K2_GetValues(TArray<float>& OutValues) const noexcept { GetValues(OutValues); }
};
