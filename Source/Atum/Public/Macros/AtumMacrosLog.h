// © 2023 Kaya Adrian.

#pragma once

#include "Logging/LogMacros.h"


#define LOCTEXT_NAMESPACE "AtumMacrosLog"

#define ATUM_LOG(Verbosity, Format, ...) ATUM_CLOG(true, Verbosity, Format, ##__VA_ARGS__)

#define ATUM_CLOG(Condition, Verbosity, Format, ...) \
UE_CLOG(IsLogAtumEnabled() && (Condition), LogAtum, Verbosity, Format, ##__VA_ARGS__)

DECLARE_LOG_CATEGORY_EXTERN(LogAtum, Log, All)

using IsLogAtumEnabledCheck = bool (*)();
extern const IsLogAtumEnabledCheck IsLogAtumEnabled;

#undef LOCTEXT_NAMESPACE
