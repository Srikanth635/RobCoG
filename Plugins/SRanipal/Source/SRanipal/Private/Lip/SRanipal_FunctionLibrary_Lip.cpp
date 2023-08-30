// ========= Copyright 2018, HTC Corporation. All rights reserved. ===========

#include "SRanipal_FunctionLibrary_Lip.h"


void USRanipal_FunctionLibrary_Lip::GetLipWeightings(UPARAM(ref) TMap<LipShape, float> &shapes)
{
	SRanipal_Lip::Instance()->GetLipWeightings(shapes);
}

void USRanipal_FunctionLibrary_Lip::UpdateTexture(UPARAM(ref) UTexture2D *&texture)
{
	SRanipal_Lip::Instance()->UpdateTexture(texture);
}


