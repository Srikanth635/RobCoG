// ========= Copyright 2019, HTC Corporation. All rights reserved. ===========

#pragma once
#include "SRanipal_Eye.h"
#include "SRanipal_Enums.h"
#include "SRanipal_Eyes_Enums.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SRanipal_FunctionLibrary_Eye.generated.h"

/**
 * @brief SRanipal blueprint function library about eye function.
 */
UCLASS()
class SRANIPAL_API USRanipal_FunctionLibrary_Eye : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Get the openness of specific eye.
	 * @param eye Specific which eye.
	 * @param[out] openness The eye openness is clamped to the range [0,1]. when openness = 0, eye is closed. when openness = 1 eye is open.
	 * @return true if the openess is valid, otherwise false.
	 */
		UFUNCTION(BlueprintCallable, Category = "SRanipal|Eye")
		static bool GetEyeOpenness(EyeIndex eye, UPARAM(ref) float &openness);

	/**
	 * Get the position of specific pupil. When position = (1, 1), eye looking up and right. When position = (-1, -1), looking down and left.
	 * @param eye Specific which eye.
	 * @param[out] position The 2d vector specify the pupil's position.
	 * @return true if the position is valid, otherwise false.
	 */
	UFUNCTION(BlueprintCallable, Category = "SRanipal|Eye")
		static bool GetPupilPosition(EyeIndex eye, UPARAM(ref) FVector2D &position);

	/**
	* Get the gaze ray of specific eye.
	* @param param gazeIndex Specific which eye.
	* @param[out] origin The starting point of the ray in local coordinates.
	* @param[out] direction The direction of the ray.
	* @return true if the gaze ray is valid, otherwise false.
	*/
	UFUNCTION(BlueprintCallable, Category = "SRanipal|Eye")
		static bool GetGazeRay(GazeIndex gazeIndex, UPARAM(ref) FVector &origin, UPARAM(ref) FVector &direction);


	/**
	* Get the combined gaze ray and focusInfo when any candidate object was focused on.
	* @param gazeIndex Specific which eye.
	* @param maxDistance the max distance the ray should check for collisions.
	* @param radius The radius of the gaze ray.
	* @param playerCamera The player's camera controller. You can get this by UGameplayStatics::GetPlayerController(UWorld*, playerIndex)->PlayerCameraManager.
	* @param[out] focusInfo If true is returned, focusInfo will contain the information about where the actor was focused on.
	* @sa FFocusInfo
	* @returns true if the gaze rays hit any actor, otherwise false.
	*/
	UFUNCTION(BlueprintCallable, Category = "SRanipal|Eye")
		static bool Focus(GazeIndex gazeIndex, float maxDistance, float radius, APlayerCameraManager* playerCamera, UPARAM(ref) FFocusInfo &focusInfo, UPARAM(ref) FVector &gazeOrigin, UPARAM(ref) FVector &gazeTarget);

	/**
	* Get a dictionary that stores individual weighting with respect to EyeShape.
	* @param[out] weightings A TArray that stores individual weighting with respect to EyeShape.
	* @return true if there is any new data.
	*/
	UFUNCTION(BlueprintCallable, Category = "SRanipal|Eye")
		static bool GetEyeWeightings(UPARAM(ref) TMap<EyeShape, float> &shapes);
	
	
};
