// © 2023 Kaya Adrian.

#pragma once

#include "IAtumEditor.h"


class FAtumEditorModule : public IAtumEditorModule
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
