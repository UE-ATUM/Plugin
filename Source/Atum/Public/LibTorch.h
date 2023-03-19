// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#if HAS_LIBTORCH
__pragma(warning(push))
__pragma(warning(disable: 4067)) /* unexpected tokens following preprocessor directive - expected a newline */
__pragma(warning(disable: 4624)) /* '<class>' : destructor was implicitly defined as deleted */
__pragma(warning(disable: 4686)) /* '<type>' : possible change in behavior, change in UDT return calling convention */
__pragma(warning(disable: 4805)) /* '<op>' : unsafe mix of type '<type1>' and type '<type2>' in operation */

THIRD_PARTY_INCLUDES_START
#include <torch/torch.h> // ReSharper disable once CppUnusedIncludeDirective
THIRD_PARTY_INCLUDES_END

__pragma(warning(pop))
#endif
