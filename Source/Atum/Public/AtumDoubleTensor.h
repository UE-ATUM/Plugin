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
};
