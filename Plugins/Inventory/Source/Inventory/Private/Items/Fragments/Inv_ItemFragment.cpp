// Copyright Rob Kohout

#include "Items/Fragments/Inv_ItemFragment.h"

void FInv_HealthPotionFragment::OnConsume(APlayerController* PlayerController)
{
	// Get a stats component from the PC or the PC->GetPawn()
	// or get the Ability System Component and apply a Gameplay Effect
	// or call an interface function for Healing()

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
		FString::Printf(TEXT("Health Potion consumed! Healing by: %f"), HealAmount));
}

void FInv_ManaPotionFragment::OnConsume(APlayerController* PlayerController)
{
	// Replenish mana
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue,
		FString::Printf(TEXT("Mana Potion consumed! Mana replenished by: %f"), ManaAmount));
}
