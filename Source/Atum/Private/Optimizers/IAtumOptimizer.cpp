// © 2023 Kaya Adrian.

#include "Optimizers/IAtumOptimizer.h"

#include "IAtumModule.h"
#include "Macros/AtumMacrosLog.h"
#include "Optimizers/AtumOptimizerBaseOptions.h"
#include "Tensors/IAtumTensor.h"
#include "UObject/Package.h"

TORCH_INCLUDES_START
#include <torch/optim/optimizer.h>
#include <torch/serialize.h>
TORCH_INCLUDES_END


#define LOCTEXT_NAMESPACE "IAtumOptimizer"

void FOptimizerParametersDeleter::operator()(torch::optim::Optimizer* const Optimizer) const noexcept
{
	if (Optimizer == nullptr)
		return;
	
	std::vector<at::Tensor>& OldParameters = Optimizer->param_groups()[0].params();
	OldParameters.clear();
	OldParameters.~vector();
}

IAtumOptimizer::IAtumOptimizer() noexcept : bInitialized(false)
{
}

const FAtumOptimizerBaseOptions* IAtumOptimizer::GetBaseOptimizerOptions() const noexcept
{
	return nullptr;
}

FAtumOptimizerBaseOptions* IAtumOptimizer::GetBaseOptimizerOptions() noexcept
{
	return nullptr;
}

bool IAtumOptimizer::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	throw std::logic_error(TCHAR_TO_UTF8(*FString::Printf(
		TEXT("OnInitializeData is not implemented in `%ls`!"),
		*GetNameSafe(_getUObject()->GetClass())
	)));
}

bool IAtumOptimizer::SetGradientToZero_Implementation(const bool bSetToNone) noexcept
{
	if (Optimizer == nullptr)
		return false;
	
	Optimizer->zero_grad(bSetToNone);
	return true;
}

void IAtumOptimizer::K2_Step_Implementation(
	const UClass* const Class,
	TScriptInterface<IAtumTensor>& OutLoss,
	const FAtumOptimizerLossClosure& LossClosure
) noexcept
{
	check(Class->ImplementsInterface(UAtumTensor::StaticClass()))
	
	if (!bInitialized)
	{
		ATUM_LOG(
			Error,
			TEXT("ATUM Optimizer of type `%hs` has not been initialized!"),
			TCHAR_TO_UTF8(*GetNameSafe(_getUObject()->GetClass()))
		)
		return;
	}
	
	OutLoss = NewObject<UObject>(GetTransientPackage(), Class);
	OutLoss->SetData(Optimizer->step([Class, LossClosure]
	{
		const TScriptInterface<IAtumTensor> Loss = NewObject<UObject>(GetTransientPackage(), Class);
		if (UNLIKELY(LossClosure.IsBound()))
		{
			LossClosure.Execute(Loss);
		}
		return Loss->IsDefined() ? Loss->GetDataChecked() : at::Tensor();
	}));
}

void IAtumOptimizer::GetParameters_Implementation(TArray<TScriptInterface<IAtumTensor>>& OutParameters) const noexcept
{
	if (const FAtumOptimizerBaseOptions* const BaseOptions = GetBaseOptimizerOptions(); BaseOptions)
	{
		OutParameters = BaseOptions->Parameters;
	}
}

void IAtumOptimizer::SetParameters_Implementation(const TArray<TScriptInterface<IAtumTensor>>& Parameters) noexcept
{
	if (FAtumOptimizerBaseOptions* const BaseOptions = GetBaseOptimizerOptions(); BaseOptions)
	{
		BaseOptions->Parameters = Parameters;
	}
}

bool IAtumOptimizer::SaveToFile_Implementation(const FString& RelativePath) const
{
	if (!bInitialized)
		return false;
	
	torch::serialize::OutputArchive Archive;
	Optimizer->save(Archive);
	
	Archive.save_to(TCHAR_TO_UTF8(*IAtumModule::GetContentDirectory(RelativePath)));
	return true;
}

bool IAtumOptimizer::LoadFromFile_Implementation(const FString& RelativePath)
{
	if (!bInitialized)
		return false;
	
	torch::serialize::InputArchive Archive;
	Archive.load_from(TCHAR_TO_UTF8(*IAtumModule::GetContentDirectory(RelativePath)));
	
	Optimizer->load(Archive);
	return true;
}

bool IAtumOptimizer::InitializeData_Implementation(const bool bRetry) noexcept
{
	if (bInitialized && !bRetry)
		return true;
	
	UObject* const OptimizerObject = _getUObject();
	FAtumOptimizerBaseOptions* const BaseOptions = GetBaseOptimizerOptions();
	
	check(BaseOptions)
	try
	{
		bInitialized = Execute_OnInitializeData(OptimizerObject, bRetry);
	}
	catch (const std::exception& Exception)
	{
		bInitialized = false;
		
		const std::string& ExceptionString = Exception.what();
		ATUM_LOG(
			Error,
			TEXT("Unhandled exception - %hs\nFailed to initialize ATUM Optimizer of type `%hs`!"),
			ExceptionString.substr(0, ExceptionString.find("\n")).c_str(),
			TCHAR_TO_UTF8(*GetNameSafe(OptimizerObject->GetClass()))
		)
	}
	if (!bInitialized)
		return false;
	
	if (UNLIKELY(Optimizer == nullptr))
	{
		bInitialized = false;
		ATUM_LOG(Error, TEXT("Pointer in ATUM Optimizer `%hs` is null!"), TCHAR_TO_UTF8(*GetNameSafe(OptimizerObject)))
		return bInitialized;
	}
	
	std::vector<at::Tensor> Parameters;
	for (const TScriptInterface<IAtumTensor>& Tensor : BaseOptions->Parameters)
	{
		if (const at::Tensor* const TensorData = Tensor->GetData(); TensorData && TensorData->defined())
		{
			Parameters.push_back(*TensorData);
		}
	}
	Optimizer->param_groups()[0].params() = MoveTemp(Parameters);
	
	bInitialized = true;
	return bInitialized;
}

#undef LOCTEXT_NAMESPACE
