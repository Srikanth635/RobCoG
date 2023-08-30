// Copyright 2019, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SLGazeProxy.generated.h"

UCLASS(ClassGroup = (SL), hidecategories = (LOD, Cooking, Transform), DisplayName = "SL Gaze Proxy")
class SRANIPAL_API ASLGazeProxy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASLGazeProxy();

	// Get camera gaze direction vector
	bool GetRelativeGazeDirection(FVector& Direction);

	// Start the eye tracking software
	bool Start();

	// Stop the eye tracking software
	void Stop();

private:
	// Framework status
	uint8 FrameworkStatus;

	// Eye tracking version
	UPROPERTY(EditAnywhere, Category = "Semantic Logger", meta = (ClampMin = 0, ClampMax = 1))
	uint8 EyeTrackingVersion = 1;
};
