// © 2023 Kaya Adrian.

#pragma once

#include "GameFramework/Actor.h"

#include "AtumEnvironment.generated.h"

class IAtumEnvironmentStateFinder;


#define LOCTEXT_NAMESPACE "AtumEnvironment"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnvironmentResetState, const AAtumEnvironment*, Environment);


UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Environment")
class AAtumEnvironment : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TScriptInterface<IAtumEnvironmentStateFinder> StateFinder;
	
public:
	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, meta = (AllowPrivateAccess))
	FOnEnvironmentResetState OnEnvironmentResetState;
	
	UFUNCTION(BlueprintCallable, Category = "ATUM|Environment")
	UObject* ResetState() const;
	
	UE_NODISCARD
	UFUNCTION(BlueprintPure = "false", Category = "ATUM|Environment")
	UObject* GetState() const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Environment")
	bool ExecuteAction(int64 ActionIndex);
	
protected:
	virtual bool ExecuteAction_Implementation([[maybe_unused]] const int64 ActionIndex)
	PURE_VIRTUAL(AAtumEnvironment::ExecuteAction, return false;);
	
public:
	UE_NODISCARD
	FORCEINLINE const TScriptInterface<IAtumEnvironmentStateFinder>& GetStateFinder() const noexcept
	{ return StateFinder; }
	
	UE_NODISCARD
	FORCEINLINE TScriptInterface<IAtumEnvironmentStateFinder>& GetStateFinder() noexcept { return StateFinder; }
};

#undef LOCTEXT_NAMESPACE
