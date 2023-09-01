// Copyright 2017-2021, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ROBCOG_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = "BFL_Constraints")
        static void GetConstrainedActors(UPhysicsConstraintComponent* PhysicsConstraintComponent, AActor*& ConstraintActor1, AActor*& ConstraintActor2)
    {
        ConstraintActor1 = PhysicsConstraintComponent->ConstraintActor1;

        ConstraintActor2 = PhysicsConstraintComponent->ConstraintActor2;
    }
	
};
