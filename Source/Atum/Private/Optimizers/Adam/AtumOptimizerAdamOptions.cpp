// © 2023 Kaya Adrian.

#include "Optimizers/Adam/AtumOptimizerAdamOptions.h"


#define LOCTEXT_NAMESPACE "AtumOptimizerAdamOptions"

FAtumOptimizerAdamOptions::FAtumOptimizerAdamOptions() noexcept :
Lr(1E-3),
Betas({ 0.9, 0.999 }),
Eps(1E-8),
WeightDecay(0.0),
Amsgrad(false)
{
}

FAtumOptimizerAdamOptions::operator torch::optim::AdamOptions() const noexcept
{
	checkf(Betas.Num() == 2LL, TEXT("Betas must contain exactly 2 values!"))
	
	return torch::optim::AdamOptions(Lr)
	.betas(std::make_tuple(Betas[0], Betas[1]))
	.eps(Eps)
	.weight_decay(WeightDecay)
	.amsgrad(Amsgrad);
}

void FAtumOptimizerAdamOptions::SetFrom(const torch::optim::AdamOptions& Options) noexcept
{
	Lr = Options.lr();
	Eps = Options.eps();
	WeightDecay = Options.weight_decay();
	Amsgrad = Options.amsgrad();
	
	const std::tuple<double, double>& OptionBetas = Options.betas();
	Betas = { std::get<0ULL>(OptionBetas), std::get<1ULL>(OptionBetas) };
}

#undef LOCTEXT_NAMESPACE
