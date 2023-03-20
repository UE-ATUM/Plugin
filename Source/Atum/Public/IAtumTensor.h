// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AtumScalarType.h"
#include "UObject/Interface.h"

#include "IAtumTensor.generated.h"


UINTERFACE(Blueprintable, BlueprintType, DisplayName = "ATUM Tensor")
class ATUM_API UAtumTensor : public UInterface
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

	template <typename T>
	void GetValues(TArray<T>& OutValues) const noexcept;

	template <typename T>
	FORCEINLINE void SetValues(T* const Values, const TArray<int64>& Sizes) noexcept
	{ SetData(torch::from_blob(Values, c10::IntArrayRef(Sizes.GetData(), Sizes.Num()))); }

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

	// TODO
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TestSetup(const TArray<int64>& Sizes);
	
	virtual void TestSetup_Implementation(const TArray<int64>& Sizes)
	{ SetData(10.0f * torch::rand(c10::IntArrayRef(Sizes.GetData(), Sizes.Num()))); }

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
	
	FORCEINLINE void SetData(torch::Tensor* const Value)
	{ Data.Reset(Value); }
	
	FORCEINLINE void SetData(const torch::Tensor& Value)
	{ Data.Reset(new torch::Tensor(Value.toType(AtumEnums::Cast(Execute_GetScalarType(_getUObject()))))); }
};


template <typename T>
class TAtumTensorInternal
{
protected:
	mutable TArray<T> InternalValues = TArray<T>();

	UE_NODISCARD_CTOR
	FORCEINLINE TAtumTensorInternal() noexcept {}

	void SetValues_Internal(IAtumTensor& AtumTensor, const TArray<T>& Values, const TArray<int64>& Sizes) noexcept;

public:
	UE_NODISCARD
	FORCEINLINE const TArray<T>& GetInternalValues() const noexcept { return InternalValues; }
	
	FORCEINLINE void GetInternalValues(TArray<T>& OutValues) noexcept { OutValues = InternalValues; }
};


template <typename T>
void IAtumTensor::GetValues(TArray<T>& OutValues) const noexcept
{
	if (Data)
	{
		OutValues.Append(static_cast<T*>(GetUncastedValues(Execute_GetScalarType(_getUObject()))), Data->numel());
	}
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
