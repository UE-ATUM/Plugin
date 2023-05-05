// © 2023 Kaya Adrian.

#pragma once

#include "AtumScalarType.h"
#include "UObject/Interface.h"

#include "IAtumTensor.generated.h"


UINTERFACE(MinimalAPI, NotBlueprintable, BlueprintType, DisplayName = "ATUM Tensor")
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
	UFUNCTION(BlueprintPure, Category = "ATUM|Tensor")
	virtual void GetSizes(TArray<int64>& OutSizes) const noexcept;
	
	UE_NODISCARD
	UFUNCTION(BlueprintPure, Category = "ATUM|Tensor")
	virtual EAtumScalarType GetScalarType() const noexcept;
	
	UE_NODISCARD
	UFUNCTION(BlueprintPure, Category = "ATUM|Tensor")
	virtual int64 GetElementCount() const noexcept;
	
	UE_NODISCARD
	UFUNCTION(BlueprintPure, Category = "ATUM|Tensor")
	virtual int64 GetElementSize() const noexcept;
	
	UFUNCTION(BlueprintPure, Category = "ATUM|Tensor")
	virtual void GetSerializedValues(TArray<uint8>& OutValues, TArray<int64>& OutSizes) const noexcept;
	
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual void SetSerializedValues(const TArray<uint8>& Values, const TArray<int64>& Sizes) noexcept;

	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual void CloneData(TScriptInterface<IAtumTensor>& OutClone, UObject* Outer = nullptr) const noexcept;
	
	UE_NODISCARD
	FORCEINLINE c10::ScalarType GetTorchScalarType() const noexcept
	{ return Data ? Data->scalar_type() : AtumEnums::Cast(GetScalarType()); }
	
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
	
	template <typename T>
	void GetValues(TArray<T>& OutValues, TArray<int64>& OutSizes) const noexcept;
	
	template <typename T>
	FORCEINLINE void SetValues(T* const Values, const TArray<int64>& Sizes) noexcept
	{ SetData(torch::from_blob(
		Values,
		c10::IntArrayRef(Sizes.GetData(), Sizes.Num()),
		GetTorchScalarType()
	)); }

private:
	UE_NODISCARD
	FORCEINLINE void* GetUncastedValues(const c10::ScalarType Type) const noexcept
	{ return Data ? Data->to(Type).data_ptr() : nullptr; }
	
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
	{ Data.Reset(new torch::Tensor(Value.to(GetTorchScalarType()))); }
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
	if (Data == nullptr)
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
