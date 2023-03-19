// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IAtumTensor.h"

#include "AtumLongTensor.generated.h"


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Long Tensor")
class ATUM_API UAtumLongTensor : public UObject, public IAtumTensor, public TAtumTensorInternal<int64>
{
	GENERATED_BODY()

protected:
	UE_NODISCARD
	virtual EAtumScalarType GetScalarType_Implementation() const noexcept override final;
};
