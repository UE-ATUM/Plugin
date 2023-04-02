// © 2023 Kaya Adrian.

#include "AtumNeuralNetworkFactory.h"

#include "AtumNeuralNetwork.h"


UAtumNeuralNetworkFactory::UAtumNeuralNetworkFactory()
{
	SupportedClass = UAtumNeuralNetwork::StaticClass();
	bCreateNew = true;
}

UObject* UAtumNeuralNetworkFactory::FactoryCreateNew(
	UClass* const InClass,
	UObject* const InParent,
	const FName InName,
	const EObjectFlags Flags,
	UObject* const Context,
	[[maybe_unused]] FFeedbackContext* const Warn
)
{
	return NewObject<UAtumNeuralNetwork>(InParent, InClass, InName, Flags, Context);
}
