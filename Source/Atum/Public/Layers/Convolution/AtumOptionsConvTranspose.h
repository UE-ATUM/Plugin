// © 2023 Kaya Adrian.

#pragma once

#include "AtumConvPaddingMode.h"

#include "AtumOptionsConvTranspose.generated.h"

class UAtumLayerConvTranspose;


USTRUCT(BlueprintType, DisplayName = "ATUM Conv Transpose Options")
struct ATUM_API FAtumOptionsConvTranspose
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	int64 InChannels;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	int64 OutChannels;

	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	TArray<int64> KernelSize;
	
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	TArray<int64> Stride;

	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	TArray<int64> Padding;

	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	TArray<int64> OutputPadding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	int64 Groups;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	bool bBias;

	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	TArray<int64> Dilation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	EAtumConvPaddingMode PaddingMode;

protected:
	UE_NODISCARD_CTOR
	FAtumOptionsConvTranspose() noexcept;

public:
	UE_NODISCARD_CTOR
	explicit FAtumOptionsConvTranspose(uint64 Dimensions) noexcept;

	UE_NODISCARD
	explicit operator torch::nn::ConvTranspose1dOptions() const noexcept;

	UE_NODISCARD
	explicit operator torch::nn::ConvTranspose2dOptions() const noexcept;
	
	UE_NODISCARD
	explicit operator torch::nn::ConvTranspose3dOptions() const noexcept;

	friend UAtumLayerConvTranspose;
	friend UScriptStruct;
};
