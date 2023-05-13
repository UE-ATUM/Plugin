// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerGroupNormOptions.h"


FAtumLayerGroupNormOptions::FAtumLayerGroupNormOptions() noexcept :
NumGroups(0),
NumChannels(0),
Eps(1e-5),
bAffine(true)
{
}
