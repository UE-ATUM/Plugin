// © 2023 Kaya Adrian.

#pragma once

#include "ClassViewerFilter.h"


#define LOCTEXT_NAMESPACE "AtumNeuralNetworkClassFilter"

class FAtumNeuralNetworkClassFilter : public IClassViewerFilter
{
	TSet<const UClass*> AllowedClasses;
	EClassFlags BannedClassFlags;
	
public:
	UE_NODISCARD_CTOR
	FAtumNeuralNetworkClassFilter() noexcept;
	
	UE_NODISCARD
	virtual bool IsClassAllowed(
		const FClassViewerInitializationOptions& InInitOptions,
		const UClass* InClass,
		TSharedRef<FClassViewerFilterFuncs> InFilterFuncs
	) override;
	
	UE_NODISCARD
	virtual bool IsUnloadedClassAllowed(
		const FClassViewerInitializationOptions& InInitOptions,
		TSharedRef<const IUnloadedBlueprintData> InUnloadedClassData,
		TSharedRef<FClassViewerFilterFuncs> InFilterFuncs
	) override;
	
	virtual void GetFilterOptions(TArray<TSharedRef<FClassViewerFilterOption>>& OutFilterOptions) override;
	
	UE_NODISCARD
	FORCEINLINE const TSet<const UClass*>& GetAllowedClasses() const noexcept { return AllowedClasses; }
	
	UE_NODISCARD
	FORCEINLINE TSet<const UClass*>& GetAllowedClasses() noexcept { return AllowedClasses; }
	
	UE_NODISCARD
	FORCEINLINE EClassFlags GetBannedClassFlags() const noexcept { return BannedClassFlags; }
	
	UE_NODISCARD
	FORCEINLINE void SetBannedClassFlags(const EClassFlags Value) noexcept { BannedClassFlags = Value; }
};

#undef LOCTEXT_NAMESPACE
