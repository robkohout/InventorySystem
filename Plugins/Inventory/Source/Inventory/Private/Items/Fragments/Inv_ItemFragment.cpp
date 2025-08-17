﻿// Copyright Rob Kohout

#include "Items/Fragments/Inv_ItemFragment.h"
#include "EquipmentManagement/EquipActor/Inv_EquipActor.h"
#include "Widgets/Composite/Inv_CompositeBase.h"
#include "Widgets/Composite/Inv_Leaf_Image.h"
#include "Widgets/Composite/Inv_Leaf_LabeledValue.h"
#include "Widgets/Composite/Inv_Leaf_Text.h"

void FInv_InventoryItemFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	if (!MatchesWidgetTag(Composite)) return;
	Composite->Expand();
}

bool FInv_InventoryItemFragment::MatchesWidgetTag(const UInv_CompositeBase* Composite) const
{
	return Composite->GetFragmentTag().MatchesTagExact(GetFragmentTag());
}

void FInv_ImageFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	if (!MatchesWidgetTag(Composite)) return;

	UInv_Leaf_Image* Image = Cast<UInv_Leaf_Image>(Composite);
	if (!IsValid(Image)) return;

	Image->SetImage(Icon);
	Image->SetBoxSize(IconDimensions);
	Image->SetImageSize(IconDimensions);
}

void FInv_TextFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	if (!MatchesWidgetTag(Composite)) return;

	UInv_Leaf_Text* LeafText = Cast<UInv_Leaf_Text>(Composite);
	if (!IsValid(LeafText)) return;

	LeafText->SetText(FragmentText);
}

void FInv_LabeledNumberFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	if (!MatchesWidgetTag(Composite)) return;

	UInv_Leaf_LabeledValue* LabeledValue = Cast<UInv_Leaf_LabeledValue>(Composite);
	if (!IsValid(LabeledValue)) return;

	LabeledValue->SetText_Label(Text_Label, bCollapseLabel);

	FNumberFormattingOptions Options;
	Options.MinimumFractionalDigits = MinFractionalDigits;
	Options.MaximumFractionalDigits = MaxFractionalDigits;
	
	LabeledValue->SetText_Value(FText::AsNumber(Value, &Options), bCollapseValue);
}

void FInv_LabeledNumberFragment::Manifest()
{
	FInv_InventoryItemFragment::Manifest();

	if (bRandomizeOnManifest)
	{
		Value = FMath::FRandRange(Min, Max);
	}
	bRandomizeOnManifest = false;
}

void FInv_ConsumableFragment::OnConsume(APlayerController* PlayerController)
{
	for (auto& Modifier : ConsumeModifiers)
	{
		auto& ModRef = Modifier.GetMutable();
		ModRef.OnConsume(PlayerController);
	}
}

void FInv_ConsumableFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	for (const auto& Modifier : ConsumeModifiers)
	{
		const auto& ModRef = Modifier.Get();
		ModRef.Assimilate(Composite);
	}
}

void FInv_ConsumableFragment::Manifest()
{
	FInv_InventoryItemFragment::Manifest();
	for (auto& Modifier : ConsumeModifiers)
	{
		auto& ModRef = Modifier.GetMutable();
		ModRef.Manifest();
	}
}

void FInv_HealthPotionFragment::OnConsume(APlayerController* PlayerController)
{
	// Get a stats component from the PC or the PC->GetPawn()
	// or get the Ability System Component and apply a Gameplay Effect
	// or call an interface function for Healing()

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
		FString::Printf(TEXT("Health Potion consumed! Healing by: %f"), GetValue()));
}

void FInv_ManaPotionFragment::OnConsume(APlayerController* PlayerController)
{
	// Replenish mana
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
		FString::Printf(TEXT("Mana Potion consumed! Mana replenished by: %f"), GetValue()));
}

void FInv_StrengthModifier::OnEquip(APlayerController* PlayerController)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
		FString::Printf(TEXT("Strength increased by: %f"), GetValue()));
}

void FInv_StrengthModifier::OnUnequip(APlayerController* PlayerController)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		FString::Printf(TEXT("Item Unequipped. Strength decreased by: %f"), GetValue()));
}

void FInv_ArmorModifier::OnEquip(APlayerController* PlayerController)
{
	GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Green,
		FString::Printf(TEXT("Item equipped. Armor increased by: %f"), GetValue()));
}

void FInv_ArmorModifier::OnUnequip(APlayerController* PlayerController)
{
	GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Red,
		FString::Printf(TEXT("Item unequipped. Armor decreased by: %f"), GetValue()));
}

void FInv_DamageModifier::OnEquip(APlayerController* PlayerController)
{
	GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Green,
		FString::Printf(TEXT("Item equipped. Damage increased by: %f"),	GetValue()));
}

void FInv_DamageModifier::OnUnequip(APlayerController* PlayerController)
{
	GEngine->AddOnScreenDebugMessage(-1,5.f, FColor::Red,
		FString::Printf(TEXT("Item equipped. Damage increased by: %f"),	GetValue()));
}

void FInv_EquipmentFragment::OnEquip(APlayerController* PlayerController)
{
	if (bEquipped) return;
	bEquipped = true;
	for(auto& Modifier : EquipModifiers)
	{
		auto& ModRef = Modifier.GetMutable();
		ModRef.OnEquip(PlayerController);
	}
}

void FInv_EquipmentFragment::OnUnequip(APlayerController* PlayerController)
{
	if (!bEquipped) return;
	bEquipped = false;
	for (auto& Modifier : EquipModifiers)
	{
		auto& ModRef = Modifier.GetMutable();
		ModRef.OnUnequip(PlayerController);
	}
}

void FInv_EquipmentFragment::Assimilate(UInv_CompositeBase* Composite) const
{
	FInv_InventoryItemFragment::Assimilate(Composite);
	for (const auto& Modifier : EquipModifiers)
	{
		const auto& ModRef = Modifier.Get();
		ModRef.Assimilate(Composite);
	}
}

void FInv_EquipmentFragment::Manifest()
{
	FInv_InventoryItemFragment::Manifest();
	for (auto& Modifier : EquipModifiers)
	{
		auto& ModRef = Modifier.GetMutable();
		ModRef.Manifest();
	}
}

AInv_EquipActor* FInv_EquipmentFragment::SpawnAttachedActor(USkeletalMeshComponent* AttachMesh) const
{
	if (!IsValid(EquipActorClass) || !IsValid(AttachMesh)) return nullptr;

	AInv_EquipActor* SpawnedActor = AttachMesh->GetWorld()->SpawnActor<AInv_EquipActor>(EquipActorClass);
	SpawnedActor->AttachToComponent(AttachMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketAttachPoint);

	return SpawnedActor;
}

void FInv_EquipmentFragment::DestroyAttachedActor()
{
	if (EquippedActor.IsValid())
	{
		EquippedActor->Destroy();
	}
}

void FInv_EquipmentFragment::SetEquippedActor(AInv_EquipActor* EquipActor)
{
	EquippedActor = EquipActor;
}
