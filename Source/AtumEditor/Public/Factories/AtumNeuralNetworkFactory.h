// © 2023 Kaya Adrian.

#pragma once

#include "Factories/Factory.h"

#include "AtumNeuralNetworkFactory.generated.h"

class UAtumNeuralNetwork;


#define LOCTEXT_NAMESPACE "AtumNeuralNetworkFactory"

UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Neural Network Factory")
class ATUMEDITOR_API UAtumNeuralNetworkFactory : public UFactory
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TSubclassOf<UAtumNeuralNetwork> NeuralNetworkClass;
	
public:
	UE_NODISCARD_CTOR
	UAtumNeuralNetworkFactory() noexcept;
	
	UE_NODISCARD
	virtual UObject* FactoryCreateNew(
		UClass* InClass,
		UObject* InParent,
		FName InName,
		EObjectFlags Flags,
		UObject* Context,
		FFeedbackContext* Warn
	) override;
	
	virtual bool ConfigureProperties() override;
	
	UE_NODISCARD
	FORCEINLINE TSubclassOf<UAtumNeuralNetwork> GetNeuralNetworkClass() const noexcept { return NeuralNetworkClass; }
	
	UE_NODISCARD
	FORCEINLINE void SetNeuralNetworkClass(const TSubclassOf<UAtumNeuralNetwork> Value) noexcept
	{ NeuralNetworkClass = Value; }
};

#undef LOCTEXT_NAMESPACE
