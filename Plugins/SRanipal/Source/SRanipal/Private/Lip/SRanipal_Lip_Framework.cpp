// ========= Copyright 2018, HTC Corporation. All rights reserved. ===========

#include "SRanipal_Lip_Framework.h"
#include "SRanipal_Lip.h"
#include "SRanipal_Lip_v2.h"


// Sets default values
ASRanipal_Lip_Framework::ASRanipal_Lip_Framework()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASRanipal_Lip_Framework::BeginPlay()
{
	Super::BeginPlay();
	StartFramework();
}

void ASRanipal_Lip_Framework::EndPlay(const EEndPlayReason::Type reason)
{
	Super::EndPlay(reason);
	StopFramework();
}

void ASRanipal_Lip_Framework::StartFramework()
{
	if (Status != FrameworkStatus::WORKING) {
		Status = FrameworkStatus::START;
		if (EnableLip) {
			if (EnableLipVersion == SupportedLipVersion::version1) {
				int* config = 0;
				int result = ViveSR::anipal::Initial(ViveSR::anipal::Lip::ANIPAL_TYPE_LIP, config);
				if (result != ViveSR::Error::WORK) {
					UE_LOG(LogTemp, Error, TEXT("[SRanipal] Initial %s failed: %d"), *AnipalTypeName, result);
				}
				else {
					UE_LOG(LogTemp, Log, TEXT("[SRanipal] Initial %s success."), *AnipalTypeName);
				}
			}
			else {
				int* config = 0;
				int result = ViveSR::anipal::Initial(ViveSR::anipal::Lip::ANIPAL_TYPE_LIP_V2, config);
				if (result != ViveSR::Error::WORK) {
					UE_LOG(LogTemp, Error, TEXT("[SRanipal] Initial %s failed: %d"), *AnipalTypeName_v2, result);
				}
				else {
					UE_LOG(LogTemp, Log, TEXT("[SRanipal] Initial %s success."), *AnipalTypeName_v2);
				}
			}
			Status = FrameworkStatus::WORKING;
		}
	}
	UE_LOG(LogTemp, Log, TEXT("[SRanipal] Framework is running."));
}

void ASRanipal_Lip_Framework::StopFramework()
{
	if (Status != FrameworkStatus::STOP) {
		if (EnableLipVersion == SupportedLipVersion::version1) {
			int result = ViveSR::anipal::Release(ViveSR::anipal::Lip::ANIPAL_TYPE_LIP);
			if (result != ViveSR::Error::WORK) {
				UE_LOG(LogTemp, Error, TEXT("[SRanipal] Release %s failed: %d"), *AnipalTypeName, result);
			}
			else {
				UE_LOG(LogTemp, Log, TEXT("[SRanipal] Release %s success"), *AnipalTypeName);
			}
		}
		else {
			int result = ViveSR::anipal::Release(ViveSR::anipal::Lip::ANIPAL_TYPE_LIP_V2);
			if (result != ViveSR::Error::WORK) {
				UE_LOG(LogTemp, Error, TEXT("[SRanipal] Release %s failed: %d"), *AnipalTypeName_v2, result);
			}
			else {
				UE_LOG(LogTemp, Log, TEXT("[SRanipal] Release %s success"), *AnipalTypeName_v2);
			}
		}
		Status = FrameworkStatus::STOP;
	}
	UE_LOG(LogTemp, Log, TEXT("[SRanipal] Framework has been stopped."));
}
