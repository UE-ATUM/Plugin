// © 2023 Kaya Adrian.

#include "Layers/IAtumLayer.h"

#include "FunctionLibraries/AtumLibraryUtilities.h"
#include "Macros/AtumMacrosLog.h"
#include "Tensors/IAtumTensor.h"

TORCH_INCLUDES_START
#include <torch/nn/module.h>
TORCH_INCLUDES_END


#define LOCTEXT_NAMESPACE "IAtumLayer"

IAtumLayer::IAtumLayer() noexcept : bInitialized(false), DimensionCount(0ULL)
{
}

const torch::nn::Module* IAtumLayer::GetBaseModule() const noexcept
{
	return nullptr;
}

const FAtumLayerBaseOptions* IAtumLayer::GetBaseLayerOptions() const noexcept
{
	return nullptr;
}

FAtumLayerBaseOptions* IAtumLayer::GetBaseLayerOptions() noexcept
{
	return nullptr;
}

bool IAtumLayer::AreInputSizesValid(const int32 InputSizeCount) const noexcept
{
	if (UNLIKELY(ValidInputSizes.empty()))
	{
		ATUM_LOG(Error, TEXT("No valid input size has been defined for this layer!"))
		return false;
	}
	
	if (!std::ranges::binary_search(ValidInputSizes, InputSizeCount))
	{
		ATUM_LOG(
			Error,
			TEXT("Expected %hs but got %dD input tensor!"),
			UAtumLibraryUtilities::FormatWithConjunction(ValidInputSizes, ", ", "", "D", " or ", false).c_str(),
			InputSizeCount
		)
		return false;
	}
	
	return true;
}

bool IAtumLayer::AreInputSizesValid(const TArray<int64>& InputSizes, const int64 ExpectedChannels) const noexcept
{
	const int32 SizeCount = InputSizes.Num();
	if (!AreInputSizesValid(SizeCount))
		return false;
	
	if (const int64 GivenChannels = InputSizes[SizeCount - DimensionCount - 1]; GivenChannels != ExpectedChannels)
	{
		ATUM_LOG(
			Error,
			TEXT("Expected %lld %ls but got %lld!"),
			ExpectedChannels,
			ExpectedChannels == 1LL ? TEXT("channel") : TEXT("channels"),
			GivenChannels
		)
		return false;
	}
	
	return true;
}

bool IAtumLayer::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	throw std::logic_error(TCHAR_TO_UTF8(*FString::Printf(
		TEXT("OnInitializeData is not implemented in `%ls`!"),
		*GetNameSafe(_getUObject()->GetClass())
	)));
}

bool IAtumLayer::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	Output = DuplicateObject(Input.GetObject(), nullptr);
	throw std::logic_error(TCHAR_TO_UTF8(*FString::Printf(
		TEXT("OnForward is not implemented in `%ls`!"),
		*GetNameSafe(_getUObject()->GetClass())
	)));
}

void IAtumLayer::CloneData_Implementation(TScriptInterface<IAtumLayer>& OutClone, UObject* const Outer) const noexcept
{
	if (OutClone = DuplicateObject(_getUObject(), Outer); OutClone)
	{
		OutClone->SetBaseModule(GetBaseModule());
	}
}

void IAtumLayer::GetParameters_Implementation(
	const UClass* const Class,
	TMap<FString, TScriptInterface<IAtumTensor>>& OutValues
) const noexcept
{
	check(Class->ImplementsInterface(UAtumTensor::StaticClass()))
	
	const torch::nn::Module* BaseModule = GetBaseModule();
	if (BaseModule == nullptr)
		return;
	
	for (const torch::OrderedDict<std::string, at::Tensor>::Item& Parameter : BaseModule->parameters_)
	{
		const at::Tensor& Value = Parameter.value();
		if (!Value.defined())
			continue;
		
		TScriptInterface<IAtumTensor> Tensor = NewObject<UObject>(GetTransientPackage(), Class);
		Tensor->SetData(Value);
		OutValues.Add(FString(Parameter.key().c_str()), MoveTemp(Tensor));
	}
}

void IAtumLayer::SetBaseModule([[maybe_unused]] const torch::nn::Module* const Value) noexcept
{
}

bool IAtumLayer::SaveToFile_Implementation(const FString& RelativePath) const
{
	if (!bInitialized)
		return false;
	
	torch::serialize::OutputArchive Archive;
	GetBaseModule()->save(Archive);
	
	Archive.save_to(TCHAR_TO_UTF8(*IAtumModule::GetContentDirectory(RelativePath)));
	return true;
}

bool IAtumLayer::LoadFromFile_Implementation(const FString& RelativePath)
{
	if (!bInitialized)
		return false;
	
	torch::serialize::InputArchive Archive;
	Archive.load_from(TCHAR_TO_UTF8(*IAtumModule::GetContentDirectory(RelativePath)));
	
	GetBaseModule()->load(Archive);
	return true;
}

bool IAtumLayer::InitializeData_Implementation(const bool bRetry) noexcept
{
	if (bInitialized && !bRetry)
		return true;

	UObject* const LayerObject = _getUObject();
	try
	{
		bInitialized = Execute_OnInitializeData(LayerObject, bRetry);
	}
	catch (const std::exception& Exception)
	{
		bInitialized = false;
		
		const std::string& ExceptionString = Exception.what();
		ATUM_LOG(
			Error,
			TEXT("Unhandled exception - %hs\nFailed to initialize ATUM Layer of type `%hs`!"),
			ExceptionString.substr(0, ExceptionString.find("\n")).c_str(),
			TCHAR_TO_UTF8(*GetNameSafe(LayerObject->GetClass()))
		)
	}
	
	return bInitialized;
}

bool IAtumLayer::Forward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
) noexcept
{
	UObject* const LayerObject = _getUObject();
	const ANSICHAR* const LayerClassName = TCHAR_TO_UTF8(*GetNameSafe(LayerObject->GetClass()));
	
	const at::Tensor* const Data = Input ? Input->GetData() : nullptr;
	const at::IntArrayRef& Sizes = Data ? Data->sizes() : at::IntArrayRef();
	
	if (Data == nullptr || Sizes.empty())
	{
		ATUM_LOG(Error, TEXT("Input had no data at ATUM Layer of type `%hs`!"), LayerClassName)
		return false;
	}
	
	for (const int64 Size : Sizes)
	{
		if (UNLIKELY(Size == 0LL))
		{
			ATUM_LOG(Error, TEXT("Input contains 0D dimension in ATUM Layer of type `%hs`!"), LayerClassName)
			return false;
		}
	}
	
	if (!bInitialized)
	{
		ATUM_LOG(Error, TEXT("ATUM Layer of type `%hs` has not been initialized!"), LayerClassName)
		return false;
	}
	
	try
	{
		Execute_OnForward(LayerObject, Input, Output);
	}
	catch (const std::exception& Exception)
	{
		const std::string& ExceptionString = Exception.what();
		ATUM_LOG(
			Error,
			TEXT("Unhandled exception - %hs\nFailed to forward in ATUM Layer of type `%hs`!"),
			ExceptionString.substr(0, ExceptionString.find("\n")).c_str(),
			LayerClassName
		)
		return false;
	}
	
	return true;
}

#undef LOCTEXT_NAMESPACE
