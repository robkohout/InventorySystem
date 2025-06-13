// Copyright Rob Kohout

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Inv_ItemFragment.generated.h"

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
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FGameplayTag FragmentTag = FGameplayTag::EmptyTag;
};
