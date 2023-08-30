// ========= Copyright 2019, HTC Corporation. All rights reserved. ===========

#include "SRanipal_FunctionLibrary_Eye_v2.h"

bool USRanipal_FunctionLibrary_Eye_v2::GetEyeOpenness(EyeIndex eye, UPARAM(ref) float &openness)
{
	return SRanipal_Eye_v2::Instance()->GetEyeOpenness(eye, openness);
}

bool USRanipal_FunctionLibrary_Eye_v2::GetPupilPosition(EyeIndex eye, UPARAM(ref) FVector2D &position)
{
	return SRanipal_Eye_v2::Instance()->GetPupilPosition(eye, position);
}

bool USRanipal_FunctionLibrary_Eye_v2::GetGazeRay(GazeIndex gazeIndex, UPARAM(ref) FVector &origin, UPARAM(ref) FVector &direction)
{
	return SRanipal_Eye_v2::Instance()->GetGazeRay(gazeIndex, origin, direction);
}

bool USRanipal_FunctionLibrary_Eye_v2::Focus(GazeIndex gazeIndex, float maxDistance, float radius, APlayerCameraManager* playerCamera, UPARAM(ref) FFocusInfo &focusInfo, UPARAM(ref) FVector &gazeOrigin, UPARAM(ref) FVector &gazeTarget)
{
	return SRanipal_Eye_v2::Instance()->Focus(gazeIndex, maxDistance, radius, playerCamera, focusInfo, gazeOrigin, gazeTarget);
}

bool USRanipal_FunctionLibrary_Eye_v2::GetEyeWeightings(UPARAM(ref) TMap<EyeShape, float> &shapes)
{
	return SRanipal_Eye_v2::Instance()->GetEyeWeightings(shapes);
}




