// © 2023 Kaya Adrian.

#include "Macros/AtumMacrosLog.h"

#include "Settings/AtumSettings.h"


#define LOCTEXT_NAMESPACE "AtumMacrosLog"

DEFINE_LOG_CATEGORY(LogAtum)

const IsLoggingAtumFunction IsLoggingAtum = []() noexcept { return GetDefault<UAtumSettings>()->IsLogging(); };

#undef LOCTEXT_NAMESPACE
