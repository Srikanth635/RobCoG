// Copyright 2019, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#include "SLGazeProxy.h"
#include "Eye_Framework.h"
#include "SRanipal_Eye.h"
#include "SRanipal_Eye_v2.h"

// Sets default values
ASLGazeProxy::ASLGazeProxy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FrameworkStatus = Eye_Framework::FrameworkStatus::STOP;
}

// Setup the active camera
bool ASLGazeProxy::Start()
{
	if (FrameworkStatus == Eye_Framework::FrameworkStatus::WORKING)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s::%d  Eye tracking framework already started.."), *FString(__FUNCTION__), __LINE__);
		return true;
	}

	if (EyeTrackingVersion == 0)
	{
		FrameworkStatus = Eye_Framework::Instance()->StartFramework(0);
		if (FrameworkStatus == Eye_Framework::FrameworkStatus::WORKING)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s::%d Eye tracking framework successfully started.."), *FString(__func__), __LINE__);
		}
	}
	else
	{
		FrameworkStatus = Eye_Framework::Instance()->StartFramework(1);
	}
	return FrameworkStatus != Eye_Framework::FrameworkStatus::NOT_SUPPORT;
}

void ASLGazeProxy::Stop()
{
	if (FrameworkStatus == Eye_Framework::FrameworkStatus::STOP)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s::%d Gaze proxy already stopped.."), *FString(__FUNCTION__), __LINE__);
		return;
	}

	if (EyeTrackingVersion == 0)
	{
		FrameworkStatus = Eye_Framework::Instance()->StopFramework(0);
	}
	else
	{
		FrameworkStatus = Eye_Framework::Instance()->StopFramework(1);
	}
}

// Get camera gaze direction vector
bool ASLGazeProxy::GetRelativeGazeDirection(FVector& Direction)
{
	// Keep origin in 0
	FVector Origin;
	if (EyeTrackingVersion == 0)
	{
		return SRanipal_Eye::Instance()->GetGazeRay(GazeIndex::COMBINE, Origin, Direction);
	}
	else
	{
		return SRanipal_Eye_v2::Instance()->GetGazeRay(GazeIndex::COMBINE, Origin, Direction);
		//return true;
	}
}
