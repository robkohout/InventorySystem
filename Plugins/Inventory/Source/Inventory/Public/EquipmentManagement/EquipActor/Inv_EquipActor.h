// Copyright Rob Kohout

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Inv_EquipActor.generated.h"

UCLASS()
class INVENTORY_API AInv_EquipActor : public AActor
{
	GENERATED_BODY()

public:
	AInv_EquipActor();
	FGameplayTag GetEquipmentType() const { return EquipmentType; }
	void SetEquipmentType(const FGameplayTag Type) { EquipmentType = Type; }
	
private:
	UPROPERTY(EditAnywhere, Category = "Inventory")
	FGameplayTag EquipmentType;
};
