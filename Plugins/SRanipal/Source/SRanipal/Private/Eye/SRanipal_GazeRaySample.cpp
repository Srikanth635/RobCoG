// ========= Copyright 2019, HTC Corporation. All rights reserved. ===========

#include "SRanipal_GazeRaySample.h"
#include "SRanipal_Eye.h"
#include "SRanipal_FunctionLibrary_Eye.h"

#include "Engine.h"
#include "Engine/Classes/Engine/World.h"


// Sets default values
ASRanipal_GazeRaySample::ASRanipal_GazeRaySample()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASRanipal_GazeRaySample::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCameraRef = UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerCameraManager;
	if (PlayerCameraRef == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Cant find player's camera manager."));
	}
}

// Called every frame
void ASRanipal_GazeRaySample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CameraGazeOrigin, CameraGazeDirection;
	FVector RayCastOrigin, RayCastDirection;

	FVector PlayerMainCameraLocation;
	FRotator PlayerMainCameraRotation;

	bool valid = USRanipal_FunctionLibrary_Eye::GetGazeRay(GazeIndex::COMBINE, CameraGazeOrigin, CameraGazeDirection);
	if (valid) {
		// Find the ray cast origin and target positon.
		PlayerMainCameraLocation = PlayerCameraRef->GetCameraLocation();
		PlayerMainCameraRotation = PlayerCameraRef->GetCameraRotation();
		RayCastOrigin = PlayerMainCameraLocation + FVector(0.f, 0.f, -4.f);
		RayCastDirection = PlayerMainCameraRotation.RotateVector(
			PlayerMainCameraLocation + CameraGazeDirection * RayLength
		);

		DrawDebugLine(
			GetWorld(),
			RayCastOrigin, RayCastDirection,
			FColor::Emerald,
			false, -1, 0,
			RayRadius
		);

	}
}

