// Fill out your copyright notice in the Description page of Project Settings.

#include "Tensors/AtumTensorInt.h"


EAtumScalarType UAtumTensorInt::GetScalarType_Implementation() const noexcept
{
	return EAtumScalarType::Int;
}
