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
};
