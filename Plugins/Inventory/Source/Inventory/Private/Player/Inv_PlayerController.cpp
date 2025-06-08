// Copyright Rob Kohout


#include "Player/Inv_PlayerController.h"
#include "Inventory.h"

void AInv_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogInventory, Log, TEXT("AInv_PlayerController::PlayerController BeginPlay"));
}
