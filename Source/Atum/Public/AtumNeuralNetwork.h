// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Layers/IAtumLayer.h"

#include "AtumNeuralNetwork.generated.h"


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Neural Network")
class ATUM_API UAtumNeuralNetwork : public UObject, public IAtumLayer
{
	GENERATED_BODY()
};
