// ========= Copyright 2019, HTC Corporation. All rights reserved. ===========

#pragma once
#include "CoreMinimal.h"
/**
 * The internal static class to handle eye framework
 */
class Eye_Framework
{
public:
	Eye_Framework();
	~Eye_Framework();

	static Eye_Framework* Instance();
	static void DestroyEyeFramework();

	
	int GetStatus();
	void SetCameraPosition(FVector position);
	FVector GetCameraPosition();

	enum FrameworkStatus {
		STOP,
		START,
		WORKING,
		ERROR,
		NOT_SUPPORT,
	};
	enum EyeVersion {
		version1,
		version2,
	};
	int StartFramework(int version);
	int StopFramework(int version);
private:
	int Status;
	static Eye_Framework* Framework;
	const FString AnipalTypeName = "Eye";
	const FString AnipalTypeName_v2 = "Eye_v2";
	FCriticalSection Mutex;
	FVector CameraPosition;		// This will be used if no eye tracking support.
};
