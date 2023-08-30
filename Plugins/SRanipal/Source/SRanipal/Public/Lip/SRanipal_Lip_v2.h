// ========= Copyright 2018, HTC Corporation. All rights reserved. ===========

#pragma once
#include "ViveSR_Enums.h"
#include "SRanipal_Lip_Enums.h"

#include "Engine/Classes/Engine/Texture2D.h"
#include "CoreMinimal.h"

#define SR_ANIPAL __declspec(dllimport)
extern "C" {

	namespace ViveSR {

		namespace anipal {
			/** Lip module */
			namespace Lip {

				//const int ANIPAL_TYPE_LIP = 1;
				const int ANIPAL_TYPE_LIP_V2 = 3;
				/** Get the LipData from Lip engine.
				* @param data ViveSR::anipal::Lip::LipData
				* @return one of ViveSR::Error
				*/
				SR_ANIPAL int GetLipData_v2(LipData_v2 *data);
			}
		}
	}
}

/** The prediction result relative blend shape.*/

UENUM(BlueprintType)
enum class LipShape_v2 :uint8
{
	Jaw_Right = 0                UMETA(DisplayName = "Jaw_Right"),
	Jaw_Left = 1                 UMETA(DisplayName = "Jaw_Left"),
	Jaw_Forward = 2              UMETA(DisplayName = "Jaw_Forward"),
	Jaw_Open = 3                 UMETA(DisplayName = "Jaw_Open"),
	Mouth_Ape_Shape = 4          UMETA(DisplayName = "Mouth_Ape_Shape"),
	Mouth_Upper_Right = 5        UMETA(DisplayName = "Mouth_Upper_Right"),
	Mouth_Upper_Left = 6         UMETA(DisplayName = "Mouth_Upper_Left"),
	Mouth_Lower_Right = 7        UMETA(DisplayName = "Mouth_Lower_Right"),
	Mouth_Lower_Left = 8         UMETA(DisplayName = "Mouth_Lower_Left"),
	Mouth_Upper_Overturn = 9     UMETA(DisplayName = "Mouth_Upper_Overturn"),
	Mouth_Lower_Overturn = 10    UMETA(DisplayName = "Mouth_Lower_Overturn"),
	Mouth_Pout = 11              UMETA(DisplayName = "Mouth_Pout"),
	Mouth_Smile_Right = 12       UMETA(DisplayName = "Mouth_Smile_Right"),
	Mouth_Smile_Left = 13        UMETA(DisplayName = "Mouth_Smile_Left"),
	Mouth_Sad_Right = 14         UMETA(DisplayName = "Mouth_Sad_Right"),
	Mouth_Sad_Left = 15          UMETA(DisplayName = "Mouth_Sad_Left"),
	Cheek_Puff_Right = 16        UMETA(DisplayName = "Cheek_Puff_Right"),
	Cheek_Puff_Left = 17         UMETA(DisplayName = "Cheek_Puff_Left"),
	Cheek_Suck = 18              UMETA(DisplayName = "Cheek_Suck"),
	Mouth_Upper_UpRight = 19     UMETA(DisplayName = "Mouth_Upper_UpRight"),
	Mouth_Upper_UpLeft = 20      UMETA(DisplayName = "Mouth_Upper_UpLeft"),
	Mouth_Lower_DownRight = 21   UMETA(DisplayName = "Mouth_Lower_DownRight"),
	Mouth_Lower_DownLeft = 22    UMETA(DisplayName = "Mouth_Lower_DownLeft"),
	Mouth_Upper_Inside = 23      UMETA(DisplayName = "Mouth_Upper_Inside"),
	Mouth_Lower_Inside = 24      UMETA(DisplayName = "Mouth_Lower_Inside"),
	Mouth_Lower_Overlay = 25     UMETA(DisplayName = "Mouth_Lower_Overlay"),
	Tongue_LongStep1 = 26        UMETA(DisplayName = "Tongue_LongStep1"),
	Tongue_LongStep2 = 32        UMETA(DisplayName = "Tongue_LongStep2"),
	Tongue_Down = 30             UMETA(DisplayName = "Tongue_Down"),
	Max = 33                     UMETA(Hidden),
	None = 63                    UMETA(DisplayName = "None"),

};


/**
 * @brief The internal static class about lip relative API
 */
class SRanipal_Lip_v2
{
public:
	SRanipal_Lip_v2();
	~SRanipal_Lip_v2();
	static SRanipal_Lip_v2* Instance();
	static void DestroyLipModule();

	/**
	* Get the LipData from Lip engine. When use this API, you should assign an uint8 image buffer(size = 800*400) to data.image.
	* @return one of ViveSR.Error
	*/
	int GetLipData_v2(ViveSR::anipal::Lip::LipData_v2 *data);
	/**
	* Get a dictionary that stores individual weighting with respect to LipShape
	* @param shapes A dictionary that stores individual weighting with respect to LipShape.
	* @return true if there is any new data.
	*/
	bool GetLipWeightings_v2(TMap<LipShape_v2, float> &shapes);
	/**
	* Update given texture2D with lip image.
	* @param texture A texture2D sholud be defined as UTexture2D::CreateTransient(ImageWidth, ImageHeight, PF_A8)
	* @return true if there is any new data.
	*/
	bool UpdateTexture(UTexture2D *&texture);

public:
	int ImageWidth, ImageHeight;
	int SingleImageWidth;

private:
	bool UpdateData();

private:
	static SRanipal_Lip_v2* SRanipal_LipModule;
	int LastUpdateFrame, LastUpdateResult;
	ViveSR::anipal::Lip::LipData_v2 lipData;
	FUpdateTextureRegion2D* updateRegion;
	uint8* LipImageBuffer;
	TMap<LipShape_v2, float> Weightings;
};