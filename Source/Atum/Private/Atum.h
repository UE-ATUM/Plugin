// © 2023 Kaya Adrian.

#pragma once

#include "IAtum.h"


#define LOCTEXT_NAMESPACE "Atum"

class FAtumModule : public IAtumModule
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

#undef LOCTEXT_NAMESPACE
