// ========= Copyright 2019, HTC Corporation. All rights reserved. ===========

#include "SRanipal_GazeRaySample_v2.h"
#include "SRanipal_Eye_v2.h"
#include "SRanipal_FunctionLibrary_Eye_v2.h"

#include "Engine.h"
#include "Engine/Classes/Engine/World.h"


// Sets default values
ASRanipal_GazeRaySample_v2::ASRanipal_GazeRaySample_v2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASRanipal_GazeRaySample_v2::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerCameraRef = UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerCameraManager;
	if (PlayerCameraRef == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Cant find player's camera manager."));
	}
}

// Called every frame
void ASRanipal_GazeRaySample_v2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CameraGazeOrigin, CameraGazeDirection;
	FVector RayCastOrigin, RayCastDirection;

	FVector PlayerMainCameraLocation;
	FRotator PlayerMainCameraRotation;

	bool valid = USRanipal_FunctionLibrary_Eye_v2::GetGazeRay(GazeIndex::COMBINE, CameraGazeOrigin, CameraGazeDirection);
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

