// © 2023 Kaya Adrian.

#pragma once

#include "IAtumEditorModule.h"


#define LOCTEXT_NAMESPACE "AtumEditorModule"

class FAtumEditorModule : public IAtumEditorModule
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

#undef LOCTEXT_NAMESPACE
