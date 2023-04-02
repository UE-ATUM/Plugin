// Fill out your copyright notice in the Description page of Project Settings.

#include "AtumLibraryTensors.h"

#include "IAtum.h"
#include "Kismet/KismetArrayLibrary.h"

#include <ranges>


void UAtumLibraryTensors::K2_SerializeArray(
	[[maybe_unused]] const TArray<UProperty*>& Target,
	[[maybe_unused]] TArray<uint8>& OutBytes
) noexcept
{
	UE_LOG(LogAtum, Warning, TEXT("Called UAtumUtilities::K2_SerializeArray from native code!"))
}

void UAtumLibraryTensors::K2_DeserializeArray(
	[[maybe_unused]] const TArray<uint8>& Bytes,
	[[maybe_unused]] const TArray<UProperty*>& TargetTypeProvider,
	[[maybe_unused]] TArray<UProperty*>& OutTarget
) noexcept
{
	UE_LOG(LogAtum, Warning, TEXT("Called UAtumUtilities::K2_DeserializeArray from native code!"))
}

UObject* UAtumLibraryTensors::Empty(const TSubclassOf<UObject> Class, const TArray<int64>& Sizes) noexcept
{
	check(Class->ImplementsInterface(UAtumTensor::StaticClass()))
	
	auto* const Tensor = NewObject<UObject>(GetTransientPackage(), Class);
	CastChecked<IAtumTensor>(Tensor)->SetData(
		torch::empty(c10::IntArrayRef(Sizes.GetData(), Sizes.Num()))
	);
	return Tensor;
}

UObject* UAtumLibraryTensors::Eye(const TSubclassOf<UObject> Class, const int64 Size) noexcept
{
	check(Class->ImplementsInterface(UAtumTensor::StaticClass()))
	
	auto* const Tensor = NewObject<UObject>(GetTransientPackage(), Class);
	CastChecked<IAtumTensor>(Tensor)->SetData(torch::eye(Size));
	return Tensor;
}

UObject* UAtumLibraryTensors::Ones(const TSubclassOf<UObject> Class, const TArray<int64>& Sizes) noexcept
{
	check(Class->ImplementsInterface(UAtumTensor::StaticClass()))
	
	auto* const Tensor = NewObject<UObject>(GetTransientPackage(), Class);
	CastChecked<IAtumTensor>(Tensor)->SetData(
		torch::ones(c10::IntArrayRef(Sizes.GetData(), Sizes.Num()))
	);
	return Tensor;
}

UObject* UAtumLibraryTensors::Random(const TSubclassOf<UObject> Class, const TArray<int64>& Sizes) noexcept
{
	check(Class->ImplementsInterface(UAtumTensor::StaticClass()))
	
	auto* const Tensor = NewObject<UObject>(GetTransientPackage(), Class);
	CastChecked<IAtumTensor>(Tensor)->SetData(
		torch::rand(c10::IntArrayRef(Sizes.GetData(), Sizes.Num()))
	);
	return Tensor;
}

UObject* UAtumLibraryTensors::RandN(const TSubclassOf<UObject> Class, const TArray<int64>& Sizes) noexcept
{
	check(Class->ImplementsInterface(UAtumTensor::StaticClass()))
	
	auto* const Tensor = NewObject<UObject>(GetTransientPackage(), Class);
	CastChecked<IAtumTensor>(Tensor)->SetData(
		torch::randn(c10::IntArrayRef(Sizes.GetData(), Sizes.Num()))
	);
	return Tensor;
}

void UAtumLibraryTensors::GenericArray_Serialize(
	const uint8* const TargetAddress,
	const FArrayProperty* const TargetProperty,
	TArray<uint8>& OutBytes
) noexcept
{
	check(TargetProperty)
	if (TargetAddress == nullptr)
		return;

	FScriptArrayHelper TargetArray(TargetProperty, TargetAddress);
	OutBytes = TArray(TargetArray.GetRawPtr(), TargetArray.Num() * TargetProperty->Inner->GetSize());
}

void UAtumLibraryTensors::GenericArray_Deserialize(
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
	OutTargetArray.AddUninitializedValues(ElementCount);

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
void UAtumLibraryTensors::execK2_SerializeArray(
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

void UAtumLibraryTensors::execK2_DeserializeArray(
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

void UAtumLibraryTensors::execConv_TensorToString(
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
