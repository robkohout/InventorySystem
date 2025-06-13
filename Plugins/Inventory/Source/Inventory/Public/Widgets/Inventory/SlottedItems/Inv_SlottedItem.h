﻿// Copyright Rob Kohout

#pragma once

#include "CoreMinimal.h"
#include "GameDelegates.h"
#include "Blueprint/UserWidget.h"
#include "Inv_SlottedItem.generated.h"

class UInv_InventoryItem;
class UImage;

/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_SlottedItem : public UUserWidget
{
	GENERATED_BODY()

public:
	bool IsStackable() const { return bIsStackable; }
	void SetIsStackable(bool bStackable) { bIsStackable = bStackable; }
	UImage* GetImageIcon() const { return Image_Icon; }
	void SetGridIndex(int32 Index) { GridIndex = Index; }
	int32 GetGridIndex() const { return GridIndex; }
	void SetGridDimensions(const FIntPoint& Dimensions) { GridDimensions = Dimensions; }
	FIntPoint GetGridDimensions() const { return GridDimensions; }
	void SetInventoryItem(UInv_InventoryItem* Item);
	UInv_InventoryItem* GetInventoryItem() const { return InventoryItem.Get(); }
	void SetImageBrush(const FSlateBrush& Brush) const;
	
private:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;

	int32 GridIndex;
	FIntPoint GridDimensions;
	TWeakObjectPtr<UInv_InventoryItem> InventoryItem;
	bool bIsStackable{false};
};
