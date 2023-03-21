// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IAtumTensor.h"

#include "AtumByteTensor.generated.h"


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Byte Tensor")
class ATUM_API UAtumByteTensor : public UObject, public IAtumTensor, public TAtumTensorInternal<uint8>
{
	GENERATED_BODY()

protected:
	UE_NODISCARD
	virtual EAtumScalarType GetScalarType_Implementation() const noexcept override final;
	
	UFUNCTION(BlueprintPure, Category = "ATUM|Tensor", DisplayName = "Get Values (Byte)", meta = (
		Keywords = "ATUM Byte uint8 Tensor Get Out Values"
	))
	FORCEINLINE void K2_GetValues(TArray<uint8>& OutValues) const noexcept { GetValues(OutValues); }
};
