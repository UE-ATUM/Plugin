// © 2023 Kaya Adrian.

#pragma once

#include "Serializable/IAtumSerializable.h"

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

DECLARE_DYNAMIC_DELEGATE_OneParam(FAtumOptimizerLossClosure, const TScriptInterface<IAtumTensor>&, Loss);


struct FOptimizerParametersDeleter
{
	void operator()(torch::optim::Optimizer* Optimizer) const noexcept;
};


UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "ATUM Optimizer")
class UAtumOptimizer : public UAtumSerializable
{
	GENERATED_BODY()
};

class ATUM_API IAtumOptimizer : public IAtumSerializable
{
	GENERATED_BODY()
	
protected:
	bool bInitialized;
	TSharedPtr<torch::optim::Optimizer> Optimizer;
	
public:
	UE_NODISCARD_CTOR
	IAtumOptimizer() noexcept;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Optimizer", meta = (
		AutoCreateRefTerm = "Parameters"
	))
	bool InitializeData(bool bRetry = true);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Optimizer")
	void GetParameters(TArray<TScriptInterface<IAtumTensor>>& OutParameters) const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Optimizer")
	void SetParameters(const TArray<TScriptInterface<IAtumTensor>>& Parameters);
	
	FORCEINLINE void Step(
		const UClass* Class,
		TScriptInterface<IAtumTensor>& OutLoss,
		const FAtumOptimizerLossClosure& LossClosure = FAtumOptimizerLossClosure()
	) noexcept
	{ Execute_K2_Step(_getUObject(), Class, OutLoss, LossClosure); }
	
	UE_NODISCARD
	virtual const FAtumOptimizerBaseOptions* GetBaseOptimizerOptions() const noexcept;
	
	UE_NODISCARD
	virtual FAtumOptimizerBaseOptions* GetBaseOptimizerOptions() noexcept;
	
protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Optimizer", meta = (
		AutoCreateRefTerm = "Parameters"
	))
	bool OnInitializeData(bool bRetry = true);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Optimizer", DisplayName = "Step", meta = (
		AdvancedDisplay = "2",
		AutoCreateRefTerm = "LossClosure"
	))
	void K2_Step(
		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) const UClass* Class,
		TScriptInterface<IAtumTensor>& OutLoss,
		const FAtumOptimizerLossClosure& LossClosure
	);
	
	virtual bool OnInitializeData_Implementation(bool bRetry = true);
	
	virtual void K2_Step_Implementation(
		const UClass* Class,
		TScriptInterface<IAtumTensor>& OutLoss,
		const FAtumOptimizerLossClosure& LossClosure
	) noexcept;
	
	virtual void GetParameters_Implementation(TArray<TScriptInterface<IAtumTensor>>& OutParameters) const noexcept;
	
	virtual void SetParameters_Implementation(const TArray<TScriptInterface<IAtumTensor>>& Parameters) noexcept;
	
	virtual bool SaveToFile_Implementation(const FString& RelativePath) const override;
	
	virtual bool LoadFromFile_Implementation(const FString& RelativePath) override;
	
private:
	bool InitializeData_Implementation(bool bRetry = true) noexcept;
	
public:
	UE_NODISCARD
	FORCEINLINE bool IsInitialized() const noexcept { return bInitialized; }
	
	UE_NODISCARD
	FORCEINLINE TSharedPtr<const torch::optim::Optimizer> GetOptimizer() const noexcept { return Optimizer; }
	
	UE_NODISCARD
	FORCEINLINE TSharedPtr<torch::optim::Optimizer> GetOptimizer() noexcept { return Optimizer; }
};

#undef LOCTEXT_NAMESPACE
