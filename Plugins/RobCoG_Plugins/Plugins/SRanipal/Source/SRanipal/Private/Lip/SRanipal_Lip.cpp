// ========= Copyright 2018, HTC Corporation. All rights reserved. ===========

#include "SRanipal_Lip.h"
#include "SRanipal_API_Lip.h"

SRanipal_Lip* SRanipal_Lip::SRanipal_LipModule = nullptr;

SRanipal_Lip::SRanipal_Lip()
{
	// Define image size.
	ImageWidth = 800; ImageHeight = 400;
	LastUpdateFrame = -1;
	LastUpdateResult = ViveSR::Error::FAILED;
	LipImageBuffer = (uint8*)FMemory::Malloc(ImageWidth * ImageHeight * sizeof(uint8));
	for (int i = 0; i < (int)LipShape::Max; ++i) {
		Weightings.Add((LipShape)i, 0.f);
	}
}

SRanipal_Lip::~SRanipal_Lip()
{
	FMemory::Free(LipImageBuffer);
}

SRanipal_Lip* SRanipal_Lip::Instance()
{
	if (SRanipal_LipModule == nullptr)
		SRanipal_LipModule = new SRanipal_Lip();
	return SRanipal_LipModule;
}

void SRanipal_Lip::DestroyLipModule()
{
	if (SRanipal_LipModule != nullptr) {
		delete SRanipal_LipModule;
		SRanipal_LipModule = nullptr;
	}
}

int SRanipal_Lip::GetLipData_(ViveSR::anipal::Lip::LipData *data)
{
	return ViveSR::anipal::Lip::GetLipData(data);
}

bool SRanipal_Lip::GetLipWeightings(TMap<LipShape, float> &shapes)
{
	bool valid = UpdateData();
	shapes = Weightings;
	return valid;
}

bool SRanipal_Lip::UpdateTexture(UTexture2D *&texture)
{
	int TexWidth = texture->GetSizeX();
	int TexHeight = texture->GetSizeY();
	bool valid = UpdateData();

	updateRegion = new FUpdateTextureRegion2D(0, 0, 0, 0, TexWidth, TexHeight);
	texture->UpdateTextureRegions(0, 1, updateRegion, static_cast<uint32>(ImageWidth * sizeof(uint8)), sizeof(uint8), LipImageBuffer);
	return valid;
}

bool SRanipal_Lip::UpdateData()
{
	lipData.image = LipImageBuffer;
	if (GFrameCounter != LastUpdateFrame) {
		LastUpdateFrame = GFrameCounter;
		LastUpdateResult = ViveSR::anipal::Lip::GetLipData(&lipData);
		if (LastUpdateResult == ViveSR::Error::WORK) {
			for (int i = 0; i < (int)LipShape::Max; ++i) {
				Weightings[(LipShape)i] = lipData.prediction_data.blend_shape_weight[i];
			}
		}
	}
	return LastUpdateResult == ViveSR::Error::WORK;
}
