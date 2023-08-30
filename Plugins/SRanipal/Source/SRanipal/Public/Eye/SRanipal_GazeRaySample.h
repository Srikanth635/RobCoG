// ========= Copyright 2019, HTC Corporation. All rights reserved. ===========

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Camera/PlayerCameraManager.h"
#include "SRanipal_GazeRaySample.generated.h"

/**
 * This is the sample actor can draw a ray trace from model's eye to user's gaze position.
 */
UCLASS()
class SRANIPAL_API ASRanipal_GazeRaySample : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
		APlayerCameraManager* PlayerCameraRef;
	
public:	
	// Sets default values for this actor's properties
	ASRanipal_GazeRaySample();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float RayLength = 1000.0f;
	float RayRadius = 0.5f;
};
