// © 2023 Kaya Adrian.

#pragma once

#include "IAtumEditor.h"


#define LOCTEXT_NAMESPACE "AtumEditor"

class FAtumEditorModule : public IAtumEditorModule
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

#undef LOCTEXT_NAMESPACE
