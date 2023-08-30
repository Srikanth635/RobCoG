// Copyright 2017-2021, Institute for Artificial Intelligence - University of Bremen

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "PhysicalConstraint.generated.h"


/**
 *
 */
UCLASS()
class UGetPhysicsConstraint : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    /*    UFUNCTION(BlueprintPure, Category = "GetPhysicsConstraints")
        FORCEINLINE void GetConstrainedActors(UPhysicsConstraintComponent* PhysicsConstraintComponent, AActor*& ConstraintActor1, AActor*& ConstraintActor2)
        {
            ConstraintActor1 = PhysicsConstraintComponent->ConstraintActor1;

            ConstraintActor2 = PhysicsConstraintComponent->ConstraintActor2;
        }*/
};