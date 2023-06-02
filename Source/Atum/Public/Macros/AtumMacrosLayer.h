// © 2023 Kaya Adrian.

#pragma once


#define LOCTEXT_NAMESPACE "AtumMacrosLayer"

#define GENERATED_ATUM_LAYER_OPTIONS_ONLY(OptionsClass) \
protected: \
	virtual bool LoadFromFile_Implementation(const FString& RelativePath) override; \
	\
public: \
	UE_NODISCARD \
	virtual const FAtumLayerBaseOptions* GetBaseLayerOptions() const noexcept override { return &Options; } \
	\
	UE_NODISCARD \
	virtual FAtumLayerBaseOptions* GetBaseLayerOptions() noexcept override { return &Options; } \
	\
	UE_NODISCARD \
	FORCEINLINE const OptionsClass& GetLayerOptions() const noexcept { return Options; } \
	\
	UE_NODISCARD \
	FORCEINLINE OptionsClass& GetLayerOptions() noexcept { return Options; } \
	\
private:

#define GENERATED_ATUM_LAYER_MODULE_ONLY(ModuleClass) \
GENERATED_ATUM_LAYER_MODULE_ONLY_IMPL(ModuleClass, ModuleClass##Impl)

#define GENERATED_ATUM_LAYER_MODULE_ONLY_IMPL(ModuleClass, ModuleClassImpl) \
protected: \
	TSharedPtr<ModuleClass> Module = nullptr; \
	\
	virtual bool OnInitializeData_Implementation(bool bRetry = true) override; \
	\
	virtual bool OnForward_Implementation( \
		const TScriptInterface<IAtumTensor>& Input, \
		TScriptInterface<IAtumTensor>& Output \
	) override; \
	\
	virtual void SetBaseModule(const torch::nn::Module* const Value) noexcept override \
	{ \
		Module = Value ? MakeShareable(new ModuleClass(std::make_shared<ModuleClassImpl>( \
			*dynamic_cast<const ModuleClassImpl*>(Value) \
		))) : nullptr; \
	} \
	\
public: \
	UE_NODISCARD \
	virtual const torch::nn::Module* GetBaseModule() const noexcept override \
	{ return Module ? Module->get() : nullptr; } \
	\
	UE_NODISCARD \
	FORCEINLINE TSharedPtr<const ModuleClass> GetModule() const noexcept { return Module; } \
	\
	UE_NODISCARD \
	FORCEINLINE TSharedPtr<ModuleClass> GetModule() noexcept { return Module; } \
	\
private:

#define GENERATED_ATUM_LAYER(OptionsClass, ModuleClass) \
GENERATED_ATUM_LAYER_IMPL(OptionsClass, ModuleClass, ModuleClass##Impl)

#define GENERATED_ATUM_LAYER_IMPL(OptionsClass, ModuleClass, ModuleClassImpl) \
	GENERATED_ATUM_LAYER_OPTIONS_ONLY(OptionsClass) \
	GENERATED_ATUM_LAYER_MODULE_ONLY_IMPL(ModuleClass, ModuleClassImpl) \
private:

#undef LOCTEXT_NAMESPACE
