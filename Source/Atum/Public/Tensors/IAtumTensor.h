﻿// © 2023 Kaya Adrian.

#pragma once

#include "AtumTensorDeviceType.h"
#include "AtumTensorRetainGraphMode.h"
#include "AtumTensorScalarType.h"
#include "Serializable/IAtumSerializable.h"

TORCH_INCLUDES_START
#include <torch/csrc/autograd/generated/variable_factories.h>
TORCH_INCLUDES_END

#include "IAtumTensor.generated.h"


#define LOCTEXT_NAMESPACE "IAtumTensor"

UINTERFACE(MinimalAPI, NotBlueprintable, BlueprintType, DisplayName = "ATUM Tensor")
class UAtumTensor : public UAtumSerializable
{
	GENERATED_BODY()
};

class ATUM_API IAtumTensor : public IAtumSerializable
{
	GENERATED_BODY()
	
protected:
	static EAtumTensorDeviceType DefaultDeviceType;
	TUniquePtr<at::Tensor> Data;
	EAtumTensorScalarType ScalarType;
	
public:
	UE_NODISCARD_CTOR
	IAtumTensor() noexcept;
	
	UE_NODISCARD
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual bool IsDefined() const noexcept;
	
	UE_NODISCARD
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor", DisplayName = "Is Broadcastable With")
	virtual bool IsBroadcastableWith(const TScriptInterface<IAtumTensor>& BroadcastTensor) const noexcept;
	
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor", DisplayName = "Broadcast To")
	virtual bool BroadcastTo(const TScriptInterface<IAtumTensor>& BroadcastTensor) noexcept;
	
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual void Detach(TScriptInterface<IAtumTensor>& OutDetachedTensor) const noexcept;
	
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual void GetGradient(TScriptInterface<IAtumTensor>& OutGradient) const noexcept;
	
	UE_NODISCARD
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual bool DoesRequireGradient() const noexcept;
	
	virtual IAtumTensor* SetRequireGradient(bool bValue) noexcept;
	
	UE_NODISCARD
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual void GetSizes(TArray<int64>& OutSizes) const noexcept;
	
	UE_NODISCARD
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual EAtumTensorDeviceType GetDeviceType() const noexcept;
	
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual void SetDeviceType(EAtumTensorDeviceType Value) noexcept;
	
	UE_NODISCARD
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual EAtumTensorScalarType GetScalarType() const noexcept;
	
	UE_NODISCARD
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual int64 GetElementCount() const noexcept;
	
	UE_NODISCARD
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual int64 GetElementSize() const noexcept;
	
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual void GetSerializedValues(TArray<uint8>& OutValues, TArray<int64>& OutSizes) const noexcept;
	
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual void SetSerializedValues(const TArray<uint8>& Values, const TArray<int64>& Sizes) noexcept;
	
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual void CloneData(TScriptInterface<IAtumTensor>& OutClone, UObject* Outer = nullptr) const noexcept;
	
	UFUNCTION(BlueprintPure = "false", Category = "ATUM|Tensor", meta = (
		AdvancedDisplay = "Gradient,Inputs,RetainGraphMode,bCreateGraph",
		AutoCreateRefTerm = "Gradient,Inputs"
	))
	virtual bool Backward(
		const TScriptInterface<IAtumTensor>& Gradient,
		const TArray<TScriptInterface<IAtumTensor>>& Inputs,
		EAtumTensorRetainGraphMode RetainGraphMode = EAtumTensorRetainGraphMode::IfCreated,
		bool bCreateGraph = false
	) const noexcept;
	
	UE_NODISCARD
	FORCEINLINE c10::DeviceType GetTorchDeviceType() const noexcept { return AtumEnums::Cast(GetDeviceType()); }
	
	UE_NODISCARD
	FORCEINLINE c10::ScalarType GetTorchScalarType() const noexcept
	{ return Data ? Data->scalar_type() : AtumEnums::Cast(GetScalarType()); }
	
	UE_NODISCARD
	TScriptInterface<IAtumTensor> Add(
		const TScriptInterface<IAtumTensor>& Other,
		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) const UClass* Class = nullptr
	) const noexcept;
	
	UE_NODISCARD
	FORCEINLINE TScriptInterface<IAtumTensor> operator+(const TScriptInterface<IAtumTensor>& Other) const noexcept
	{ return Add(Other); }
	
	UE_NODISCARD
	explicit operator FString() const noexcept;
	
	UE_NODISCARD
	FORCEINLINE FString ToString() const noexcept { return static_cast<FString>(*this); }
	
	UE_NODISCARD
	FORCEINLINE at::Tensor operator[](const int64 Index) { return (*Data)[Index]; }
	
	UE_NODISCARD
	FORCEINLINE at::Tensor operator[](const c10::Scalar& Scalar) { return (*Data)[Scalar]; }
	
	UE_NODISCARD
	FORCEINLINE at::Tensor operator[](const at::Tensor& Tensor) { return (*Data)[Tensor]; }
	
	UE_NODISCARD
	FORCEINLINE at::Tensor operator[](const IAtumTensor& Tensor) { return (*Data)[*Tensor.Data]; }
	
	template <typename T>
	void GetValues(TArray<T>& OutValues, TArray<int64>& OutSizes) const noexcept;
	
	template <typename T>
	FORCEINLINE void SetValues(T* const Values, const TArray<int64>& Sizes) noexcept
	{
		try
		{
			SetData(torch::from_blob(
				Values,
				c10::IntArrayRef(Sizes.GetData(), Sizes.Num()),
				GetTorchScalarType()
			).to(GetTorchDeviceType()));
		}
		catch (const std::exception& Exception)
		{
			UE_LOG(LogTemp, Fatal, TEXT("%hs"), Exception.what())
		}
	}
	
protected:
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor", DisplayName = "Set Require Gradient")
	virtual void K2_SetRequireGradient(bool bValue, TScriptInterface<IAtumTensor>& OutSelf) noexcept;
	
	virtual bool SaveToFile_Implementation(const FString& RelativePath) const override;
	
	virtual bool LoadFromFile_Implementation(const FString& RelativePath) override;
	
private:
	UE_NODISCARD
	FORCEINLINE void* GetUncastedValues(const c10::ScalarType Type) const noexcept
	{ return IsDefined() ? Data->to(Type).data_ptr() : nullptr; }
	
	UE_NODISCARD
	FORCEINLINE void* GetUncastedValues(const EAtumTensorScalarType Type) const noexcept
	{ return GetUncastedValues(AtumEnums::Cast(Type)); }

	friend std::ostream& operator<<(std::ostream& OutStream, const IAtumTensor& AtumTensor) noexcept;
	friend std::ostream& operator<<(std::ostream& OutStream, const TScriptInterface<IAtumTensor>& AtumTensor) noexcept;

public:
	UE_NODISCARD
	static FORCEINLINE EAtumTensorDeviceType GetDefaultDeviceType() noexcept { return DefaultDeviceType; }
	
	static FORCEINLINE void SetDefaultDeviceType(const EAtumTensorDeviceType Value) noexcept
	{ DefaultDeviceType = Value; }
	
	UE_NODISCARD
	FORCEINLINE const at::Tensor* GetData() const noexcept { return Data.Get(); }
	
	UE_NODISCARD
	FORCEINLINE const at::Tensor& GetDataChecked() const { return *GetData(); }
	
	FORCEINLINE void SetData(const at::Tensor& Value) noexcept
	{
		Data.Reset(Value.defined() ?
			new at::Tensor(Value.to(GetTorchDeviceType()).to(GetTorchScalarType())) :
			nullptr
		);
	}
};


template <typename T>
class TAtumTensor
{
protected:
	mutable TArray<T> InternalValues = TArray<T>();
	
	void SetInternalValues(IAtumTensor& AtumTensor, const TArray<T>& Values, const TArray<int64>& Sizes) noexcept;

public:
	UE_NODISCARD
	FORCEINLINE const TArray<T>& GetInternalValues() const noexcept { return InternalValues; }
	
	FORCEINLINE void GetInternalValues(TArray<T>& OutValues) noexcept { OutValues = InternalValues; }
};


template <typename T>
void IAtumTensor::GetValues(TArray<T>& OutValues, TArray<int64>& OutSizes) const noexcept
{
	if (!IsDefined())
		return;
	
	OutValues.Append(static_cast<T*>(GetUncastedValues(GetScalarType())), Data->numel());
	
	const c10::IntArrayRef DataSizes = Data->sizes();
	OutSizes = TArray(DataSizes.data(), DataSizes.size());
}

template <typename T>
void TAtumTensor<T>::SetInternalValues(
	IAtumTensor& AtumTensor,
	const TArray<T>& Values,
	const TArray<int64>& Sizes
) noexcept
{
	InternalValues = Values;
	AtumTensor.SetValues<T>(InternalValues.GetData(), Sizes);
}

#undef LOCTEXT_NAMESPACE
