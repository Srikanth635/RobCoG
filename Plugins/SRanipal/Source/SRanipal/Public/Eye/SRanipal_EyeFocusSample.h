// ======== = Copyright 2019, HTC Corporation.All rights reserved. ========== =
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Camera/PlayerCameraManager.h"
#include "SRanipal_EyeFocusSample.generated.h"


/**
* This is a sample actor that demonstrate focus function.
* User can get gaze location and focus data via Focus() function.
* If the gaze ray hit any other actor, the ray cast's color will become red.
*/
UCLASS()
class SRANIPAL_API ASRanipal_EyeFocusSample : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASRanipal_EyeFocusSample();

	UPROPERTY()
		APlayerCameraManager* PlayerCameraRef;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	float RayLength = 1000.0f;
	float RayRadius = 1.0f;
};
