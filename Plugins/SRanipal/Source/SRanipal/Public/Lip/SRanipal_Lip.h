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

				const int ANIPAL_TYPE_LIP = 1;
				/** Get the LipData from Lip engine.
				* @param data ViveSR::anipal::Lip::LipData
				* @return one of ViveSR::Error
				*/
				SR_ANIPAL int GetLipData(LipData *data);
			}
		}
	}
}

/** The prediction result relative blend shape.*/
UENUM(BlueprintType)
enum class LipShape :uint8
{
	Jaw_Forward				=  0 UMETA(DisplayName = "Jaw_Forward"),
	Jaw_Right				=  1 UMETA(DisplayName = "Jaw_Right"),
	Jaw_Left				=  2 UMETA(DisplayName = "Jaw_Left"),
	Jaw_Open				=  3 UMETA(DisplayName = "Jaw_Open"),
	Mouth_Ape_Shape			=  4 UMETA(DisplayName = "Mouth_Ape_Shape"),
	Mouth_O_Shape			=  5 UMETA(DisplayName = "Mouth_O_Shape"),
	Mouth_Pout				=  6 UMETA(DisplayName = "Mouth_Pout"),
	Mouth_Lower_Right		=  7 UMETA(DisplayName = "Mouth_Lower_Right"),
	Mouth_Lower_Left		=  8 UMETA(DisplayName = "Mouth_Lower_Left"),
	Mouth_Smile_Right		=  9 UMETA(DisplayName = "Mouth_Smile_Right"),
	Mouth_Smile_Left		= 10 UMETA(DisplayName = "Mouth_Smile_Left"),
	Mouth_Sad_Right			= 11 UMETA(DisplayName = "Mouth_Sad_Right"),
	Mouth_Sad_Left			= 12 UMETA(DisplayName = "Mouth_Sad_Left"),
	Cheek_Puff_Right		= 13 UMETA(DisplayName = "Cheek_Puff_Right"),
	Cheek_Puff_Left			= 14 UMETA(DisplayName = "Cheek_Puff_Left"),
	Mouth_Lower_Inside		= 15 UMETA(DisplayName = "Mouth_Lower_Inside"),
	Mouth_Upper_Inside		= 16 UMETA(DisplayName = "Mouth_Upper_Inside"),
	Mouth_Lower_Overlay		= 17 UMETA(DisplayName = "Mouth_Lower_Overlay"),
	Mouth_Upper_Overlay		= 18 UMETA(DisplayName = "Mouth_Upper_Overlay"),
	Cheek_Suck				= 19 UMETA(DisplayName = "Cheek_Suck"),
	Mouth_LowerRight_Down	= 20 UMETA(DisplayName = "Mouth_LowerRight_Down"),
	Mouth_LowerLeft_Down	= 21 UMETA(DisplayName = "Mouth_LowerLeft_Down"),
	Mouth_UpperRight_Up		= 22 UMETA(DisplayName = "Mouth_UpperRight_Up"),
	Mouth_UpperLeft_Up		= 23 UMETA(DisplayName = "Mouth_UpperLeft_Up"),
	Mouth_Philtrum_Right	= 24 UMETA(DisplayName = "Mouth_Philtrum_Right"),
	Mouth_Philtrum_Left		= 25 UMETA(DisplayName = "Mouth_Philtrum_Left"),
	Max						= 26 UMETA(Hidden),
	None					= 63 UMETA(DisplayName = "None"),
};

/**
 * @brief The internal static class about lip relative API 
 */
class SRanipal_Lip
{
public:
	SRanipal_Lip();
	~SRanipal_Lip();
	static SRanipal_Lip* Instance();
	static void DestroyLipModule();

	/** 
	* Get the LipData from Lip engine. When use this API, you should assign an uint8 image buffer(size = 800*400) to data.image.
	* @return one of ViveSR.Error
	*/
	int GetLipData_(ViveSR::anipal::Lip::LipData *data);
	/** 
	* Get a dictionary that stores individual weighting with respect to LipShape
	* @param shapes A dictionary that stores individual weighting with respect to LipShape.
	* @return true if there is any new data.
	*/
	bool GetLipWeightings(TMap<LipShape, float> &shapes);
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
	static SRanipal_Lip* SRanipal_LipModule;
	int LastUpdateFrame, LastUpdateResult;
	ViveSR::anipal::Lip::LipData lipData;
	FUpdateTextureRegion2D* updateRegion;
	uint8* LipImageBuffer;
	TMap<LipShape, float> Weightings;
};
