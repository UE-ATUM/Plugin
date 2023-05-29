// © 2023 Kaya Adrian.

#include "Macros/AtumEditorMacrosLog.h"

#include "Settings/AtumSettings.h"


#define LOCTEXT_NAMESPACE "AtumEditorMacrosLog"

DEFINE_LOG_CATEGORY(LogAtumEditor)

const IsLoggingAtumEditorFunction IsLoggingAtumEditor = []() noexcept
{
	return GetDefault<UAtumSettings>()->IsLogging();
};

#undef LOCTEXT_NAMESPACE
