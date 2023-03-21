// Fill out your copyright notice in the Description page of Project Settings.

#include "IAtumTensor.h"


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

void IAtumTensor::GetSerializedValues_Implementation(TArray<uint8>& OutValues) const noexcept
{
	const uint64 ByteCount = Data ? Data->numel() * Data->element_size() : 0u;
	if (ByteCount == 0u)
		return;

	OutValues.AddUninitialized(ByteCount);
	FMemory::Memcpy(OutValues.GetData(), Data->data_ptr(), ByteCount);
}

std::ostream& operator<<(std::ostream& OutStream, const IAtumTensor& AtumTensor) noexcept
{
	if (const torch::Tensor* const Tensor = AtumTensor.Data.Get(); Tensor)
	{
		OutStream << *Tensor;
	}
	return OutStream;
}

std::ostream& operator<<(std::ostream& OutStream, const TScriptInterface<IAtumTensor>& AtumTensor) noexcept
{
	if (const IAtumTensor* const Interface = AtumTensor.GetInterface(); Interface)
	{
		OutStream << *Interface;
	}
	return OutStream;
}
