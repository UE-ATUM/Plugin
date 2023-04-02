// Fill out your copyright notice in the Description page of Project Settings.

#include "Tensors/AtumTensorDouble.h"


EAtumScalarType UAtumTensorDouble::GetScalarType_Implementation() const noexcept
{
	return EAtumScalarType::Double;
}
