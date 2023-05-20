// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerBatchNormOptions.h"


FAtumLayerBatchNormOptions::FAtumLayerBatchNormOptions() noexcept :
NumFeatures(0LL),
Epsilon(1E-5),
Momentum(0.1),
bAffine(true),
bTrackRunningStats(true)
{
}
