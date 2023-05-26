// © 2023 Kaya Adrian.

#pragma once

#include "UObject/Interface.h"

#include <memory>
#include <vector>

#include "IAtumLayer.generated.h"

class IAtumTensor;
struct FAtumLayerBaseOptions;

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
namespace torch::nn
{
	class Module;
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning


#define LOCTEXT_NAMESPACE "IAtumLayer"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "ATUM Layer")
class UAtumLayer : public UInterface
{
	GENERATED_BODY()
};

class ATUM_API IAtumLayer
{
	GENERATED_BODY()
	
protected:
	bool bInitialized;
	uint64 DimensionCount;
	std::vector<int64> ValidInputSizes;
	
public:
	UE_NODISCARD_CTOR
	IAtumLayer() noexcept;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool InitializeData(bool bRetry = true);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool Forward(const TScriptInterface<IAtumTensor>& Input, TScriptInterface<IAtumTensor>& Output);
	
	FORCEINLINE bool operator()(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) noexcept
	{ return Execute_Forward(_getUObject(), Input, Output); }
	
	UE_NODISCARD
	virtual const FAtumLayerBaseOptions* GetBaseOptions() const noexcept;
	
	UE_NODISCARD
	virtual FAtumLayerBaseOptions* GetBaseOptions() noexcept;
	
	UE_NODISCARD
	virtual std::shared_ptr<torch::nn::Module> GetSharedModule() const noexcept;
	
private:
	bool InitializeData_Implementation(bool bRetry = true) noexcept;
	
	bool Forward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) noexcept;
	
protected:
	UE_NODISCARD
	bool AreInputSizesValid(int32 InputSizeCount) const noexcept;
	
	UE_NODISCARD
	bool AreInputSizesValid(const TArray<int64>& InputSizes, int64 ExpectedChannels) const noexcept;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool OnInitializeData(bool bRetry = true);
	virtual bool OnInitializeData_Implementation(bool bRetry = true) noexcept;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool OnForward(const TScriptInterface<IAtumTensor>& Input, TScriptInterface<IAtumTensor>& Output);
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	);
	
public:
	UE_NODISCARD
	FORCEINLINE bool IsInitialized() const noexcept { return bInitialized; }
	
	UE_NODISCARD
	FORCEINLINE uint64 GetDimensionCount() const noexcept { return DimensionCount; }
	
	UE_NODISCARD
	FORCEINLINE const std::vector<int64>& GetValidInputSizes() const noexcept { return ValidInputSizes; }
};

#undef LOCTEXT_NAMESPACE
