// ========= Copyright 2019, HTC Corporation. All rights reserved. ===========

#include "Eye_Framework.h"
#include "SRanipal_Enums.h"
#include "SRanipal_API.h"
#include "SRanipal_API_Eye.h"
#include "ViveSR_Enums.h"

Eye_Framework* Eye_Framework::Framework = nullptr;

Eye_Framework::Eye_Framework()
{
	Status = FrameworkStatus::STOP;
	CameraPosition = FVector::ZeroVector;
}

Eye_Framework::~Eye_Framework()
{
}

Eye_Framework* Eye_Framework::Instance()
{
	if (Framework == nullptr) {
		Framework = new Eye_Framework();
	}
	return Framework;
}

void Eye_Framework::DestroyEyeFramework()
{
	if (Framework != nullptr) {
		delete Framework;
		Framework = nullptr;
	}
}

int Eye_Framework::StartFramework(int version) {
	if (Status == FrameworkStatus::WORKING) {
		UE_LOG(LogTemp, Log, TEXT("[SRanipal] Framework is already running."));
	}
	if (!ViveSR::anipal::Eye::IsViveProEye()) {
	//if (false) {
		UE_LOG(LogTemp, Log, TEXT("[SRanipal] This HMD does not support eye tracking function."));
		Status = FrameworkStatus::NOT_SUPPORT;
	}
	else {
		Status = FrameworkStatus::START;                                        //FrameworkStatus enum present in Eye_Framework.h ----------------------------------
		if (version == EyeVersion::version1) {									//EyeVersion enum present in Eye_Framework.h ----------------------------------
			int* config = 0;
			int result = ViveSR::anipal::Initial(ViveSR::anipal::Eye::ANIPAL_TYPE_EYE, config);  // ANIPAL_TYPE_EYE value set in SRanipal_API_Eye.h and Initial() in SRanipal_API.h
			if (result != ViveSR::Error::WORK) {     //ViveSR::Error enum present in ViveSR_Enums.h
				Status = FrameworkStatus::ERROR;
				UE_LOG(LogTemp, Error, TEXT("[SRanipal] Start %s Framework failed: %d"), *AnipalTypeName, result);   
			}
			else {
				Status = FrameworkStatus::WORKING;
				UE_LOG(LogTemp, Log, TEXT("[SRanipal] Start %s Framework success."), *AnipalTypeName);
			}
		}
		else {
			int* config = 0;
			int ANIPAL_TYPE_EYE_V2 = ViveSR::anipal::Eye::ANIPAL_TYPE_EYE_V2;
			int result = ViveSR::anipal::Initial(ViveSR::anipal::Eye::ANIPAL_TYPE_EYE_V2, config);
			if (result != ViveSR::Error::WORK) {
				Status = FrameworkStatus::ERROR;
				UE_LOG(LogTemp, Error, TEXT("[SRanipal] Start %s Framework failed: %d"), *AnipalTypeName_v2, result);
			}
			else {
				Status = FrameworkStatus::WORKING;
				UE_LOG(LogTemp, Log, TEXT("[SRanipal] Start %s Framework success."), *AnipalTypeName_v2);
			}
		}
	}
	return Status;
	//return FrameworkStatus::WORKING;
}

int Eye_Framework::StopFramework(int version) {
	if (Status != FrameworkStatus::NOT_SUPPORT) {
		if (Status == FrameworkStatus::STOP) {
			UE_LOG(LogTemp, Log, TEXT("[SRanipal] Stop Framework: Module not on"));
		}
		else {
			if (version == EyeVersion::version1) {
				int result = ViveSR::anipal::Release(ViveSR::anipal::Eye::ANIPAL_TYPE_EYE);
				if (result != ViveSR::Error::WORK) {
					UE_LOG(LogTemp, Error, TEXT("[SRanipal] Stop %s Framework failed: %d"), *AnipalTypeName, result);
				}
				else {
					UE_LOG(LogTemp, Log, TEXT("[SRanipal] Stop %s Framework success"), *AnipalTypeName);
				}
			}
			else {
				int result = ViveSR::anipal::Release(ViveSR::anipal::Eye::ANIPAL_TYPE_EYE_V2);
				if (result != ViveSR::Error::WORK) {
					UE_LOG(LogTemp, Error, TEXT("[SRanipal] Stop %s Framework failed: %d"), *AnipalTypeName_v2, result);
				}
				else {
					UE_LOG(LogTemp, Log, TEXT("[SRanipal] Stop %s Framework success"), *AnipalTypeName_v2);
				}
			}
		}
	}
	Status = FrameworkStatus::STOP;
	return Status;
}

int Eye_Framework::GetStatus() {
	return Status;
}

void Eye_Framework::SetCameraPosition(FVector position)
{
	Mutex.Lock();
	CameraPosition = position;
	Mutex.Unlock();
}

FVector Eye_Framework::GetCameraPosition() 
{
	return CameraPosition;
}