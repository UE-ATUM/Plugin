// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widgets/SLeafWidget.h"


class ATUMEDITOR_API SAtumNeuralNetworkWidget : public SLeafWidget
{
public:
	SLATE_BEGIN_ARGS(SAtumNeuralNetworkWidget)
		{}
	SLATE_END_ARGS()
	
	void Construct(const FArguments& Arguments) noexcept;
	
	virtual int32 OnPaint(
		const FPaintArgs& Args,
		const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect,
		FSlateWindowElementList& OutDrawElements,
		int32 LayerId,
		const FWidgetStyle& InWidgetStyle,
		bool bParentEnabled
	) const override;

	UE_NODISCARD
	virtual FVector2D ComputeDesiredSize(float LayoutScaleMultiplier) const override;
};
