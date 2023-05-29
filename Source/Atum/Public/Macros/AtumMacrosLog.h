// © 2023 Kaya Adrian.

#pragma once

#include "Logging/LogMacros.h"


#define LOCTEXT_NAMESPACE "AtumMacrosLog"

#define ATUM_LOG(Verbosity, Format, ...) ATUM_CLOG(true, Verbosity, Format, ##__VA_ARGS__)

#define ATUM_CLOG(Condition, Verbosity, Format, ...) \
UE_CLOG(IsLoggingAtum() && (Condition), LogAtum, Verbosity, Format, ##__VA_ARGS__)

DECLARE_LOG_CATEGORY_EXTERN(LogAtum, Log, All)

using IsLoggingAtumFunction = bool (*)();
extern const IsLoggingAtumFunction IsLoggingAtum;

#undef LOCTEXT_NAMESPACE
