// ========= Copyright 2019, HTC Corporation. All rights reserved. ===========

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "SRanipal_Enums.h"
#include "SRanipal_Eyes_Enums.h"
#include "SRanipal_Eye_Framework.generated.h"


UCLASS()
class SRANIPAL_API ASRanipal_Eye_Framework : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY()
		APlayerCameraManager* PlayerCameraRef;
public:	
	// Sets default values for this actor's properties
	ASRanipal_Eye_Framework();

	/** Enable the eye engine or not. */
	UPROPERTY(EditAnywhere)
		bool EnableEye;
	UPROPERTY(EditAnywhere)
		SupportedEyeVersion EnableEyeVersion = SupportedEyeVersion::version1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type) override;
	virtual void Tick(float DeltaTime) override;

private:
	int status;
};
