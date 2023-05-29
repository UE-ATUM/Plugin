// © 2023 Kaya Adrian.

#pragma once

#include "Layers/IAtumLayer.h"

#include "IAtumLayerBaseConvolution.generated.h"


#define LOCTEXT_NAMESPACE "IAtumLayerBaseConvolution"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "ATUM Convolution Layer Base")
class UAtumLayerBaseConvolution : public UAtumLayer
{
	GENERATED_BODY()
};

class ATUM_API IAtumLayerBaseConvolution : public IAtumLayer
{
	GENERATED_BODY()
	
protected:
	UE_NODISCARD
	static bool AreChannelsDivisibleByGroups(int64 InChannels, int64 OutChannels, int64 Groups) noexcept;
	
	UE_NODISCARD
	bool AreSizesPositive(const TArray<int64>& Sizes, const FString& Name, bool bAllowZero = false) const noexcept;
};

#undef LOCTEXT_NAMESPACE
