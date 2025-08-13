﻿// Copyright Rob Kohout

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Inv_ItemFragment.generated.h"

class UInv_CompositeBase;

USTRUCT(BlueprintType)
struct FInv_ItemFragment
{
	GENERATED_BODY()

	FInv_ItemFragment() {}
	FInv_ItemFragment(const FInv_ItemFragment&) = default;
	FInv_ItemFragment& operator=(const FInv_ItemFragment&) = default;
	FInv_ItemFragment(FInv_ItemFragment&&) = default;
	FInv_ItemFragment& operator=(FInv_ItemFragment&&) = default;
	virtual ~FInv_ItemFragment() {}

	FGameplayTag GetFragmentTag() const { return FragmentTag; }
	void SetFragmentTag(FGameplayTag Tag) { FragmentTag = Tag; }

	virtual void Manifest() {}
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory", meta=(Categories="FragmentTags"))
	FGameplayTag FragmentTag = FGameplayTag::EmptyTag;
};

/*
 * Item fragment specifically for assimilation into a widget.
 */
USTRUCT(BlueprintType)
struct FInv_InventoryItemFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	virtual void Assimilate(UInv_CompositeBase* Composite) const;

protected:
	virtual bool MatchesWidgetTag(const UInv_CompositeBase* Composite) const;
};

USTRUCT(BlueprintType)
struct FInv_GridFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	FIntPoint GetGridSize() const { return GridSize; }
	void SetGridSize(const FIntPoint& Size) { GridSize = Size; }
	float GetGridPadding() const { return GridPadding; }
	void SetGridPadding(float Padding) { GridPadding = Padding; }
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FIntPoint GridSize{1,1};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	float GridPadding{0.0f};
};

USTRUCT(BlueprintType)
struct FInv_ImageFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()

	UTexture2D* GetIcon() const { return Icon; }
	virtual void Assimilate(UInv_CompositeBase* Composite) const override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TObjectPtr<UTexture2D> Icon{nullptr};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	FVector2D IconDimensions{44.f,44.f};
};

USTRUCT(BlueprintType)
struct FInv_TextFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()

	FText GetText() const { return FragmentText; }
	void SetText(const FText& Text) { FragmentText = Text; }
	virtual void Assimilate(UInv_CompositeBase* Composite) const override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FText FragmentText;
};

USTRUCT(BlueprintType)
struct FInv_LabeledNumberFragment : public FInv_InventoryItemFragment
{
	GENERATED_BODY()

	virtual void Assimilate(UInv_CompositeBase* Composite) const override;
	virtual void Manifest() override;

	// When manifesting for the first time, this fragment will randomize. However, once equipped
	// and dropped, an item should retain the same value, so randomization should not occur.
	bool bRandomizeOnManifest{true};
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FText Text_Label{};

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	float Value{0.f};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	float Min{0.f};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	float Max{0.f};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	bool bCollapseLabel{false};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	bool bCollapseValue{false};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 MinFractionalDigits{1};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 MaxFractionalDigits{1};
};

USTRUCT(BlueprintType)
struct FInv_StackableFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	int32 GetMaxStackSize() const { return MaxStackSize; }
	int32 GetStackCount() const { return StackCount; }
	void SetStackCount(int32 Count) { StackCount = Count; }
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 MaxStackSize{1};

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 StackCount{1};
};

USTRUCT(BlueprintType)
struct FInv_ConsumableFragment : public FInv_ItemFragment
{
	GENERATED_BODY()

	virtual void OnConsume(APlayerController* PlayerController) {}
};

USTRUCT(BlueprintType)
struct FInv_HealthPotionFragment : public FInv_ConsumableFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Inventory")
	float HealAmount{20.0f};
	
	virtual void OnConsume(APlayerController* PlayerController) override;
};

USTRUCT(BlueprintType)
struct FInv_ManaPotionFragment : public FInv_ConsumableFragment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Inventory")
	float ManaAmount{20.0f};
	
	virtual void OnConsume(APlayerController* PlayerController) override;
};