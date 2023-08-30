// ========= Copyright 2019, HTC Corporation. All rights reserved. ===========

#include "SRanipal_AvatarEyeSample_v2.h"
#include "SRanipal_FunctionLibrary_Eye_v2.h"
#include "SRanipal_Eye_Framework.h"

#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/Public/DrawDebugHelpers.h"
#include "Engine/Classes/Kismet/KismetMathLibrary.h"
#include "EngineUtils.h"


// Sets default values
ASRanipal_AvatarEyeSample_v2::ASRanipal_AvatarEyeSample_v2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the avatar mesh components here.
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetMobility(EComponentMobility::Movable);
	RootComponent = Root;
	HeadModel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HeadModel"));
	HeadModel->SetupAttachment(Root);
	// Create the eye model anchors, the anchors are used as eye model's pivot.
	EyeAnchorLeft = CreateDefaultSubobject<USceneComponent>(TEXT("EyeAnchorLeft"));
	EyeAnchorLeft->SetupAttachment(Root);
	EyeAnchorRight = CreateDefaultSubobject<USceneComponent>(TEXT("EyeAnchorRight"));
	EyeAnchorRight->SetupAttachment(Root);
	// Attach eye models to the anchors.
	EyeModelLeft = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EyeModelLeft"));
	EyeModelLeft->SetupAttachment(EyeAnchorLeft);
	EyeModelRight = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EyeModelRight"));
	EyeModelRight->SetupAttachment(EyeAnchorRight);
	EyeAnchors.Add(EyeAnchorLeft);
	EyeAnchors.Add(EyeAnchorRight);
}

#if WITH_EDITOR
void ASRanipal_AvatarEyeSample_v2::PostEditChangeProperty(struct FPropertyChangedEvent& Event)
{
	Super::PostEditChangeProperty(Event);

	FName PropertyName = Event.GetPropertyName();
	// When change model, reset the model's morph target and binding predict weighting.
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ASRanipal_AvatarEyeSample_v2, HeadModel)) {
		USkeletalMesh* HeadModelSkelMesh = HeadModel->SkeletalMesh;
		if (HeadModelSkelMesh) {
#if ENGINE_MINOR_VERSION > 26 || ENGINE_MAJOR_VERSION > 4			
			TMap<FName, int32> MorphMap = HeadModelSkelMesh->GetMorphTargetIndexMap();
#else 			
			TMap<FName, int32> MorphMap = HeadModelSkelMesh->MorphTargetIndexMap;
#endif
			for (TPair<FName, int32> Entry : MorphMap) {
				EyeShapeTable.Add(Entry.Key, EyeShape::None);
			}
		}
	}
}
#endif

// Called when the game starts or when spawned
void ASRanipal_AvatarEyeSample_v2::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASRanipal_AvatarEyeSample_v2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateEyeShapes();
	UpdateGazeRay();
}

//int ASRanipal_AvatarEyeSample::GetFrameworkStatus() {
//	ASRanipal_Eye_Framework* framework;
//	for (TActorIterator<ASRanipal_Eye_Framework> it(GetWorld()); it; it++) {
//		framework = *it;
//		break;
//	}
//	return framework->GetStatus();
//}

void ASRanipal_AvatarEyeSample_v2::UpdateEyeShapes()
{
	USRanipal_FunctionLibrary_Eye_v2::GetEyeWeightings(EyeWeighting);
	RenderModelEyeShape(HeadModel, EyeShapeTable, EyeWeighting);
}

void ASRanipal_AvatarEyeSample_v2::RenderModelEyeShape(USkeletalMeshComponent* Model, TMap<FName, EyeShape> eyeShapeTable, TMap<EyeShape, float> Weighting)
{
	for (TPair<FName, EyeShape> Entry : eyeShapeTable) {
		if (eyeShapeTable[Entry.Key] != EyeShape::None) {
			Model->SetMorphTarget(Entry.Key, Weighting[eyeShapeTable[Entry.Key]]);
		}
	}
}

void ASRanipal_AvatarEyeSample_v2::UpdateGazeRay()
{
	FVector GazeOriginCombinedLocal, GazeDirectionCombinedLocal;
	FVector ModelGazeOrigin, ModelGazeTarget;
	FRotator LookAtRotation, EyeRotator;

	for (int eye = 0; eye < EYE_NUMS; ++eye) {
		bool valid = USRanipal_FunctionLibrary_Eye_v2::GetGazeRay((GazeIndex)eye, GazeOriginCombinedLocal, GazeDirectionCombinedLocal);
		if (valid) {
#if ENGINE_MINOR_VERSION > 23 || ENGINE_MAJOR_VERSION > 4
			ModelGazeOrigin = EyeAnchors[eye]->GetRelativeLocation();
			ModelGazeTarget = EyeAnchors[eye]->GetRelativeLocation() + GazeDirectionCombinedLocal;
#else
			ModelGazeOrigin = EyeAnchors[eye]->RelativeLocation;
			ModelGazeTarget = EyeAnchors[eye]->RelativeLocation + GazeDirectionCombinedLocal;
#endif
			LookAtRotation = UKismetMathLibrary::FindLookAtRotation(ModelGazeOrigin, ModelGazeTarget);
			EyeRotator = FRotator(LookAtRotation.Roll, LookAtRotation.Yaw, -LookAtRotation.Pitch);
			EyeAnchors[eye]->SetRelativeRotation(EyeRotator);
		}
	}
}