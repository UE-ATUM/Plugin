// © 2023 Kaya Adrian.

#pragma once

#include "Logging/LogMacros.h"


//DECLARE_LOG_CATEGORY_EXTERN(LogAtum, Log, All)

#define ATUM_LOG(Verbosity, Format, ...) UE_LOG(LogAtum, Verbosity, Format, ##__VA_ARGS__)

/*
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
private:
*/