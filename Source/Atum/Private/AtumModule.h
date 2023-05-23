// © 2023 Kaya Adrian.

#pragma once

#include "IAtumModule.h"


#define LOCTEXT_NAMESPACE "AtumModule"

class FAtumModule : public IAtumModule
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

#undef LOCTEXT_NAMESPACE
