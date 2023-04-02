// © 2023 Kaya Adrian.

#include "SAtumNeuralNetworkWidget.h"

#include "SlateOptMacros.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SAtumNeuralNetworkWidget::Construct([[maybe_unused]] const FArguments& Arguments) noexcept
{
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

int32 SAtumNeuralNetworkWidget::OnPaint(
	[[maybe_unused]] const FPaintArgs& Args,
	const FGeometry& AllottedGeometry,
	[[maybe_unused]] const FSlateRect& MyCullingRect,
	FSlateWindowElementList& OutDrawElements,
	const int32 LayerId,
	[[maybe_unused]] const FWidgetStyle& InWidgetStyle,
	[[maybe_unused]] const bool bParentEnabled
) const
{
	FSlateDrawElement::MakeLines(
		OutDrawElements,
		LayerId,
		AllottedGeometry.ToPaintGeometry(),
		TArray<FVector2D>()
	);
	return LayerId;
}

FVector2D SAtumNeuralNetworkWidget::ComputeDesiredSize([[maybe_unused]] const float LayoutScaleMultiplier) const
{
	return FVector2D(200.0f, 200.0f);
}
