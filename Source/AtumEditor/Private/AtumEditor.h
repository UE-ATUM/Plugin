// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IAtumEditor.h"


class FAtumEditorModule : public IAtumEditorModule
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
