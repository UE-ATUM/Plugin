// © 2023 Kaya Adrian.

#pragma once

#include "Serializable/IAtumSerializable.h"

#include <vector>

#include "IAtumLayer.generated.h"

class IAtumTensor;
enum class EAtumTensorDeviceType : uint8;
struct FAtumLayerBaseOptions;

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
namespace torch::nn
{
	class Module;
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning


#define LOCTEXT_NAMESPACE "IAtumLayer"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "ATUM Layer")
class UAtumLayer : public UAtumSerializable
{
	GENERATED_BODY()
};

class ATUM_API IAtumLayer : public IAtumSerializable
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
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	void CloneData(TScriptInterface<IAtumLayer>& OutClone, UObject* Outer = nullptr) const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool SetGradientToZero(bool bSetToNone = false);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	void GetParameters(
		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) const UClass* Class,
		TMap<FString, TScriptInterface<IAtumTensor>>& OutValues
	) const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	void SetDeviceType(EAtumTensorDeviceType Value);
	
	UE_NODISCARD
	virtual const torch::nn::Module* GetBaseModule() const noexcept;
	
	UE_NODISCARD
	FORCEINLINE torch::nn::Module* GetBaseModule() noexcept
	{ return const_cast<torch::nn::Module*>(std::as_const(*this).GetBaseModule()); }
	
	UE_NODISCARD
	virtual const FAtumLayerBaseOptions* GetBaseLayerOptions() const noexcept;
	
	UE_NODISCARD
	virtual FAtumLayerBaseOptions* GetBaseLayerOptions() noexcept;
	
	FORCEINLINE bool operator()(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) noexcept
	{ return Execute_Forward(_getUObject(), Input, Output); }
	
protected:
	UE_NODISCARD
	bool AreInputSizesValid(int32 InputSizeCount) const noexcept;
	
	UE_NODISCARD
	bool AreInputSizesValid(const TArray<int64>& InputSizes, int64 ExpectedChannels) const noexcept;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool OnInitializeData(bool bRetry = true);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool OnForward(const TScriptInterface<IAtumTensor>& Input, TScriptInterface<IAtumTensor>& Output);
	
	virtual bool OnInitializeData_Implementation(bool bRetry = true);
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	);
	
	virtual void CloneData_Implementation(
		TScriptInterface<IAtumLayer>& OutClone,
		UObject* Outer = nullptr
	) const noexcept;
	
	virtual bool SetGradientToZero_Implementation(bool bSetToNone = false) noexcept;
	
	virtual void GetParameters_Implementation(
		const UClass* Class,
		TMap<FString, TScriptInterface<IAtumTensor>>& OutValues
	) const noexcept;
	
	virtual void SetDeviceType_Implementation(EAtumTensorDeviceType Value) noexcept;
	
	virtual void SetBaseModule(const torch::nn::Module* Value) noexcept;
	
	virtual bool SaveToFile_Implementation(const FString& RelativePath) const override;
	
	virtual bool LoadFromFile_Implementation(const FString& RelativePath) override;
	
private:
	bool InitializeData_Implementation(bool bRetry = true) noexcept;
	
	bool Forward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) noexcept;
	
public:
	UE_NODISCARD
	FORCEINLINE bool IsInitialized() const noexcept { return bInitialized; }
	
	UE_NODISCARD
	FORCEINLINE uint64 GetDimensionCount() const noexcept { return DimensionCount; }
	
	UE_NODISCARD
	FORCEINLINE const std::vector<int64>& GetValidInputSizes() const noexcept { return ValidInputSizes; }
};

#undef LOCTEXT_NAMESPACE
