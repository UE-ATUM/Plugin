// © 2023 Kaya Adrian.

#include "Layers/Recurrent/AtumLayerLstmOptions.h"


#define LOCTEXT_NAMESPACE "AtumLayerLstmOptions"

FAtumLayerLstmOptions::FAtumLayerLstmOptions() noexcept :
InputSize(0LL),
HiddenSize(0LL),
LayerCount(1LL),
bBias(true),
bBatchFirst(false),
Dropout(0.0),
bBidirectional(false),
ProjectionSize(0LL)
{
}

void FAtumLayerLstmOptions::SetFrom(const torch::nn::LSTMOptions& Options) noexcept
{
	InputSize = Options.input_size();
	HiddenSize = Options.hidden_size();
	LayerCount = Options.num_layers();
	bBias = Options.bias();
	bBatchFirst = Options.batch_first();
	Dropout = Options.dropout();
	bBidirectional = Options.bidirectional();
	ProjectionSize = Options.proj_size();
}

#undef LOCTEXT_NAMESPACE
