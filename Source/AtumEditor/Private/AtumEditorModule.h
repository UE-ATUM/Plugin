// © 2023 Kaya Adrian.

#pragma once

#include "IAtumEditorModule.h"


#define LOCTEXT_NAMESPACE "AtumEditorModule"

/**
 * Editor ATUM Module implementation
 */
class FAtumEditorModule : public IAtumEditorModule
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
