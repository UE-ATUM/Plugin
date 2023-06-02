// © 2023 Kaya Adrian.

#pragma once

#include "UObject/Interface.h"

#include "IAtumEnvironmentStateFinder.generated.h"

class AAtumEnvironment;


#define LOCTEXT_NAMESPACE "IAtumEnvironmentStateFinder"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "ATUM Environment State Finder")
class UAtumEnvironmentStateFinder : public UInterface
{
	GENERATED_BODY()
};

class ATUM_API IAtumEnvironmentStateFinder
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Environment")
	bool FindStateIn(const AAtumEnvironment* Environment);
	
protected:
	virtual bool FindStateIn_Implementation([[maybe_unused]] const AAtumEnvironment* const Environment) noexcept
	PURE_VIRTUAL(IAtumEnvironmentStateFinder::FindStateIn, return false;);
};

#undef LOCTEXT_NAMESPACE
