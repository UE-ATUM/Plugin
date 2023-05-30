// © 2023 Kaya Adrian.

#pragma once

#include "Logging/LogMacros.h"


#define LOCTEXT_NAMESPACE "AtumEditorMacrosLog"

#define ATUMEDITOR_LOG(Verbosity, Format, ...) ATUMEDITOR_CLOG(true, Verbosity, Format, ##__VA_ARGS__)

#define ATUMEDITOR_CLOG(Condition, Verbosity, Format, ...) \
UE_CLOG(IsLogAtumEditorEnabled() && (Condition), LogAtumEditor, Verbosity, Format, ##__VA_ARGS__)

DECLARE_LOG_CATEGORY_EXTERN(LogAtumEditor, Log, All)

using IsLogAtumEditorEnabledCheck = bool (*)();
extern const IsLogAtumEditorEnabledCheck IsLogAtumEditorEnabled;

#undef LOCTEXT_NAMESPACE
