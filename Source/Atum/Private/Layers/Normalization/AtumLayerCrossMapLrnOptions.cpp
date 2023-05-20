﻿// © 2023 Kaya Adrian.

#include "Layers/Normalization/AtumLayerCrossMapLrnOptions.h"


#define LOCTEXT_NAMESPACE "AtumLayerCrossMapLrnOptions"

FAtumLayerCrossMapLrnOptions::FAtumLayerCrossMapLrnOptions() noexcept : Size(0LL), Alpha(1E-4), Beta(0.75), K(1LL)
{
}

#undef LOCTEXT_NAMESPACE
