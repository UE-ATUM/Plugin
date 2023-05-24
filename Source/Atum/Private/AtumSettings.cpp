// © 2023 Kaya Adrian.

#include "AtumSettings.h"

#include "HAL/IConsoleManager.h"


#define LOCTEXT_NAMESPACE "AtumSettings"

UAtumSettings::UAtumSettings() noexcept :
bLogging(true),
NeuralNetworkAssetTypeColor(213U, 100U, 35U, 200U),
bAllowBlueprintableClasses(true)
{
	CategoryName = TEXT("Plugins");
	SectionName = TEXT("ATUM");
	
	LoadConfig();
	RegisterConsoleVariables();
}

void UAtumSettings::RegisterConsoleVariables() noexcept
{
	auto& Console = IConsoleManager::Get();
	Console.RegisterConsoleVariableRef(
		TEXT("atum.Settings.Logging"),
		bLogging,
		TEXT("Controls whether or not ATUM is able to print messages to LogAtum.")
	);
	Console.RegisterConsoleVariableRef(
		TEXT("atum.Settings.AllowBlueprintableClasses"),
		bAllowBlueprintableClasses,
		TEXT("Filter option which makes it possible whether or not to ") \
		TEXT("create ATUM Neural Networks using derived Blueprintable classes.")
	);
}

#undef LOCTEXT_NAMESPACE
