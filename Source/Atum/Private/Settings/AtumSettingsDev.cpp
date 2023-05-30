// © 2023 Kaya Adrian.

#include "Settings/AtumSettingsDev.h"

#include "HAL/IConsoleManager.h"


#define LOCTEXT_NAMESPACE "AtumSettingsDev"

UAtumSettingsDev::UAtumSettingsDev() noexcept : bLogAtumEnabled(true)
{
	SectionName = TEXT("ATUM - Development");
	
	LoadConfig();
	IConsoleManager::Get().RegisterConsoleVariableRef(
		TEXT("atum.Dev.EnableLogAtum"),
		bLogAtumEnabled,
		TEXT("Controls whether or not ATUM is able to print debug messages to LogAtum.")
	);
}

#if WITH_EDITOR
FText UAtumSettingsDev::GetSectionText() const
{
	return LOCTEXT("AtumSettingsDevSectionText", "Development");
}

FText UAtumSettingsDev::GetSectionDescription() const
{
	return LOCTEXT("AtumSettingsDevSectionDescription", "ATUM settings for development purposes");
}
#endif

#undef LOCTEXT_NAMESPACE
