// Fill out your copyright notice in the Description page of Project Settings.

#include "AtumFloatTensor.h"


EAtumScalarType UAtumFloatTensor::GetScalarType_Implementation() const noexcept
{
	return EAtumScalarType::Float;
}
