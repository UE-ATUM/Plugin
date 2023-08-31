// © 2023 Kaya Adrian.

#pragma once

#include "Logging/LogMacros.h"


#define LOCTEXT_NAMESPACE "AtumMacrosLog"

/**
 * Logs messages to the console using the LogAtum category
 * 
 * @param Verbosity Type of message being written
 * @param Format Message string
 */
#define ATUM_LOG(Verbosity, Format, ...) ATUM_CLOG(true, Verbosity, Format, ##__VA_ARGS__)

/**
 * Logs messages to the console using the LogAtum category when a certain condition is met
 *
 * @param Condition Expression that determines if the message is written or not
 * @param Verbosity Type of message being written
 * @param Format Message string
 */
#define ATUM_CLOG(Condition, Verbosity, Format, ...) \
UE_CLOG(IsLogAtumEnabled() && (Condition), LogAtum, Verbosity, Format, ##__VA_ARGS__)

DECLARE_LOG_CATEGORY_EXTERN(LogAtum, Log, All)

/**
 * Function pointer which takes no arguments and returns a boolean
 */
using IsLogAtumEnabledCheck = bool (*)();

/**
 * Instance of the function pointer which checks if the logs are enabled
 */
extern const IsLogAtumEnabledCheck IsLogAtumEnabled;

#undef LOCTEXT_NAMESPACE
