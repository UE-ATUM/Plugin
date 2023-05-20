// © 2023 Kaya Adrian.

#include "AtumSettings.h"

#include "HAL/IConsoleManager.h"


#define LOCTEXT_NAMESPACE "AtumSettings"

UAtumSettings::UAtumSettings() noexcept :
bLogging(true),
NeuralNetworkAssetTypeColor(213U, 100U, 35U, 200U)
{
	CategoryName = TEXT("Plugins");
	SectionName = TEXT("ATUM");
	LoadConfig();
	
	static const FAutoConsoleVariableRef CVarLogging(
		TEXT("atum.Settings.Logging"),
		bLogging,
		TEXT("Controls whether or not ATUM is able to print messages to LogAtum.")
	);
}

#undef LOCTEXT_NAMESPACE
