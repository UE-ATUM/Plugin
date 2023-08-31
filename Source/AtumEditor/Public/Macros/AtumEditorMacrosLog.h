// © 2023 Kaya Adrian.

#pragma once

#include "Logging/LogMacros.h"


#define LOCTEXT_NAMESPACE "AtumEditorMacrosLog"

/**
 * Logs messages to the console using the LogAtumEditor category
 * 
 * @param Verbosity Type of message being written
 * @param Format Message string
 */
#define ATUMEDITOR_LOG(Verbosity, Format, ...) ATUMEDITOR_CLOG(true, Verbosity, Format, ##__VA_ARGS__)

/**
 * Logs messages to the console using the LogAtumEditor category when a certain condition is met
 *
 * @param Condition Expression that determines if the message is written or not
 * @param Verbosity Type of message being written
 * @param Format Message string
 */
#define ATUMEDITOR_CLOG(Condition, Verbosity, Format, ...) \
UE_CLOG(IsLogAtumEditorEnabled() && (Condition), LogAtumEditor, Verbosity, Format, ##__VA_ARGS__)

DECLARE_LOG_CATEGORY_EXTERN(LogAtumEditor, Log, All)

/**
 * Function pointer which takes no arguments and returns a boolean
 */
using IsLogAtumEditorEnabledCheck = bool (*)();

/**
 * Instance of the function pointer which checks if the logs are enabled
 */
extern const IsLogAtumEditorEnabledCheck IsLogAtumEditorEnabled;

#undef LOCTEXT_NAMESPACE
