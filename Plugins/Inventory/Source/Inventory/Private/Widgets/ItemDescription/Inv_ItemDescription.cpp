// Copyright Rob Kohout


#include "Widgets/ItemDescription/Inv_ItemDescription.h"

#include "Components/SizeBox.h"

void UInv_ItemDescription::SetVisibility(ESlateVisibility InVisibility)
{
	for (auto Child : GetChildren())
	{
		Child->Collapse();
	}
	Super::SetVisibility(InVisibility);
}

FVector2D UInv_ItemDescription::GetBoxSize() const
{
	return SizeBox->GetDesiredSize();
}
