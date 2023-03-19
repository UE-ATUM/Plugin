// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IAtum.h"


class FAtumModule : public IAtumModule
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
