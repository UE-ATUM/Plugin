// © 2023 Kaya Adrian.

#include "Settings/AtumSettingsEditor.h"

#include "HAL/IConsoleManager.h"


#define LOCTEXT_NAMESPACE "AtumSettingsEditor"

UAtumSettingsEditor::UAtumSettingsEditor() noexcept :
bLogAtumEditorEnabled(true),
bBlueprintableClassesAllowed(true),
NeuralNetworkAssetTypeColor(213U, 100U, 35U, 200U)
{
	SectionName = TEXT("ATUM - Editor");
	
	LoadConfig();
	auto& ConsoleManager = IConsoleManager::Get();
	
	ConsoleManager.RegisterConsoleVariableRef(
		TEXT("atum.Editor.EnableLogAtumEditor"),
		bLogAtumEditorEnabled,
		TEXT("Controls whether or not ATUM is able to print debug messages to LogAtumEditor.")
	);
	ConsoleManager.RegisterConsoleVariableRef(
		TEXT("atum.Editor.AllowBlueprintableClasses"),
		bBlueprintableClassesAllowed,
		TEXT("Filter option which makes it possible whether or not to ") \
		TEXT("create ATUM Neural Networks using derived Blueprintable classes.")
	);
}

#if WITH_EDITOR
FText UAtumSettingsEditor::GetSectionText() const
{
	return LOCTEXT("AtumSettingsEditorSectionText", "Editor");
}

FText UAtumSettingsEditor::GetSectionDescription() const
{
	return LOCTEXT("AtumSettingsEditorSectionDescription", "ATUM settings that control editor features");
}
#endif

#undef LOCTEXT_NAMESPACE
