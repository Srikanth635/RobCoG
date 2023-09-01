#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "PhysicalConstraint.generated.h"


UCLASS()
class ROBCOG_API UGetPhysicsConstraint : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "GetPhysicsConstraints")
    static void GetConstrainedActors(UPhysicsConstraintComponent* PhysicsConstraintComponent, AActor*& ConstraintActor1, AActor*& ConstraintActor2)
    {
        ConstraintActor1 = PhysicsConstraintComponent->ConstraintActor1;

        ConstraintActor2 = PhysicsConstraintComponent->ConstraintActor2;
    }
};