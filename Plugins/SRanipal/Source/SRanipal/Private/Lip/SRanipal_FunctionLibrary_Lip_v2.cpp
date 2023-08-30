// ========= Copyright 2018, HTC Corporation. All rights reserved. ===========

#include "SRanipal_FunctionLibrary_Lip_v2.h"


void USRanipal_FunctionLibrary_Lip_v2::GetLipWeightings(UPARAM(ref) TMap<LipShape_v2, float> &shapes)
{
	SRanipal_Lip_v2::Instance()->GetLipWeightings_v2(shapes);
}

void USRanipal_FunctionLibrary_Lip_v2::UpdateTexture(UPARAM(ref) UTexture2D *&texture)
{
	SRanipal_Lip_v2::Instance()->UpdateTexture(texture);
}


