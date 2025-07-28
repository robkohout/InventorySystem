﻿// Copyright Rob Kohout


#include "Items/Inv_InventoryItem.h"
#include "Net/UnrealNetwork.h"

void UInv_InventoryItem::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, ItemManifest);
	DOREPLIFETIME(ThisClass, TotalStackCount);
}

void UInv_InventoryItem::SetItemManifest(const FInv_ItemManifest& Manifest)
{
	ItemManifest = FInstancedStruct::Make<FInv_ItemManifest>(Manifest);
}

bool UInv_InventoryItem::IsStackable() const
{
	const FInv_StackableFragment* Stackable = GetItemManifest().GetFragmentOfType<FInv_StackableFragment>();
	return Stackable != nullptr;
}
