﻿// Copyright Rob Kohout

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Inv_PlayerController.generated.h"

class UInv_HUDWidget;
class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class INVENTORY_API AInv_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:

	void PrimaryInteract();
	void CreateHUDWidget();
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TArray<TObjectPtr<UInputMappingContext>> DefaultMappingContexts;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TObjectPtr<UInputAction> PrimaryInteractAction;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UInv_HUDWidget> HUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UInv_HUDWidget> HUDWidget;
};
