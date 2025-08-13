﻿// Copyright Rob Kohout

#pragma once

#include "CoreMinimal.h"
#include "Inv_CompositeBase.h"
#include "Inv_Leaf.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORY_API UInv_Leaf : public UInv_CompositeBase
{
	GENERATED_BODY()

public:
	virtual void ApplyFunction(FuncType Function) override;
};
