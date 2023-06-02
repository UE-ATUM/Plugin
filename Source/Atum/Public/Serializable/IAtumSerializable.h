// © 2023 Kaya Adrian.

#pragma once

#include "UObject/Interface.h"

#include "IAtumSerializable.generated.h"


#define LOCTEXT_NAMESPACE "IAtumSerializable"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "ATUM Serializable")
class UAtumSerializable : public UInterface
{
	GENERATED_BODY()
};

class ATUM_API IAtumSerializable
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintPure = "false", Category = "ATUM|Serializable")
	bool SaveToFile(const FString& RelativePath) const;
	
protected:
	virtual bool SaveToFile_Implementation([[maybe_unused]] const FString& RelativePath) const noexcept
	PURE_VIRTUAL(IAtumSerializable::SaveToFile, return false;);
};

#undef LOCTEXT_NAMESPACE
