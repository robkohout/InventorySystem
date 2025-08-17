﻿// Copyright Rob Kohout

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inv_CharacterDisplay.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_CharacterDisplay : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
private:
	bool bIsDragging{false};
	TWeakObjectPtr<USkeletalMeshComponent> Mesh;

	FVector2D CurrentPosition;
	FVector2D LastPosition;
};
