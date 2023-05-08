// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerInstanceNormOptions.h"


FAtumLayerInstanceNormOptions::FAtumLayerInstanceNormOptions() noexcept :
NumFeatures(0),
Epsilon(1e-5),
Momentum(0.1),
bAffine(false),
bTrackRunningStats(false)
{
}
