// ========= Copyright 2019, HTC Corporation. All rights reserved. ===========

#include "SRanipal_FunctionLibrary_Eye.h"

bool USRanipal_FunctionLibrary_Eye::GetEyeOpenness(EyeIndex eye, UPARAM(ref) float &openness)
{
	return SRanipal_Eye::Instance()->GetEyeOpenness(eye, openness);
}

bool USRanipal_FunctionLibrary_Eye::GetPupilPosition(EyeIndex eye, UPARAM(ref) FVector2D &position)
{
	return SRanipal_Eye::Instance()->GetPupilPosition(eye, position);
}

bool USRanipal_FunctionLibrary_Eye::GetGazeRay(GazeIndex gazeIndex, UPARAM(ref) FVector &origin, UPARAM(ref) FVector &direction)
{
	return SRanipal_Eye::Instance()->GetGazeRay(gazeIndex, origin, direction);
}

bool USRanipal_FunctionLibrary_Eye::Focus(GazeIndex gazeIndex, float maxDistance, float radius, APlayerCameraManager* playerCamera, UPARAM(ref) FFocusInfo &focusInfo, UPARAM(ref) FVector &gazeOrigin, UPARAM(ref) FVector &gazeTarget)
{
	return SRanipal_Eye::Instance()->Focus(gazeIndex, maxDistance, radius, playerCamera, focusInfo, gazeOrigin, gazeTarget);
}

bool USRanipal_FunctionLibrary_Eye::GetEyeWeightings(UPARAM(ref) TMap<EyeShape, float> &shapes)
{
	return SRanipal_Eye::Instance()->GetEyeWeightings(shapes);
}




