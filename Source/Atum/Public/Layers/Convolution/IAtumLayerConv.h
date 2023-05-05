// © 2023 Kaya Adrian.

#pragma once

#include "Layers/IAtumLayer.h"

#include "IAtumLayerConv.generated.h"


UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "ATUM Conv Layer Interface")
class UAtumLayerConv : public UAtumLayer
{
	GENERATED_BODY()
};

class ATUM_API IAtumLayerConv : public IAtumLayer
{
	GENERATED_BODY()

protected:
	uint64 DimensionCount;
	
public:
	UE_NODISCARD_CTOR
	IAtumLayerConv() noexcept;

protected:
	UE_NODISCARD
	bool AreInputSizesValid(int64 SizeCount, int64 GivenChannels, int64 ExpectedChannels) const noexcept;

public:
	UE_NODISCARD
	FORCEINLINE uint64 GetDimensionCount() const noexcept { return DimensionCount; }
};
