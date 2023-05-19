// © 2023 Kaya Adrian.

#pragma once

#include "IAtumLayerOptions.generated.h"


USTRUCT(BlueprintType, DisplayName = "ATUM Layer Options")
struct ATUM_API FAtumLayerOptions
{
	GENERATED_BODY()
	
protected:
	UE_NODISCARD_CTOR
	FAtumLayerOptions() noexcept;
	
	friend UScriptStruct;
};
