// ========= Copyright 2019, HTC Corporation. All rights reserved. ===========

#include "SRanipal_Eye_v2.h"
#include "SRanipal_API_Eye.h"
#include "ViveSR_Enums.h"
#include "Eye_Framework.h"

#include "Core/Public/Math/NumericLimits.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

using namespace ViveSR::anipal;

SRanipal_Eye_v2* SRanipal_Eye_v2::SRanipal_EyeModule = nullptr;

SRanipal_Eye_v2::SRanipal_Eye_v2()
{
	LastUpdateFrame = -1;
	LastUpdateResult = ViveSR::Error::FAILED;
	for (int i = 0; i < (int)EyeShape::Max; ++i) {
		Weightings.Add((EyeShape)i, 0.f);
	}
}

SRanipal_Eye_v2::~SRanipal_Eye_v2() {}

SRanipal_Eye_v2* SRanipal_Eye_v2::Instance()
{
	if (SRanipal_EyeModule == nullptr)
		SRanipal_EyeModule = new SRanipal_Eye_v2();
	return SRanipal_EyeModule;
}

void SRanipal_Eye_v2::DestroyEyeModule()
{
	if (SRanipal_EyeModule != nullptr) {
		delete SRanipal_EyeModule;
		SRanipal_EyeModule = nullptr;
	}
}

int SRanipal_Eye_v2::GetEyeData_(ViveSR::anipal::Eye::EyeData_v2 * data)
{
	return Eye::GetEyeData_v2(data);
}

int SRanipal_Eye_v2::SetEyeParameter_(ViveSR::anipal::Eye::EyeParameter parameter)
{
	return Eye::SetEyeParameter(parameter);
}

int SRanipal_Eye_v2::GetEyeParameter_(ViveSR::anipal::Eye::EyeParameter *parameter)
{
	return Eye::GetEyeParameter(parameter);
}

int SRanipal_Eye_v2::LaunchEyeCalibration_(void * callback)
{
	return Eye::LaunchEyeCalibration(callback);
}

bool SRanipal_Eye_v2::GetVerboseData(ViveSR::anipal::Eye::VerboseData &data)
{
	bool update = UpdateData();
	data = EyeData_.verbose_data;
	return update;
}

bool SRanipal_Eye_v2::GetEyeOpenness(EyeIndex eye, float &openness)
{
	bool valid = false;
	if (Eye_Framework::Instance()->GetStatus() == Eye_Framework::FrameworkStatus::NOT_SUPPORT) {
		valid = true;
		openness = 1.0f;
	}
	else {
		UpdateData();
		Eye::SingleEyeData eyeData = eye == EyeIndex::LEFT ? EyeData_.verbose_data.left : EyeData_.verbose_data.right;
		valid = eyeData.GetValidity(Eye::SingleEyeDataValidity::SINGLE_EYE_DATA_EYE_OPENNESS_VALIDITY);
		openness = valid ? eyeData.eye_openness : 0.f;
	}
	return valid;
}

bool SRanipal_Eye_v2::GetPupilPosition(EyeIndex eye, FVector2D &position)
{
	bool valid = false;
	if (Eye_Framework::Instance()->GetStatus() == Eye_Framework::FrameworkStatus::NOT_SUPPORT) {
		valid = true;
		position.Set(0.5f, 0.5f);
	}
	else {
		UpdateData();
		Eye::SingleEyeData eyeData = eye == EyeIndex::LEFT ? EyeData_.verbose_data.left : EyeData_.verbose_data.right;
		valid = eyeData.GetValidity(Eye::SingleEyeDataValidity::SINGLE_EYE_DATA_PUPIL_POSITION_IN_SENSOR_AREA_VALIDITY);
		if (valid) {
			position.Set(eyeData.pupil_position_in_sensor_area.X * 2 - 1,
				eyeData.pupil_position_in_sensor_area.Y * -2 + 1);
		}
		else
			position.Set(0.f, 0.f);
	}
	return valid;
}

bool SRanipal_Eye_v2::GetGazeRay(GazeIndex gazeIndex, FVector &origin, FVector &direction)
{
	bool valid = false;
	origin = FVector::ZeroVector;
	direction = FVector::ForwardVector;
	if (Eye_Framework::Instance()->GetStatus() == Eye_Framework::FrameworkStatus::NOT_SUPPORT) {
		origin = Eye_Framework::Instance()->GetCameraPosition();
		valid = true;
	}
	else {
		UpdateData();
		Eye::SingleEyeData singeEyeDatas[2];
		singeEyeDatas[(int)GazeIndex::LEFT] = EyeData_.verbose_data.left;
		singeEyeDatas[(int)GazeIndex::RIGHT] = EyeData_.verbose_data.right;

		if (gazeIndex == GazeIndex::COMBINE)
		{
			valid = singeEyeDatas[(int)GazeIndex::LEFT].GetValidity(Eye::SingleEyeDataValidity::SINGLE_EYE_DATA_GAZE_DIRECTION_VALIDITY)
				&& singeEyeDatas[(int)GazeIndex::RIGHT].GetValidity(Eye::SingleEyeDataValidity::SINGLE_EYE_DATA_GAZE_DIRECTION_VALIDITY);
			if (valid)
			{
				origin = (singeEyeDatas[(int)GazeIndex::LEFT].gaze_origin_mm + singeEyeDatas[(int)GazeIndex::RIGHT].gaze_origin_mm) / 1000 / 2;
				direction = (singeEyeDatas[(int)GazeIndex::LEFT].gaze_direction_normalized + singeEyeDatas[(int)GazeIndex::RIGHT].gaze_direction_normalized) / 2;
				direction.X *= -1;
				CovertToUnrealScale(origin);
				CovertToUnrealScale(direction);
			}
		}
		else if (gazeIndex == GazeIndex::LEFT || gazeIndex == GazeIndex::RIGHT)
		{
			valid = singeEyeDatas[(int)gazeIndex].GetValidity(Eye::SingleEyeDataValidity::SINGLE_EYE_DATA_GAZE_DIRECTION_VALIDITY);
			if (valid)
			{
				origin = singeEyeDatas[(int)gazeIndex].gaze_origin_mm / 1000;
				direction = singeEyeDatas[(int)gazeIndex].gaze_direction_normalized;
				direction.X *= -1;
				CovertToUnrealScale(origin);
				CovertToUnrealScale(direction);
			}
		}
	}
	return valid;
}

bool SRanipal_Eye_v2::GetEyeWeightings(TMap<EyeShape, float> &shape)
{
	bool update = UpdateData();
	float openness[2];
	bool valid[2];
	FVector2D pupilPosition[2];
	for (int index = 0; index < (int)EyeIndex::MAX; ++index) {
		GetEyeOpenness((EyeIndex)index, openness[index]);
		valid[index] = GetPupilPosition((EyeIndex)index, pupilPosition[(int)index]);
	}

	float weighting_up[3] = { FGenericPlatformMath::Max(pupilPosition[(int)GazeIndex::LEFT].Y, 0.f),
							  FGenericPlatformMath::Max(pupilPosition[(int)GazeIndex::RIGHT].Y, 0.f), 0.f };
	float weighting_down[3] = { -FGenericPlatformMath::Max(pupilPosition[(int)GazeIndex::LEFT].Y, 0.f),
								-FGenericPlatformMath::Max(pupilPosition[(int)GazeIndex::RIGHT].Y, 0.f), 0.f };
	float weighting_left[3] = { -FGenericPlatformMath::Max(pupilPosition[(int)GazeIndex::LEFT].X, 0.f),
								-FGenericPlatformMath::Max(pupilPosition[(int)GazeIndex::RIGHT].X, 0.f), 0.f };
	float weighting_right[3] = { FGenericPlatformMath::Max(pupilPosition[(int)GazeIndex::LEFT].X, 0.f),
								 FGenericPlatformMath::Max(pupilPosition[(int)GazeIndex::RIGHT].X, 0.f), 0.f };
	weighting_up[(int)GazeIndex::COMBINE] = (weighting_up[(int)GazeIndex::LEFT] + weighting_up[(int)GazeIndex::RIGHT]) / 2;
	weighting_down[(int)GazeIndex::COMBINE] = (weighting_down[(int)GazeIndex::LEFT] + weighting_down[(int)GazeIndex::RIGHT]) / 2;
	weighting_left[(int)GazeIndex::COMBINE] = (weighting_left[(int)GazeIndex::LEFT] + weighting_left[(int)GazeIndex::RIGHT]) / 2;
	weighting_right[(int)GazeIndex::COMBINE] = (weighting_right[(int)GazeIndex::LEFT] + weighting_right[(int)GazeIndex::RIGHT]) / 2;

	for (int i = 0; i < (int)EyeShape::Max; ++i) {
		Weightings.Add((EyeShape)i, 0.f);
	}

	Weightings[EyeShape::Eye_Left_Blink] = 1 - openness[(int)EyeIndex::LEFT];
	Weightings[EyeShape::Eye_Right_Blink] = 1 - openness[(int)EyeIndex::RIGHT];
	// version2
	Weightings[EyeShape::Eye_Left_Wide] = EyeData_.expression_data.left.eye_wide;
	Weightings[EyeShape::Eye_Right_Wide] = EyeData_.expression_data.right.eye_wide;


	if (valid[(int)EyeIndex::LEFT] && valid[(int)EyeIndex::RIGHT]) {
		FVector combined_gaze_origin, combined_gaze_direction;
		GetGazeRay(GazeIndex::COMBINE, combined_gaze_origin, combined_gaze_direction);
		FVector gaze_direction = combined_gaze_direction - combined_gaze_origin;
		gaze_direction.Y = 0.0f;
		gaze_direction.Normalize(0.f);
		FVector gaze_axis_forward = FVector(1.0, 0.f, 0.f);
		float z_weight = FGenericPlatformMath::Acos(FVector::DotProduct(gaze_direction, gaze_axis_forward));

		Weightings[EyeShape::Eye_Left_Up] = EyeData_.expression_data.left.eye_wide;
		Weightings[EyeShape::Eye_Left_Down] = gaze_direction.Z < 0 ? z_weight : 0;
		Weightings[EyeShape::Eye_Left_Left] = weighting_left[(int)GazeIndex::COMBINE];
		Weightings[EyeShape::Eye_Left_Right] = weighting_right[(int)GazeIndex::COMBINE];
		//Weightings[EyeShape::Eye_Left_Wide] = Weightings[EyeShape::Eye_Left_Up];

		Weightings[EyeShape::Eye_Right_Up] = EyeData_.expression_data.right.eye_wide;
		Weightings[EyeShape::Eye_Right_Down] = gaze_direction.Z < 0 ? z_weight : 0;
		Weightings[EyeShape::Eye_Right_Left] = weighting_left[(int)GazeIndex::COMBINE];
		Weightings[EyeShape::Eye_Right_Right] = weighting_right[(int)GazeIndex::COMBINE];
		//Weightings[EyeShape::Eye_Right_Wide] = Weightings[EyeShape::Eye_Left_Up];
	}
	else if (valid[(int)EyeIndex::LEFT]) {
		FVector combined_gaze_origin, combined_gaze_direction;
		GetGazeRay(GazeIndex::COMBINE, combined_gaze_origin, combined_gaze_direction);
		FVector gaze_direction = combined_gaze_direction - combined_gaze_origin;
		gaze_direction.Y = 0.0f;
		gaze_direction.Normalize(0.f);
		FVector gaze_axis_forward = FVector(1.0, 0.f, 0.f);
		float z_weight = FGenericPlatformMath::Acos(FVector::DotProduct(gaze_direction, gaze_axis_forward));
		Weightings[EyeShape::Eye_Left_Up] = EyeData_.expression_data.left.eye_wide;
		Weightings[EyeShape::Eye_Left_Down] = gaze_direction.Z < 0 ? z_weight : 0;//weighting_down[(int)GazeIndex::LEFT];
		Weightings[EyeShape::Eye_Left_Left] = weighting_left[(int)GazeIndex::LEFT];
		Weightings[EyeShape::Eye_Left_Right] = weighting_right[(int)GazeIndex::LEFT];
		//Weightings[EyeShape::Eye_Left_Wide] = Weightings[EyeShape::Eye_Left_Up];
	}
	else if (valid[(int)EyeIndex::RIGHT]) {
		FVector combined_gaze_origin, combined_gaze_direction;
		GetGazeRay(GazeIndex::COMBINE, combined_gaze_origin, combined_gaze_direction);
		FVector gaze_direction = combined_gaze_direction - combined_gaze_origin;
		gaze_direction.Y = 0.0f;
		gaze_direction.Normalize(0.f);
		FVector gaze_axis_forward = FVector(1.0, 0.f, 0.f);
		float z_weight = FGenericPlatformMath::Acos(FVector::DotProduct(gaze_direction, gaze_axis_forward));
		Weightings[EyeShape::Eye_Right_Up] = EyeData_.expression_data.right.eye_wide;
		Weightings[EyeShape::Eye_Right_Down] = gaze_direction.Z < 0 ? z_weight : 0;//weighting_down[(int)GazeIndex::RIGHT];
		Weightings[EyeShape::Eye_Right_Left] = weighting_left[(int)GazeIndex::RIGHT];
		Weightings[EyeShape::Eye_Right_Right] = weighting_right[(int)GazeIndex::RIGHT];
		//Weightings[EyeShape::Eye_Right_Wide] = Weightings[EyeShape::Eye_Right_Up];
	}
	shape = Weightings;
	return update;
}

bool SRanipal_Eye_v2::Focus(GazeIndex gazeIndex, float maxDistance, float radius, APlayerCameraManager* playerCamera, FFocusInfo &focusInfo, FVector &gazeOrigin, FVector &gazeTarget)
{
	FVector CameraGazeOrigin, CameraGazeDirection;
	FVector RayCastOrigin, RayCastDirection;
	FVector PlayerMainCameraLocation;
	FRotator PlayerMainCameraRotation;

	FCollisionQueryParams traceParam;
	FHitResult hitResult;
	bool hit = false;

	if (GetGazeRay(GazeIndex::COMBINE, CameraGazeOrigin, CameraGazeDirection)) {
		// Find the ray cast origin and target positon.
		PlayerMainCameraLocation = playerCamera->GetCameraLocation();
		PlayerMainCameraRotation = playerCamera->GetCameraRotation();
		RayCastOrigin = PlayerMainCameraLocation;
		RayCastDirection = PlayerMainCameraRotation.RotateVector(PlayerMainCameraLocation + CameraGazeDirection * maxDistance);
		gazeOrigin = RayCastOrigin;
		gazeTarget = RayCastDirection;

		// Create collision information container.
		traceParam = FCollisionQueryParams(FName("traceParam"), true, playerCamera);
		traceParam.bTraceComplex = true;
		traceParam.bReturnPhysicalMaterial = false;
		hitResult = FHitResult(ForceInit);

		// Single line trace
		if (radius == 0.f) {
			hit = playerCamera->GetWorld()->LineTraceSingleByChannel(
				hitResult,
				RayCastOrigin, RayCastDirection,
				ECC_Pawn,
				traceParam);
		}
		// Sphear line trace
		else {
			FCollisionShape sphear = FCollisionShape();
			sphear.SetSphere(radius);
			hit = playerCamera->GetWorld()->SweepSingleByChannel(
				hitResult,
				RayCastOrigin, RayCastDirection,
				FQuat(0.f, 0.f, 0.f, 0.f),
				ECC_Pawn,
				sphear,
				traceParam
			);
		}
		// If collision occured, fill data into focusInfo.
		if (hit) {
			focusInfo.actor = hitResult.GetActor();
			focusInfo.distance = hitResult.Distance;
			focusInfo.point = hitResult.Location;
			focusInfo.normal = hitResult.Normal;
		}
	}
	return hit;
}

bool SRanipal_Eye_v2::Focus(GazeIndex gazeIndex, float maxDistance, APlayerCameraManager* playerCamera, FFocusInfo &focusInfo, FVector &gazeOrigin, FVector &gazeTarget)
{
	return SRanipal_Eye_v2::Focus(gazeIndex, maxDistance, 0, playerCamera, focusInfo, gazeOrigin, gazeTarget);
}

bool SRanipal_Eye_v2::Focus(GazeIndex gazeIndex, APlayerCameraManager* playerCamera, FFocusInfo &focusInfo, FVector &gazeOrigin, FVector &gazeTarget)
{
	return SRanipal_Eye_v2::Focus(gazeIndex, TNumericLimits<float>::Max(), 0, playerCamera, focusInfo, gazeOrigin, gazeTarget);
}

bool SRanipal_Eye_v2::UpdateData()
{
	if (GFrameCounter != LastUpdateFrame) {
		LastUpdateFrame = GFrameCounter;
		LastUpdateResult = GetEyeData_v2(&EyeData_);
	}
	return LastUpdateResult == ViveSR::Error::WORK;
}

void SRanipal_Eye_v2::CovertToUnrealScale(FVector &vector)
{
	FVector temp = vector;
	vector.X = temp.Z;
	vector.Y = temp.X;
	vector.Z = temp.Y;
	vector *= 100;
}
