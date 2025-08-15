// Copyright Rob Kohout

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Inv_GridSlot.h"
#include "Inv_EquippedGridSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEquippedGridSlotClicked, UInv_EquippedGridSlot*, GridSlot, const FGameplayTag&, EquipmentTypeTag);

/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_EquippedGridSlot : public UInv_GridSlot
{
	GENERATED_BODY()

public:
	virtual void NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& MouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	FEquippedGridSlotClicked EquipGridSlotClicked;

private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FGameplayTag EquipmentTypeTag;
};
