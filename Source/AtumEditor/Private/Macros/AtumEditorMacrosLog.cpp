// © 2023 Kaya Adrian.

#include "Macros/AtumEditorMacrosLog.h"

#include "Settings/AtumSettingsEditor.h"


#define LOCTEXT_NAMESPACE "AtumEditorMacrosLog"

DEFINE_LOG_CATEGORY(LogAtumEditor)

namespace
{
	UE_NODISCARD
	FORCEINLINE bool AreLogsEnabled() noexcept { return GetDefault<UAtumSettingsEditor>()->IsLogAtumEditorEnabled(); }
}
const IsLogAtumEditorEnabledCheck IsLogAtumEditorEnabled = &AreLogsEnabled;

#undef LOCTEXT_NAMESPACE
