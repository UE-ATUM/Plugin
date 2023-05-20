// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerInstanceNormOptions.h"


#define LOCTEXT_NAMESPACE "AtumLayerInstanceNormOptions"

FAtumLayerInstanceNormOptions::FAtumLayerInstanceNormOptions() noexcept :
NumFeatures(0LL),
Epsilon(1E-5),
Momentum(0.1),
bAffine(false),
bTrackRunningStats(false)
{
}

#undef LOCTEXT_NAMESPACE
