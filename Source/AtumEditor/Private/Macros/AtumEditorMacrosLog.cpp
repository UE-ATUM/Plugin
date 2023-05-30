// © 2023 Kaya Adrian.

#include "Macros/AtumEditorMacrosLog.h"

#include "Settings/AtumSettingsEditor.h"


#define LOCTEXT_NAMESPACE "AtumEditorMacrosLog"

DEFINE_LOG_CATEGORY(LogAtumEditor)

FORCEINLINE bool IsLogging() noexcept { return GetDefault<UAtumSettingsEditor>()->IsLogAtumEditorEnabled(); }
const IsLoggingAtumEditorFunction IsLoggingAtumEditor = &IsLogging;

#undef LOCTEXT_NAMESPACE
