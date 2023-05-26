// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerBaseOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerBaseOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Layer Base Options")
struct ATUM_API FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	FString LayerName;
	
	UE_NODISCARD_CTOR
	FAtumLayerBaseOptions() noexcept;
};

#undef LOCTEXT_NAMESPACE
