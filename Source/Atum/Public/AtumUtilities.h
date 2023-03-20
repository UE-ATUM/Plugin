// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IAtumTensor.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "AtumUtilities.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType)
class ATUM_API UAtumUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "ATUM|Internal", CustomThunk)
	static FORCEINLINE void GetByteTensorValues(
		const TScriptInterface<const IAtumTensor>& Target,
		TArray<uint8>& OutValues
	) noexcept
	{ Target->GetValues(OutValues); }

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "ATUM|Internal", CustomThunk)
	static FORCEINLINE void GetDoubleTensorValues(
		const TScriptInterface<const IAtumTensor>& Target,
		TArray<double>& OutValues
	) noexcept
	{ Target->GetValues(OutValues); }

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "ATUM|Internal", CustomThunk)
	static FORCEINLINE void GetFloatTensorValues(
		const TScriptInterface<const IAtumTensor>& Target,
		TArray<float>& OutValues
	) noexcept
	{ Target->GetValues(OutValues); }
	
	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "ATUM|Internal", CustomThunk)
	static FORCEINLINE void GetIntTensorValues(
		const TScriptInterface<const IAtumTensor>& Target,
		TArray<int32>& OutValues
	) noexcept
	{ Target->GetValues(OutValues); }

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, Category = "ATUM|Internal", CustomThunk)
	static FORCEINLINE void GetLongTensorValues(
		const TScriptInterface<const IAtumTensor>& Target,
		TArray<int64>& OutValues
	) noexcept
	{ Target->GetValues(OutValues); }

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
	DECLARE_FUNCTION(execGetByteTensorValues) noexcept;
	DECLARE_FUNCTION(execGetDoubleTensorValues) noexcept;
	DECLARE_FUNCTION(execGetFloatTensorValues) noexcept;
	DECLARE_FUNCTION(execGetIntTensorValues) noexcept;
	DECLARE_FUNCTION(execGetLongTensorValues) noexcept;
	DECLARE_FUNCTION(execK2_SerializeArray) noexcept;
	DECLARE_FUNCTION(execK2_DeserializeArray) noexcept;
	DECLARE_FUNCTION(execConv_TensorToString);
};
