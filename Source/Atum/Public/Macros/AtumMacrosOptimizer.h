// © 2023 Kaya Adrian.

#pragma once


#define LOCTEXT_NAMESPACE "AtumMacrosOptimizer"

#define GENERATED_ATUM_OPTIMIZER(OptionsClass) \
protected: \
	virtual bool OnInitializeData_Implementation(bool bRetry = true) override; \
	\
public: \
	UE_NODISCARD \
	virtual const FAtumOptimizerBaseOptions* GetBaseOptimizerOptions() const noexcept override { return &Options; } \
	\
	UE_NODISCARD \
	virtual FAtumOptimizerBaseOptions* GetBaseOptimizerOptions() noexcept override { return &Options; } \
	\
	UE_NODISCARD \
	FORCEINLINE const OptionsClass& GetOptimizerOptions() const noexcept { return Options; } \
	\
	UE_NODISCARD \
	FORCEINLINE OptionsClass& GetOptimizerOptions() noexcept { return Options; } \
	\
private:

#undef LOCTEXT_NAMESPACE
