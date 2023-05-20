// © 2023 Kaya Adrian.

#pragma once

#include "Logging/LogMacros.h"


#define ATUMEDITOR_LOG(Verbosity, Format, ...) \
if (GetDefault<UAtumSettings>()->IsLogging()) \
{ \
	UE_LOG(LogAtumEditor, Verbosity, Format, ##__VA_ARGS__) \
}

DECLARE_LOG_CATEGORY_EXTERN(LogAtumEditor, Log, All)
