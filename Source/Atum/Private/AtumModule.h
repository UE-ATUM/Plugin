// © 2023 Kaya Adrian.

#pragma once

#include "IAtumModule.h"


#define LOCTEXT_NAMESPACE "AtumModule"

/**
 * Runtime ATUM Module implementation
 */
class FAtumModule : public IAtumModule
{
public:
	/**
	 * Runs instructions after starting the module
	 */
	virtual void StartupModule() override;
	
	/**
	 * Runs instructions before stopping the module
	 */
	virtual void ShutdownModule() override;
};

#undef LOCTEXT_NAMESPACE
