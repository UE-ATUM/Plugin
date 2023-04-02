// Fill out your copyright notice in the Description page of Project Settings.

#include "Tensors/IAtumTensor.h"


IAtumTensor::operator FString() const noexcept
{
	std::ostringstream Stream;
	Stream << *this;
	return Stream.str().c_str();
}

EAtumScalarType IAtumTensor::GetScalarType_Implementation() const noexcept
{
	return Data ? AtumEnums::Cast(Data->scalar_type()) : EAtumScalarType::Undefined;
}

int64 IAtumTensor::GetElementCount_Implementation() const noexcept
{
	return Data ? Data->numel() : 0;
}

int64 IAtumTensor::GetElementSize_Implementation() const noexcept
{
	return Data ? Data->element_size() : 0;
}

void IAtumTensor::GetSerializedValues_Implementation(TArray<uint8>& OutValues, TArray<int64>& OutSizes) const noexcept
{
	const uint64 ByteCount = Data ? Data->numel() * Data->element_size() : 0u;
	if (ByteCount == 0u)
	{
		OutSizes.AddZeroed();
		return;
	}

	OutValues.AddUninitialized(ByteCount);
	FMemory::Memcpy(OutValues.GetData(), Data->data_ptr(), ByteCount);

	const c10::IntArrayRef DataSizes = Data->sizes();
	OutSizes = TArray(DataSizes.data(), DataSizes.size());
}

void IAtumTensor::SetSerializedValues_Implementation(const TArray<uint8>& Values, const TArray<int64>& Sizes) noexcept
{
	SetData(torch::empty(c10::IntArrayRef(Sizes.GetData(), Sizes.Num())));
	
	uint64 MaxSize = Data->element_size();
	for (const int64 Size : Sizes)
	{
		MaxSize *= Size;
	}
	
	FMemory::Memcpy(
		Data->data_ptr(),
		Values.GetData(),
		std::min(static_cast<uint64>(Values.Num()), MaxSize)
	);
}

std::ostream& operator<<(std::ostream& OutStream, const IAtumTensor& AtumTensor) noexcept
{
	if (const torch::Tensor* const Tensor = AtumTensor.Data.Get())
	{
		OutStream << *Tensor;
	}
	return OutStream;
}

std::ostream& operator<<(std::ostream& OutStream, const TScriptInterface<IAtumTensor>& AtumTensor) noexcept
{
	if (const IAtumTensor* const Interface = AtumTensor.GetInterface())
	{
		OutStream << *Interface;
	}
	return OutStream;
}
