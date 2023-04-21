// © 2023 Kaya Adrian.

#pragma once

#include "Tensors/IAtumTensor.h"
#include "UObject/Interface.h"

#include "IAtumLayer.generated.h"


UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "ATUM Layer")
class UAtumLayer : public UInterface
{
	GENERATED_BODY()
};

class ATUM_API IAtumLayer
{
	GENERATED_BODY()
	
	bool bInitialized = false;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool InitializeData(bool bRetry = false);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool Forward(const TScriptInterface<IAtumTensor>& Input, TScriptInterface<IAtumTensor>& Output);
	
	FORCEINLINE bool operator()(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) noexcept
	{ return Forward(Input, Output); }

private:
	bool InitializeData_Implementation(bool bRetry = false) noexcept;
	
	bool Forward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) noexcept;

protected:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool OnInitializeData(bool bRetry = false);
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool OnForward(const TScriptInterface<IAtumTensor>& Input, TScriptInterface<IAtumTensor>& Output);
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) noexcept;
	
public:
	FORCEINLINE bool IsInitialized() const { return bInitialized; }
};


template <typename T>
requires std::is_base_of_v<torch::nn::Module, T>
class TAtumLayer
{
protected:
	mutable TUniquePtr<T> Module = nullptr;

public:
	UE_NODISCARD
	FORCEINLINE const T* GetModule() const noexcept { return Module.Get(); }
	
	UE_NODISCARD
	FORCEINLINE T* GetModule() noexcept { return Module.Get(); }

	UE_NODISCARD
	FORCEINLINE const T& GetModuleChecked() const { return *GetModule(); }

	UE_NODISCARD
	FORCEINLINE T& GetModuleChecked() { return *GetModule(); }
};
