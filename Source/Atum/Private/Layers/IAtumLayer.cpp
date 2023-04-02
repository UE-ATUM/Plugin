// Fill out your copyright notice in the Description page of Project Settings.

#include "Layers/IAtumLayer.h"


bool IAtumLayer::InitializeData_Implementation() noexcept
{
	bInitialized = true;
	return true;
}

bool IAtumLayer::Forward_Implementation(
	[[maybe_unused]] const TScriptInterface<IAtumTensor>& Input,
	[[maybe_unused]] TScriptInterface<IAtumTensor>& Output
) noexcept
{
	return false;
}
