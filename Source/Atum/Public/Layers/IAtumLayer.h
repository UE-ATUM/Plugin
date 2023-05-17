// © 2023 Kaya Adrian.

#pragma once

#include "Tensors/IAtumTensor.h"
#include "UObject/Interface.h"

#include "IAtumLayer.generated.h"

// ReSharper disable once CppUE4CodingStandardNamingViolationWarning
namespace torch::nn
{
	// ReSharper disable once CppUE4CodingStandardNamingViolationWarning
	class Module;
}


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
	bool InitializeData(bool bRetry = false);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool Forward(const TScriptInterface<IAtumTensor>& Input, TScriptInterface<IAtumTensor>& Output);
	
	FORCEINLINE bool operator()(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) noexcept
	{ return Execute_Forward(_getUObject(), Input, Output); }
	
	UE_NODISCARD
	virtual std::shared_ptr<torch::nn::Module> GetSharedModule() const noexcept { return nullptr; }
	
private:
	bool InitializeData_Implementation(bool bRetry = false) noexcept;
	
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
	bool OnInitializeData(bool bRetry = false);
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept;

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


USTRUCT(BlueprintType, DisplayName = "ATUM Layer Options")
struct ATUM_API FAtumLayerOptions
{
	GENERATED_BODY()

protected:
	UE_NODISCARD_CTOR
	FAtumLayerOptions() noexcept = default;

	friend UScriptStruct;
};


#define GENERATED_ATUM_LAYER(ModuleClass) \
protected: \
	ModuleClass Module = nullptr; \
	\
public: \
	UE_NODISCARD \
	virtual std::shared_ptr<torch::nn::Module> GetSharedModule() const noexcept override { return Module.ptr(); } \
	\
	UE_NODISCARD \
	FORCEINLINE const ModuleClass& GetModule() const noexcept { return Module; } \
	\
	UE_NODISCARD \
	FORCEINLINE ModuleClass& GetModule() noexcept { return Module; } \
	\
private: \
