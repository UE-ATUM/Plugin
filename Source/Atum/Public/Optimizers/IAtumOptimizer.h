// © 2023 Kaya Adrian.

#pragma once

#include "UObject/Interface.h"

#include "IAtumOptimizer.generated.h"

class IAtumTensor;
struct FAtumOptimizerBaseOptions;

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
namespace torch::optim
{
	class Optimizer;
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning


#define LOCTEXT_NAMESPACE "IAtumOptimizer"

struct FOptimizerParametersDeleter
{
	void operator()(torch::optim::Optimizer* Optimizer) const noexcept;
};


UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "ATUM Optimizer")
class UAtumOptimizer : public UInterface
{
	GENERATED_BODY()
};

class ATUM_API IAtumOptimizer
{
	GENERATED_BODY()
	
protected:
	bool bInitialized;
	TSharedPtr<torch::optim::Optimizer> Optimizer;
	
public:
	UE_NODISCARD_CTOR
	IAtumOptimizer() noexcept;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Optimizer")
	bool InitializeData(bool bRetry = true);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "ATUM|Optimizer")
	void GetParameters(TArray<TScriptInterface<IAtumTensor>>& OutParameters) const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Optimizer")
	void SetParameters(const TArray<TScriptInterface<IAtumTensor>>& Parameters);
	
	UE_NODISCARD
	virtual const FAtumOptimizerBaseOptions* GetBaseOptimizerOptions() const noexcept;
	
	UE_NODISCARD
	virtual FAtumOptimizerBaseOptions* GetBaseOptimizerOptions() noexcept;
	
private:
	bool InitializeData_Implementation(bool bRetry = true) noexcept;
	
protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Optimizer")
	bool OnInitializeData(bool bRetry = true);
	
	virtual bool OnInitializeData_Implementation(bool bRetry = true);
	
	virtual void GetParameters_Implementation(TArray<TScriptInterface<IAtumTensor>>& OutParameters) const noexcept;
	virtual void SetParameters_Implementation(const TArray<TScriptInterface<IAtumTensor>>& Parameters) noexcept;
	
public:
	UE_NODISCARD
	FORCEINLINE bool IsInitialized() const noexcept { return bInitialized; }
	
	UE_NODISCARD
	FORCEINLINE TSharedPtr<const torch::optim::Optimizer> GetOptimizer() const noexcept { return Optimizer; }
	
	UE_NODISCARD
	FORCEINLINE TSharedPtr<torch::optim::Optimizer> GetOptimizer() noexcept { return Optimizer; }
};

#undef LOCTEXT_NAMESPACE
