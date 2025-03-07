// ========= Copyright 2018, HTC Corporation. All rights reserved. ===========

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Camera/PlayerCameraManager.h"
#include "SRanipal_MirrorCameraSample_Lip.generated.h"

/**
* This is the sample actor can move a 2D mirror in front of user.
* The actor can let user see avatar's facial expression in mirror.
*/
UCLASS()
class SRANIPAL_API ASRanipal_MirrorCameraSample_Lip : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASRanipal_MirrorCameraSample_Lip();

	UPROPERTY()
		USceneComponent* Root;
	UPROPERTY()
		APlayerCameraManager* PlayerCameraRef;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	const float Distance = 50.f;
};
