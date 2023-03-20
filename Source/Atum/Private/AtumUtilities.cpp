// Fill out your copyright notice in the Description page of Project Settings.

#include "AtumUtilities.h"

#include "IAtum.h"

#include <ranges>


void UAtumUtilities::K2_SerializeArray(
	[[maybe_unused]] const TArray<UProperty*>& Target,
	[[maybe_unused]] TArray<uint8>& OutBytes
) noexcept
{
	UE_LOG(LogAtum, Warning, TEXT("Called UAtumUtilities::K2_SerializeArray from native code!"))
}

void UAtumUtilities::K2_DeserializeArray(
	[[maybe_unused]] const TArray<uint8>& Bytes,
	[[maybe_unused]] const TArray<UProperty*>& TargetTypeProvider,
	[[maybe_unused]] TArray<UProperty*>& OutTarget
) noexcept
{
	UE_LOG(LogAtum, Warning, TEXT("Called UAtumUtilities::K2_DeserializeArray from native code!"))
}

void UAtumUtilities::GenericArray_Serialize(
	const uint8* const TargetAddress,
	const FArrayProperty* const TargetProperty,
	TArray<uint8>& OutBytes
) noexcept
{
	check(TargetProperty)
	if (TargetAddress)
	{
		FScriptArrayHelper TargetArray(TargetProperty, TargetAddress);
		OutBytes = TArray(TargetArray.GetRawPtr(), TargetArray.Num() * TargetProperty->Inner->GetSize());
	}
}

void UAtumUtilities::GenericArray_Deserialize(
	const TArray<uint8>& Bytes,
	uint8* const OutTargetAddress,
	const FArrayProperty* const OutTargetProperty
) noexcept
{
	check(OutTargetProperty)
	if (OutTargetAddress == nullptr)
		return;
	
	const FProperty* const OutTargetInnerProperty = OutTargetProperty->Inner;
	const int32 ElementSize = OutTargetInnerProperty->GetSize();
	const int32 ElementCount = Bytes.Num() / ElementSize;

	FScriptArrayHelper OutTargetArray(OutTargetProperty, OutTargetAddress);
	OutTargetArray.AddValues(ElementCount);

	const uint8* Source = Bytes.GetData();
	uint8* Destination = OutTargetArray.GetRawPtr();
	
	for ([[maybe_unused]] const int32 Dummy : std::ranges::iota_view(0, ElementCount))
	{
		OutTargetInnerProperty->CopySingleValueToScriptVM(Destination, Source);
		Source += ElementSize;
		Destination += ElementSize;
	}
}

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
void UAtumUtilities::execGetByteTensorValues(
	[[maybe_unused]] UObject* const Context,
	FFrame& Stack,
	[[maybe_unused]] void* const Z_Param__Result
) noexcept
{
	TScriptInterface<const IAtumTensor> TensorTemp;
	const TScriptInterface<const IAtumTensor>& Tensor = Stack
	.StepCompiledInRef<FInterfaceProperty, TScriptInterface<const IAtumTensor>>(&TensorTemp);

	P_GET_TARRAY_REF(uint8, OutValues)
		
	P_FINISH
		
	P_NATIVE_BEGIN
	GetByteTensorValues(Tensor, OutValues);
	P_NATIVE_END
}

void UAtumUtilities::execGetDoubleTensorValues(
	[[maybe_unused]] UObject* const Context,
	FFrame& Stack,
	[[maybe_unused]] void* const Z_Param__Result
) noexcept
{
	TScriptInterface<const IAtumTensor> TensorTemp;
	const TScriptInterface<const IAtumTensor>& Tensor = Stack
	.StepCompiledInRef<FInterfaceProperty, TScriptInterface<const IAtumTensor>>(&TensorTemp);

	P_GET_TARRAY_REF(double, OutValues)
		
	P_FINISH
		
	P_NATIVE_BEGIN
	GetDoubleTensorValues(Tensor, OutValues);
	P_NATIVE_END
}

void UAtumUtilities::execGetFloatTensorValues(
	[[maybe_unused]] UObject* const Context,
	FFrame& Stack,
	[[maybe_unused]] void* const Z_Param__Result
) noexcept
{
	TScriptInterface<const IAtumTensor> TensorTemp;
	const TScriptInterface<const IAtumTensor>& Tensor = Stack
	.StepCompiledInRef<FInterfaceProperty, TScriptInterface<const IAtumTensor>>(&TensorTemp);

	P_GET_TARRAY_REF(float, OutValues)
		
	P_FINISH
		
	P_NATIVE_BEGIN
	GetFloatTensorValues(Tensor, OutValues);
	P_NATIVE_END
}

void UAtumUtilities::execGetIntTensorValues(
	[[maybe_unused]] UObject* const Context,
	FFrame& Stack,
	[[maybe_unused]] void* const Z_Param__Result
) noexcept
{
	TScriptInterface<const IAtumTensor> TensorTemp;
	const TScriptInterface<const IAtumTensor>& Tensor = Stack
	.StepCompiledInRef<FInterfaceProperty, TScriptInterface<const IAtumTensor>>(&TensorTemp);

	P_GET_TARRAY_REF(int32, OutValues)
		
	P_FINISH
		
	P_NATIVE_BEGIN
	GetIntTensorValues(Tensor, OutValues);
	P_NATIVE_END
}

void UAtumUtilities::execGetLongTensorValues(
	[[maybe_unused]] UObject* const Context,
	FFrame& Stack,
	[[maybe_unused]] void* const Z_Param__Result
) noexcept
{
	TScriptInterface<const IAtumTensor> TensorTemp;
	const TScriptInterface<const IAtumTensor>& Tensor = Stack
	.StepCompiledInRef<FInterfaceProperty, TScriptInterface<const IAtumTensor>>(&TensorTemp);

	P_GET_TARRAY_REF(int64, OutValues)
		
	P_FINISH
		
	P_NATIVE_BEGIN
	GetLongTensorValues(Tensor, OutValues);
	P_NATIVE_END
}

void UAtumUtilities::execK2_SerializeArray(
	[[maybe_unused]] UObject* const Context,
	FFrame& Stack,
	[[maybe_unused]] void* const Z_Param__Result
) noexcept
{
	Stack.MostRecentProperty = nullptr;
	Stack.StepCompiledIn<FArrayProperty>(nullptr);

	const uint8* const TargetAddress = Stack.MostRecentPropertyAddress;
	const FArrayProperty* const TargetProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
	if (TargetProperty == nullptr)
	{
		Stack.bArrayContextFailed = true;
		return;
	}

	P_GET_TARRAY_REF(uint8, OutBytes)
	
	P_FINISH
		
	P_NATIVE_BEGIN
	GenericArray_Serialize(TargetAddress, TargetProperty, OutBytes);
	P_NATIVE_END
}

void UAtumUtilities::execK2_DeserializeArray(
	[[maybe_unused]] UObject* const Context,
	FFrame& Stack,
	[[maybe_unused]] void* const Z_Param__Result
) noexcept
{
	TArray<uint8> BytesTemp;
	const TArray<uint8>& Bytes = Stack.StepCompiledInRef<FArrayProperty, TArray<uint8>>(&BytesTemp);

	Stack.MostRecentProperty = nullptr;
	Stack.StepCompiledIn<FArrayProperty>(nullptr);
	
	if (CastField<FArrayProperty>(Stack.MostRecentProperty) == nullptr)
	{
		Stack.bArrayContextFailed = true;
		return;
	}

	Stack.MostRecentProperty = nullptr;
	Stack.StepCompiledIn<FArrayProperty>(nullptr);

	uint8* const OutTargetAddress = Stack.MostRecentPropertyAddress;
	const FArrayProperty* const OutTargetProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
	if (OutTargetProperty == nullptr)
	{
		Stack.bArrayContextFailed = true;
		return;
	}
	
	P_FINISH
	
	P_NATIVE_BEGIN
	GenericArray_Deserialize(Bytes, OutTargetAddress, OutTargetProperty);
	P_NATIVE_END
}

void UAtumUtilities::execConv_TensorToString(
	[[maybe_unused]] UObject* const Context,
	FFrame& Stack,
	void* const Z_Param__Result
)
{
	TScriptInterface<const IAtumTensor> TensorTemp;
	const TScriptInterface<const IAtumTensor>& Tensor = Stack
	.StepCompiledInRef<FInterfaceProperty, TScriptInterface<const IAtumTensor>>(&TensorTemp);
		
	P_FINISH
		
	P_NATIVE_BEGIN
	*static_cast<FString*>(Z_Param__Result) = Conv_TensorToString(Tensor);
	P_NATIVE_END
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning
