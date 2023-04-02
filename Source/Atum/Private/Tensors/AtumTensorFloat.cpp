// Fill out your copyright notice in the Description page of Project Settings.

#include "Tensors/AtumTensorFloat.h"


EAtumScalarType UAtumTensorFloat::GetScalarType_Implementation() const noexcept
{
	return EAtumScalarType::Float;
}
