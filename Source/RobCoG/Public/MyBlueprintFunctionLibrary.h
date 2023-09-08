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

    /*UPROPERTY(EditAnywhere, BlueprintReadOnly)
    static AActor* ConActor1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        static  AActor* ConActor2;*/

    UFUNCTION(BlueprintCallable, Category = "BFL_Constraints")
    static FString GetConstrainedActors(UPhysicsConstraintComponent* PhysicsConstraintComponent)
    {
        FConstrainComponentPropName comp1 = PhysicsConstraintComponent->ComponentName1;
        FConstrainComponentPropName comp2 = PhysicsConstraintComponent->ComponentName2;

        FName tag1 = comp1.ComponentName;
        FName tag2 = comp2.ComponentName;

        FString Tags = tag1.ToString() + " " + tag2.ToString();
        
        return Tags;
    }
	
};
