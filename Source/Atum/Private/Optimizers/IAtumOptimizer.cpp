// © 2023 Kaya Adrian.

#include "Optimizers/IAtumOptimizer.h"

#include "AtumSettings.h"
#include "Optimizers/AtumOptimizerBaseOptions.h"
#include "Tensors/IAtumTensor.h"

LIBTORCH_INCLUDES_START
#include <torch/optim/optimizer.h>
LIBTORCH_INCLUDES_END


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

bool IAtumOptimizer::InitializeData_Implementation(const bool bRetry) noexcept
{
	if (bInitialized && !bRetry)
		return true;
	
	UObject* const OptimizerObject = _getUObject();
	const ANSICHAR* const OptimizerClassName = TCHAR_TO_UTF8(*GetNameSafe(OptimizerObject->GetClass()));
	
	const FAtumOptimizerBaseOptions* const BaseOptions = GetBaseOptimizerOptions();
	if (UNLIKELY(BaseOptions == nullptr))
	{
		bInitialized = false;
		ATUM_LOG(Error, TEXT("No options have been found in ATUM Optimizer of type `%hs`!"), OptimizerClassName)
		return bInitialized;
	}
	
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
			OptimizerClassName
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

bool IAtumOptimizer::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	throw std::logic_error(TCHAR_TO_UTF8(*FString::Printf(
		TEXT("OnInitializeData is not implemented in `%ls`!"),
		*GetNameSafe(_getUObject()->GetClass())
	)));
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

#undef LOCTEXT_NAMESPACE
