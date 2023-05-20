﻿// © 2023 Kaya Adrian.

#include "Tensors/IAtumTensor.h"


IAtumTensor::IAtumTensor() noexcept : Data(nullptr), ScalarType(EAtumTensorScalarType::Undefined)
{
}

void IAtumTensor::GetSizes(TArray<int64>& OutSizes) const noexcept
{
	const c10::IntArrayRef DataSizes = Data->sizes();
	OutSizes = TArray(DataSizes.data(), DataSizes.size());
}

EAtumTensorScalarType IAtumTensor::GetScalarType() const noexcept
{
	return ScalarType == EAtumTensorScalarType::Undefined ? AtumEnums::Cast(Data->scalar_type()) : ScalarType;
}

int64 IAtumTensor::GetElementCount() const noexcept
{
	return Data ? Data->numel() : 0LL;
}

int64 IAtumTensor::GetElementSize() const noexcept
{
	return Data ? Data->element_size() : 0LL;
}

void IAtumTensor::GetSerializedValues(TArray<uint8>& OutValues, TArray<int64>& OutSizes) const noexcept
{
	const uint64 ByteCount = Data ? Data->numel() * Data->element_size() : 0ULL;
	if (ByteCount == 0ULL)
	{
		OutSizes.AddZeroed();
		return;
	}

	OutValues.AddUninitialized(ByteCount);
	FMemory::Memcpy(OutValues.GetData(), Data->data_ptr(), ByteCount);
	GetSizes(OutSizes);
}

void IAtumTensor::SetSerializedValues(const TArray<uint8>& Values, const TArray<int64>& Sizes) noexcept
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

void IAtumTensor::CloneData(TScriptInterface<IAtumTensor>& OutClone, UObject* const Outer) const noexcept
{
	if (OutClone = DuplicateObject(_getUObject(), Outer); OutClone && Data)
	{
		OutClone->SetData(*Data);
	}
}

IAtumTensor::operator FString() const noexcept
{
	std::ostringstream Stream;
	Stream << *this;
	return Stream.str().c_str();
}

std::ostream& operator<<(std::ostream& OutStream, const IAtumTensor& AtumTensor) noexcept
{
	if (const at::Tensor* const Tensor = AtumTensor.Data.Get())
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
