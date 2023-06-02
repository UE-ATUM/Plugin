// © 2023 Kaya Adrian.

#include "Tensors/IAtumTensor.h"

#include "IAtumModule.h"

TORCH_INCLUDES_START
#include <torch/serialize.h>
TORCH_INCLUDES_END


#define LOCTEXT_NAMESPACE "IAtumTensor"

IAtumTensor::IAtumTensor() noexcept : Data(nullptr), ScalarType(EAtumTensorScalarType::Undefined)
{
}

bool IAtumTensor::IsDefined() const noexcept
{
	return Data && Data->defined();
}

void IAtumTensor::GetGradient(TScriptInterface<IAtumTensor>& OutGradient) const noexcept
{
	if (OutGradient = IsDefined() ? DuplicateObject(_getUObject(), nullptr) : nullptr; OutGradient)
	{
		OutGradient->SetData(Data->grad());
	}
}

bool IAtumTensor::DoesRequireGradient() const noexcept
{
	return Data && Data->requires_grad();
}

IAtumTensor* IAtumTensor::SetRequireGradient(const bool bValue) noexcept
{
	if (Data)
	{
		SetData(Data->set_requires_grad(bValue));
	}
	return this;
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
	return IsDefined() ? Data->numel() : 0LL;
}

int64 IAtumTensor::GetElementSize() const noexcept
{
	return IsDefined() ? Data->element_size() : 0LL;
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

bool IAtumTensor::Backward(
	const TScriptInterface<IAtumTensor>& Gradient,
	const TArray<TScriptInterface<IAtumTensor>>& Inputs,
	const EAtumTensorRetainGraphMode RetainGraphMode,
	const bool bCreateGraph
) const noexcept
{
	if (!IsDefined() || !DoesRequireGradient())
		return false;
	
	at::Tensor GradientTensor = Gradient && Gradient->IsDefined() ?
		Gradient->GetDataChecked() : torch::ones_like(*Data, c10::TensorOptions().requires_grad(true));
	if (!Data->is_same_size(GradientTensor))
		return false;
	
	std::vector<at::Tensor> TensorList;
	TensorList.reserve(Inputs.Num());
	for (const TScriptInterface<IAtumTensor>& Input : Inputs)
	{
		if (Input->IsDefined() && Input->GetDataChecked().requires_grad())
		{
			TensorList.push_back(Input->GetDataChecked().to(c10::kFloat).set_requires_grad(true));
		}
	}
	
	const bool bRetainGraph = RetainGraphMode == EAtumTensorRetainGraphMode::Always;
	Data->backward(
		MoveTemp(GradientTensor),
		RetainGraphMode == EAtumTensorRetainGraphMode::IfCreated ? c10::nullopt : c10::optional<bool>(bRetainGraph),
		bCreateGraph,
		TensorList.empty() ? c10::nullopt : c10::optional<at::TensorList>(MoveTemp(TensorList))
	);
	return true;
}

IAtumTensor::operator FString() const noexcept
{
	std::ostringstream Stream;
	Stream << *this;
	return Stream.str().c_str();
}

void IAtumTensor::K2_SetRequireGradient(const bool bValue, TScriptInterface<IAtumTensor>& OutSelf) noexcept
{
	OutSelf = SetRequireGradient(bValue)->_getUObject();
}

bool IAtumTensor::SaveToFile_Implementation(const FString& RelativePath) const
{
	if (!IsDefined())
		return false;
	
	torch::save(*Data, TCHAR_TO_UTF8(*IAtumModule::GetContentDirectory(RelativePath)));
	return true;
}

bool IAtumTensor::LoadFromFile_Implementation(const FString& RelativePath)
{
	at::Tensor LoadedTensor;
	torch::load(LoadedTensor, TCHAR_TO_UTF8(*IAtumModule::GetContentDirectory(RelativePath)));
	SetData(MoveTemp(LoadedTensor));
	return IsDefined();
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

#undef LOCTEXT_NAMESPACE
