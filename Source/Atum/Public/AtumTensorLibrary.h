// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IAtumTensor.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "AtumTensorLibrary.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType)
class ATUM_API UAtumTensorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "ATUM|Cast", DisplayName = "Serialize Array", CustomThunk, meta = (
		ArrayParm = "Target",
		CompactNodeTitle = "Serialize",
		Keywords = "ATUM Cast Serialise Serialize Target Any Wildcard Array Out Bytes"
	))
	static void K2_SerializeArray(const TArray<UProperty*>& Target, TArray<uint8>& OutBytes) noexcept;
	
	UFUNCTION(BlueprintCallable, Category = "ATUM|Cast", DisplayName = "Deserialize Array", CustomThunk, meta = (
		ArrayParm = "TargetTypeProvider",
		ArrayTypeDependentParams = "OutTarget",
		CompactNodeTitle = "Deserialize",
		Keywords = "ATUM Cast Deserialise Deserialize Any Wildcard Bytes Out Target Type Provider"
	))
	static void K2_DeserializeArray(
		const TArray<uint8>& Bytes,
		const TArray<UProperty*>& TargetTypeProvider,
		TArray<UProperty*>& OutTarget
	) noexcept;

public:
	UE_NODISCARD
	UFUNCTION(BlueprintPure, Category = "ATUM|Cast", DisplayName = "To String", CustomThunk, meta = (
		BlueprintAutocast,
		CompactNodeTitle = "->",
		Keywords = "ATUM Cast Tensor To String"
	))
	static FORCEINLINE FString Conv_TensorToString(const TScriptInterface<const IAtumTensor>& Tensor)
	{ return Tensor->ToString(); }

	static void GenericArray_Serialize(
		const uint8* TargetAddress,
		const FArrayProperty* TargetProperty,
		TArray<uint8>& OutBytes
	) noexcept;

	static void GenericArray_Deserialize(
		const TArray<uint8>& Bytes,
		uint8* OutTargetAddress,
		const FArrayProperty* OutTargetProperty
	) noexcept;

private:
	DECLARE_FUNCTION(execK2_SerializeArray) noexcept;
	DECLARE_FUNCTION(execK2_DeserializeArray) noexcept;
	DECLARE_FUNCTION(execConv_TensorToString);
};
