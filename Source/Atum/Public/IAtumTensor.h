// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AtumScalarType.h"
#include "UObject/Interface.h"

#include "IAtumTensor.generated.h"


UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "ATUM Tensor")
class UAtumTensor : public UInterface
{
	GENERATED_BODY()
};

class ATUM_API IAtumTensor
{
	GENERATED_BODY()
	
protected:
	TUniquePtr<torch::Tensor> Data = nullptr;

public:
	UE_NODISCARD
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "ATUM|Tensor")
	EAtumScalarType GetScalarType() const;

	UE_NODISCARD
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "ATUM|Tensor")
	int64 GetElementCount() const;

	UE_NODISCARD
	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "ATUM|Tensor")
	int64 GetElementSize() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "ATUM|Tensor")
	void GetSerializedValues(TArray<uint8>& OutValues, TArray<int64>& OutSizes) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Tensor")
	void SetSerializedValues(const TArray<uint8>& Values, const TArray<int64>& Sizes);

	UE_NODISCARD
	FORCEINLINE c10::ScalarType GetTorchScalarType() const noexcept
	{ return Data ? Data->scalar_type() : AtumEnums::Cast(Execute_GetScalarType(_getUObject())); }

	template <typename T>
	void GetValues(TArray<T>& OutValues, TArray<int64>& OutSizes) const noexcept;

	template <typename T>
	FORCEINLINE void SetValues(T* const Values, const TArray<int64>& Sizes) noexcept
	{ SetData(torch::from_blob(
		Values,
		c10::IntArrayRef(Sizes.GetData(), Sizes.Num()),
		GetTorchScalarType()
	)); }

	UE_NODISCARD
	explicit operator FString() const noexcept;
	
	UE_NODISCARD
	FORCEINLINE FString ToString() const noexcept { return static_cast<FString>(*this); }

	UE_NODISCARD
	FORCEINLINE torch::Tensor operator[](const int64 Index) { return (*Data)[Index]; }
	
	UE_NODISCARD
	FORCEINLINE torch::Tensor operator[](const torch::Scalar& Scalar) { return (*Data)[Scalar]; }
	
	UE_NODISCARD
	FORCEINLINE torch::Tensor operator[](const torch::Tensor& Tensor) { return (*Data)[Tensor]; }
	
	UE_NODISCARD
	FORCEINLINE torch::Tensor operator[](const IAtumTensor& Tensor) { return (*Data)[*Tensor.Data]; }

protected:
	UE_NODISCARD
	virtual EAtumScalarType GetScalarType_Implementation() const noexcept;

	UE_NODISCARD
	virtual int64 GetElementCount_Implementation() const noexcept;

	UE_NODISCARD
	virtual int64 GetElementSize_Implementation() const noexcept;

	virtual void GetSerializedValues_Implementation(TArray<uint8>& OutValues, TArray<int64>& OutSizes) const noexcept;
	virtual void SetSerializedValues_Implementation(const TArray<uint8>& Values, const TArray<int64>& Sizes) noexcept;

private:
	UE_NODISCARD
	FORCEINLINE void* GetUncastedValues(const c10::ScalarType Type) const noexcept
	{ return Data ? Data->toType(Type).data_ptr() : nullptr; }
	
	UE_NODISCARD
	FORCEINLINE void* GetUncastedValues(const EAtumScalarType Type) const noexcept
	{ return GetUncastedValues(AtumEnums::Cast(Type)); }

	friend std::ostream& operator<<(std::ostream& OutStream, const IAtumTensor& AtumTensor) noexcept;
	friend std::ostream& operator<<(std::ostream& OutStream, const TScriptInterface<IAtumTensor>& AtumTensor) noexcept;

public:
	UE_NODISCARD
	FORCEINLINE const torch::Tensor* GetData() const noexcept { return Data.Get(); }
	
	UE_NODISCARD
	FORCEINLINE const torch::Tensor& GetDataChecked() const { return *GetData(); }
	
	FORCEINLINE void SetData(const torch::Tensor& Value) noexcept
	{ Data.Reset(new torch::Tensor(Value.toType(GetTorchScalarType()))); }
};


template <typename T>
class TAtumTensorInternal
{
protected:
	mutable TArray<T> InternalValues = TArray<T>();
	
	void SetValues_Internal(IAtumTensor& AtumTensor, const TArray<T>& Values, const TArray<int64>& Sizes) noexcept;

public:
	UE_NODISCARD
	FORCEINLINE const TArray<T>& GetInternalValues() const noexcept { return InternalValues; }
	
	FORCEINLINE void GetInternalValues(TArray<T>& OutValues) noexcept { OutValues = InternalValues; }
};


template <typename T>
void IAtumTensor::GetValues(TArray<T>& OutValues, TArray<int64>& OutSizes) const noexcept
{
	if (Data == nullptr)
		return;
	
	OutValues.Append(static_cast<T*>(GetUncastedValues(Execute_GetScalarType(_getUObject()))), Data->numel());

	const c10::IntArrayRef DataSizes = Data->sizes();
	OutSizes = TArray(DataSizes.data(), DataSizes.size());
}

template <typename T>
void TAtumTensorInternal<T>::SetValues_Internal(
	IAtumTensor& AtumTensor,
	const TArray<T>& Values,
	const TArray<int64>& Sizes
) noexcept
{
	InternalValues = Values;
	AtumTensor.SetValues<T>(InternalValues.GetData(), Sizes);
}
