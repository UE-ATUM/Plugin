// © 2023 Kaya Adrian.

#include "Optimizers/Adam/AtumOptimizerAdam.h"


#define LOCTEXT_NAMESPACE "AtumOptimizerAdam"

bool UAtumOptimizerAdam::OnInitializeData_Implementation([[maybe_unused]] const bool bRetry)
{
	Optimizer = MakeShareable(new torch::optim::Adam(
		std::vector<at::Tensor>(),
		static_cast<torch::optim::AdamOptions>(Options)
	), FOptimizerParametersDeleter());
	return true;
}

bool UAtumOptimizerAdam::LoadFromFile_Implementation(const FString& RelativePath)
{
	if (!IAtumOptimizer::LoadFromFile_Implementation(RelativePath))
		return false;
	
	Options.SetFrom(static_cast<torch::optim::AdamOptions&>(Optimizer->defaults()));
	return true;
}

#undef LOCTEXT_NAMESPACE
