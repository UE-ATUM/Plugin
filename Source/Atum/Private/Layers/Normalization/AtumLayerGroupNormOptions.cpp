// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerGroupNormOptions.h"


#define LOCTEXT_NAMESPACE "AtumLayerGroupNormOptions"

FAtumLayerGroupNormOptions::FAtumLayerGroupNormOptions() noexcept :
NumGroups(0LL),
NumChannels(0LL),
Eps(1E-5),
bAffine(true)
{
}

#undef LOCTEXT_NAMESPACE
