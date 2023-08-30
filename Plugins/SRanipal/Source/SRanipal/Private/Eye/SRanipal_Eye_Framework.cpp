// ========= Copyright 2019, HTC Corporation. All rights reserved. ===========

#include "SRanipal_Eye_Framework.h"
#include "SRanipal_API.h"
#include "SRanipal_API_Eye.h"
#include "Eye_Framework.h"


// Sets default values
ASRanipal_Eye_Framework::ASRanipal_Eye_Framework()
{
	status = Eye_Framework::FrameworkStatus::STOP;
}

// Called when the game starts or when spawned
void ASRanipal_Eye_Framework::BeginPlay()
{
	Super::BeginPlay();

	// Get camera manager to record main camera position
	PlayerCameraRef = UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerCameraManager;
	if (PlayerCameraRef == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Cant find player's camera manager."));
	}

	// Start framework, If not support eye tracking, use HMD position as default eye tracking data.
	if (EnableEye) {
		if(EnableEyeVersion == SupportedEyeVersion::version1){
			status = Eye_Framework::Instance()->StartFramework(0);
		}
		status = Eye_Framework::Instance()->StartFramework(1);
		if (status != Eye_Framework::FrameworkStatus::NOT_SUPPORT) {
			SetActorTickEnabled(false);
		}
	}
}

void ASRanipal_Eye_Framework::EndPlay(const EEndPlayReason::Type reason)
{
	Super::EndPlay(reason);

	// Stop framework
	if (EnableEyeVersion == SupportedEyeVersion::version1) {
		status = Eye_Framework::Instance()->StopFramework(0);
	}
	status = Eye_Framework::Instance()->StopFramework(1);
}

void ASRanipal_Eye_Framework::Tick(float DeltaTime)
{
	Eye_Framework::Instance()->SetCameraPosition(PlayerCameraRef->GetCameraLocation());
}
