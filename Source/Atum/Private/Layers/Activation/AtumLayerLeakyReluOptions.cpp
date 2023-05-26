// © 2023 Kaya Adrian.

#include "Layers/Activation/AtumLayerLeakyReluOptions.h"


#define LOCTEXT_NAMESPACE "AtumLayerLeakyReluOptions"

FAtumLayerLeakyReluOptions::FAtumLayerLeakyReluOptions() noexcept : NegativeSlope(1E-2), bInplace(false)
{
}

#undef LOCTEXT_NAMESPACE
