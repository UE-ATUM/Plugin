// © 2023 Kaya Adrian.

#include "AtumSettings.h"

#include "HAL/IConsoleManager.h"


#define LOCTEXT_NAMESPACE "UAtumSettings"

UAtumSettings::UAtumSettings() noexcept : bLogging(true)
{
	CategoryName = TEXT("Plugins");
	SectionName = TEXT("LibTorch");
	LoadConfig();
	
	static const FAutoConsoleVariableRef CVarLogging(
		TEXT("atum.Settings.Logging"),
		bLogging,
		TEXT("Controls whether or not ATUM is able to print messages to LogAtum.")
	);
}

#undef LOCTEXT_NAMESPACE
