// © 2023 Kaya Adrian.

#pragma once

#include "IAtum.h"


class FAtumModule : public IAtumModule
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
