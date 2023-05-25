// © 2023 Kaya Adrian.

#pragma once

#include "Logging/LogMacros.h"


#define LOCTEXT_NAMESPACE "AtumEditorMacros"

#define ATUMEDITOR_LOG(Verbosity, Format, ...) UE_CLOG( \
	GetDefault<UAtumSettings>()->IsLogging(), \
	LogAtumEditor, \
	Verbosity, \
	Format, \
	##__VA_ARGS__ \
)

DECLARE_LOG_CATEGORY_EXTERN(LogAtumEditor, Log, All)

#undef LOCTEXT_NAMESPACE
