// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerLocalResponseNormOptions.h"


#define LOCTEXT_NAMESPACE "AtumLayerLocalResponseNormOptions"

FAtumLayerLocalResponseNormOptions::FAtumLayerLocalResponseNormOptions() noexcept :
Size(0LL),
Alpha(1E-4),
Beta(0.75),
K(1.0)
{
}

#undef LOCTEXT_NAMESPACE
