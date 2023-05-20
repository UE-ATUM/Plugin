// © 2023 Kaya Adrian.

#pragma once

#include "Logging/LogMacros.h"


#define LOCTEXT_NAMESPACE "AtumMacros"

#define ATUM_LOG(Verbosity, Format, ...) \
if (GetDefault<UAtumSettings>()->IsLogging()) \
{ \
	UE_LOG(LogAtum, Verbosity, Format, ##__VA_ARGS__) \
}

#define GENERATED_ATUM_LAYER(ModuleClass) \
protected: \
	TUniquePtr<ModuleClass> Module = nullptr; \
	\
public: \
	UE_NODISCARD \
	virtual std::shared_ptr<torch::nn::Module> GetSharedModule() const noexcept override \
	{ return Module ? Module->ptr() : nullptr; } \
	\
	UE_NODISCARD \
	FORCEINLINE const ModuleClass* GetModule() const noexcept { return Module.Get(); } \
	\
	UE_NODISCARD \
	FORCEINLINE ModuleClass* GetModule() noexcept { return Module.Get(); } \
	\
private:

#ifndef LIBTORCH_INCLUDES_START
#define LIBTORCH_INCLUDES_START \
__pragma(warning(push)) \
\
/*
* unexpected tokens following preprocessor directive - expected a newline
*/ \
__pragma(warning(disable: 4067)) \
\
/*
* 'identifier' : unreferenced formal parameter
*/ \
__pragma(warning(disable: 4100)) \
\
/*
* conditional expression is constant
*/ \
__pragma(warning(disable: 4127)) \
\
/*
* 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
*/ \
__pragma(warning(disable: 4251)) \
\
/*
* 'var' : conversion from 'size_t' to 'type', possible loss of data
*/ \
__pragma(warning(disable: 4267)) \
\
/*
* non - DLL-interface class 'class_1' used as base for DLL-interface class 'class_2'
*/ \
__pragma(warning(disable: 4275)) \
\
/*
* 'struct_name' : structure was padded due to __declspec(align())
*/ \
__pragma(warning(disable: 4324)) \
\
/*
* 'derived class' : destructor was implicitly defined as deleted
* because a base class destructor is inaccessible or deleted
*/ \
__pragma(warning(disable: 4624)) \
\
/*
* 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'
*/ \
__pragma(warning(disable: 4668)) \
\
/*
* 'user-defined type' : possible change in behavior, change in UDT return calling convention
*/ \
__pragma(warning(disable: 4686)) \
\
/*
* unreachable code
*/ \
__pragma(warning(disable: 4702)) \
\
/*
* 'operation' : unsafe mix of type 'type' and type 'type' in operation
*/ \
__pragma(warning(disable: 4805)) \
\
THIRD_PARTY_INCLUDES_START
#endif

#ifndef LIBTORCH_INCLUDES_END
#define LIBTORCH_INCLUDES_END \
THIRD_PARTY_INCLUDES_END \
__pragma(warning(pop))
#endif

DECLARE_LOG_CATEGORY_EXTERN(LogAtum, Log, All)

#undef LOCTEXT_NAMESPACE
