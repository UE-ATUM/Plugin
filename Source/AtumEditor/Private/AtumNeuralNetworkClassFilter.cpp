// © 2023 Kaya Adrian.

#include "AtumNeuralNetworkClassFilter.h"

#include "Kismet2/KismetEditorUtilities.h"
#include "Layers/Network/AtumNeuralNetwork.h"
#include "Settings/AtumSettings.h"


#define LOCTEXT_NAMESPACE "AtumNeuralNetworkClassFilter"

FAtumNeuralNetworkClassFilter::FAtumNeuralNetworkClassFilter() noexcept :
AllowedClasses({ UAtumNeuralNetwork::StaticClass() }),
BannedClassFlags(CLASS_Abstract | CLASS_Deprecated | CLASS_HideDropDown | CLASS_NewerVersionExists)
{
}

bool FAtumNeuralNetworkClassFilter::IsClassAllowed(
	[[maybe_unused]] const FClassViewerInitializationOptions& InInitOptions,
	const UClass* const InClass,
	const TSharedRef<FClassViewerFilterFuncs> InFilterFuncs
)
{
	if (InClass == UAtumNeuralNetwork::StaticClass())
		return true;
	
	if (
		InFilterFuncs->IfInChildOfClassesSet(AllowedClasses, InClass) == EFilterReturn::Failed
		|| InClass->HasAnyClassFlags(BannedClassFlags)
	)
		return false;
	
	return !FKismetEditorUtilities::CanCreateBlueprintOfClass(InClass)
	|| GetDefault<UAtumSettings>()->CanAllowBlueprintableClasses();
}

bool FAtumNeuralNetworkClassFilter::IsUnloadedClassAllowed(
	[[maybe_unused]] const FClassViewerInitializationOptions& InInitOptions,
	const TSharedRef<const IUnloadedBlueprintData> InUnloadedClassData,
	const TSharedRef<FClassViewerFilterFuncs> InFilterFuncs
)
{
	return GetDefault<UAtumSettings>()->CanAllowBlueprintableClasses() &&
		!InUnloadedClassData->HasAnyClassFlags(BannedClassFlags) &&
		InFilterFuncs->IfInChildOfClassesSet(AllowedClasses, InUnloadedClassData) != EFilterReturn::Failed;
}

void FAtumNeuralNetworkClassFilter::GetFilterOptions(TArray<TSharedRef<FClassViewerFilterOption>>& OutFilterOptions)
{
	const TSharedRef<FClassViewerFilterOption> BlueprintableClassFilter = MakeShared<FClassViewerFilterOption>();
	BlueprintableClassFilter->bEnabled = GetDefault<UAtumSettings>()->CanAllowBlueprintableClasses();
	BlueprintableClassFilter->LabelText = LOCTEXT("BlueprintableClassFilterLabel", "Show Blueprintable Classes");
	BlueprintableClassFilter->ToolTipText = LOCTEXT(
		"BlueprintableClassFilterToolTip",
		"Shows derived classes marked as Blueprintable in the view."
	);
	BlueprintableClassFilter->OnOptionChanged = FOnClassViewerFilterOptionChanged::CreateLambda(
		[](const bool bEnabled)
		{ GetMutableDefault<UAtumSettings>()->SetAllowBlueprintableClasses(bEnabled); }
	);
	
	OutFilterOptions.Add(BlueprintableClassFilter);
}

#undef LOCTEXT_NAMESPACE
