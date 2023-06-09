﻿// © 2023 Kaya Adrian.

#pragma once

#include "IAtumTensor.h"

#include "AtumTensorInt.generated.h"


#define LOCTEXT_NAMESPACE "AtumTensorInt"

UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Int Tensor")
class ATUM_API UAtumTensorInt : public UObject, public IAtumTensor, public TAtumTensor<int32>
{
	GENERATED_BODY()
	
public:
	UE_NODISCARD_CTOR
	UAtumTensorInt() noexcept;
	
protected:
	UFUNCTION(BlueprintPure, Category = "ATUM|Tensor", DisplayName = "Get Values (Int)", meta = (
		Keywords = "ATUM Tensor Int int32 Get Out Values Sizes"
	))
	FORCEINLINE void K2_GetValues(TArray<int32>& OutValues, TArray<int64>& OutSizes) const noexcept
	{ GetValues(OutValues, OutSizes); }
	
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor", DisplayName = "Set Values (Int)", meta = (
		Keywords = "ATUM Tensor Int int32 Set Values Sizes"
	))
	FORCEINLINE void K2_SetValues(const TArray<int32>& Values, const TArray<int64>& Sizes) noexcept
	{ SetInternalValues(*this, Values, Sizes); }
};

#undef LOCTEXT_NAMESPACE
