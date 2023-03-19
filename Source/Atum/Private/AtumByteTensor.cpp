// Fill out your copyright notice in the Description page of Project Settings.

#include "AtumByteTensor.h"


EAtumScalarType UAtumByteTensor::GetScalarType_Implementation() const noexcept
{
	return EAtumScalarType::Byte;
}
