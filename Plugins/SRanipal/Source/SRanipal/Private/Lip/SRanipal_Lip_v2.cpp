// ========= Copyright 2018, HTC Corporation. All rights reserved. ===========

#include "SRanipal_Lip_v2.h"
#include "SRanipal_API_Lip.h"

SRanipal_Lip_v2* SRanipal_Lip_v2::SRanipal_LipModule = nullptr;

SRanipal_Lip_v2::SRanipal_Lip_v2()
{
	// Define image size.
	ImageWidth = 800; ImageHeight = 400;
	LastUpdateFrame = -1;
	LastUpdateResult = ViveSR::Error::FAILED;
	LipImageBuffer = (uint8*)FMemory::Malloc(ImageWidth * ImageHeight * sizeof(uint8));
	for (int i = 0; i < (int)LipShape_v2::Max; ++i) {
		Weightings.Add((LipShape_v2)i, 0.f);
	}
}

SRanipal_Lip_v2::~SRanipal_Lip_v2()
{
	FMemory::Free(LipImageBuffer);
}

SRanipal_Lip_v2* SRanipal_Lip_v2::Instance()
{
	if (SRanipal_LipModule == nullptr)
		SRanipal_LipModule = new SRanipal_Lip_v2();
	return SRanipal_LipModule;
}

void SRanipal_Lip_v2::DestroyLipModule()
{
	if (SRanipal_LipModule != nullptr) {
		delete SRanipal_LipModule;
		SRanipal_LipModule = nullptr;
	}
}

int SRanipal_Lip_v2::GetLipData_v2(ViveSR::anipal::Lip::LipData_v2 *data)
{
	return ViveSR::anipal::Lip::GetLipData_v2(data);
}

bool SRanipal_Lip_v2::GetLipWeightings_v2(TMap<LipShape_v2, float> &shapes)
{
	bool valid = UpdateData();
	shapes = Weightings;
	return valid;
}

bool SRanipal_Lip_v2::UpdateTexture(UTexture2D *&texture)
{
	int TexWidth = texture->GetSizeX();
	int TexHeight = texture->GetSizeY();
	bool valid = UpdateData();

	updateRegion = new FUpdateTextureRegion2D(0, 0, 0, 0, TexWidth, TexHeight);
	texture->UpdateTextureRegions(0, 1, updateRegion, static_cast<uint32>(ImageWidth * sizeof(uint8)), sizeof(uint8), LipImageBuffer);
	return valid;
}

bool SRanipal_Lip_v2::UpdateData()
{
	lipData.image = LipImageBuffer;
	if (GFrameCounter != LastUpdateFrame) {
		LastUpdateFrame = GFrameCounter;
		LastUpdateResult = ViveSR::anipal::Lip::GetLipData_v2(&lipData);
		if (LastUpdateResult == ViveSR::Error::WORK) {
			for (int i = 0; i < (int)LipShape_v2::Max; ++i) {
				Weightings[(LipShape_v2)i] = lipData.prediction_data.blend_shape_weight[i];
			}
		}
	}
	return LastUpdateResult == ViveSR::Error::WORK;
}
