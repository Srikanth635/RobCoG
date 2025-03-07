// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "SRanipal_Lip_v2.h"

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SRanipal_FunctionLibrary_Lip_v2.generated.h"

/**
 * @brief SRanipal function library about lip function.
 */
UCLASS()
class SRANIPAL_API USRanipal_FunctionLibrary_Lip_v2 : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* @summary Get a TArray that stores weighting with respect to LipShape.
	* @param[out] weightings A TArray that stores individual weighting with respect to LipShape
	*/
	UFUNCTION(BlueprintCallable, Category = "SRanipal|Lip")
		static void GetLipWeightings(UPARAM(ref) TMap<LipShape_v2, float> &shapes);

	/**
	* @summary Update given texture2D with lip image.
	* @param[out] texture Target texture.
	*/
	UFUNCTION(BlueprintCallable, Category = "SRanipal|Lip")
		static void UpdateTexture(UPARAM(ref) UTexture2D *&texture);
};
