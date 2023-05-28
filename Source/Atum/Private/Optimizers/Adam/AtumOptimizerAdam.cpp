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

#undef LOCTEXT_NAMESPACE
