// © 2023 Kaya Adrian.

#include "Macros/AtumMacrosLog.h"

#include "Settings/AtumSettingsDev.h"


#define LOCTEXT_NAMESPACE "AtumMacrosLog"

DEFINE_LOG_CATEGORY(LogAtum)

FORCEINLINE bool IsLogging() noexcept { return GetDefault<UAtumSettingsDev>()->IsLogAtumEnabled(); }
const IsLoggingAtumFunction IsLoggingAtum = &IsLogging;

#undef LOCTEXT_NAMESPACE
