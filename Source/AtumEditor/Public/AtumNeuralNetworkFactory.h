// © 2023 Kaya Adrian.

#pragma once

#include "Factories/Factory.h"

#include "AtumNeuralNetworkFactory.generated.h"


UCLASS()
class ATUMEDITOR_API UAtumNeuralNetworkFactory : public UFactory
{
	GENERATED_BODY()

public:
	UE_NODISCARD_CTOR
	UAtumNeuralNetworkFactory();

	UE_NODISCARD
	virtual UObject* FactoryCreateNew(
		UClass* InClass,
		UObject* InParent,
		FName InName,
		EObjectFlags Flags,
		UObject* Context,
		FFeedbackContext* Warn
	) override;
};
