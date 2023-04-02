// Fill out your copyright notice in the Description page of Project Settings.

#include "Tensors/AtumTensorByte.h"


EAtumScalarType UAtumTensorByte::GetScalarType_Implementation() const noexcept
{
	return EAtumScalarType::Byte;
}
