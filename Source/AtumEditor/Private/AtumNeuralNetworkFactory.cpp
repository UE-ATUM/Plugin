// © 2023 Kaya Adrian.

#include "AtumNeuralNetworkFactory.h"

#include "AtumNeuralNetworkClassFilter.h"
#include "Kismet2/SClassPickerDialog.h"
#include "Layers/AtumNeuralNetwork.h"


#define LOCTEXT_NAMESPACE "AtumNeuralNetworkFactory"

UAtumNeuralNetworkFactory::UAtumNeuralNetworkFactory() noexcept : NeuralNetworkClass(nullptr)
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UAtumNeuralNetwork::StaticClass();
}

UObject* UAtumNeuralNetworkFactory::FactoryCreateNew(
	UClass* const InClass,
	UObject* const InParent,
	const FName InName,
	const EObjectFlags Flags,
	[[maybe_unused]] UObject* const Context,
	[[maybe_unused]] FFeedbackContext* const Warn
)
{
	return NewObject<UAtumNeuralNetwork>(
		InParent,
		NeuralNetworkClass ? NeuralNetworkClass.Get() : InClass,
		InName,
		Flags | RF_Transactional
	);
}

bool UAtumNeuralNetworkFactory::ConfigureProperties()
{
	FClassViewerInitializationOptions Options;
	Options.ClassFilters.Add(MakeShared<FAtumNeuralNetworkClassFilter>());
	Options.Mode = EClassViewerMode::ClassPicker;
	Options.DisplayMode = EClassViewerDisplayMode::TreeView;
	Options.bShowNoneOption = false;
	Options.NameTypeToDisplay = EClassViewerNameTypeToDisplay::Dynamic;
	
	UClass* PickedClass = nullptr;
	const bool bPicked = SClassPickerDialog::PickClass(
		LOCTEXT("CreateAtumNeuralNetworkAssetOptions", "Pick Neural Network Class"),
		Options,
		PickedClass,
		UAtumNeuralNetwork::StaticClass()
	);
	
	NeuralNetworkClass = PickedClass;
	return bPicked;
}

#undef LOCTEXT_NAMESPACE
