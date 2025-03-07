// ========= Copyright 2019, HTC Corporation. All rights reserved. ===========

#include "SRanipal_EyeFocusSample.h"
#include "SRanipal_Eye.h"
#include "SRanipal_FunctionLibrary_Eye.h"

#include "Engine.h"
#include "Engine/Classes/Engine/World.h"


// Sets default values
ASRanipal_EyeFocusSample::ASRanipal_EyeFocusSample()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASRanipal_EyeFocusSample::BeginPlay()
{
	Super::BeginPlay();

	PlayerCameraRef = UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerCameraManager;
	if (PlayerCameraRef == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Cant find player's camera manager."));
	}
}

// Called every frame
void ASRanipal_EyeFocusSample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FFocusInfo focusInfo;
	FVector gazeOrigin, gazeTarget;
	bool hit = USRanipal_FunctionLibrary_Eye::Focus(GazeIndex::COMBINE, RayLength, RayRadius, PlayerCameraRef, focusInfo, gazeOrigin, gazeTarget);

	DrawDebugLine(
		GetWorld(),
		gazeOrigin, gazeTarget,
		hit ? FColor::Red : FColor::Emerald,
		false, -1, 0,
		RayRadius
	);
}
