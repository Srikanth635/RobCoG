// ========= Copyright 2018, HTC Corporation. All rights reserved. ===========

#include "SRanipal_AvatarLipSample_v2.h"
#include "SRanipal_FunctionLibrary_Lip_v2.h"

#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/Public/DrawDebugHelpers.h"
#include "Engine/Classes/Kismet/KismetMathLibrary.h"
#include "EngineUtils.h"


// Sets default values
ASRanipal_AvatarLipSample_v2::ASRanipal_AvatarLipSample_v2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the avatar mesh components here.
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetMobility(EComponentMobility::Movable);
	RootComponent = Root;
	HeadModel = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HeadModel"));
	HeadModel->SetupAttachment(Root);
	EyeLeft = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LeftEyeModel"));
	EyeLeft->SetupAttachment(Root);
	EyeRight = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RightEyeModel"));
	EyeRight->SetupAttachment(Root);
}

#if WITH_EDITOR
void ASRanipal_AvatarLipSample_v2::PostEditChangeProperty(struct FPropertyChangedEvent& Event)
{
	Super::PostEditChangeProperty(Event);

	FName PropertyName = Event.GetPropertyName();
	// When change model, reset the model's morph target and binding predict weighting.
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ASRanipal_AvatarLipSample_v2, HeadModel)) {
		if (HeadModel != nullptr) {
			USkeletalMesh* HeadModelSkelMesh = HeadModel->SkeletalMesh;
			if (HeadModelSkelMesh) {
#if ENGINE_MINOR_VERSION > 26 || ENGINE_MAJOR_VERSION > 4			
				TMap<FName, int32> MorphMap = HeadModelSkelMesh->GetMorphTargetIndexMap();
#else 			
				TMap<FName, int32> MorphMap = HeadModelSkelMesh->MorphTargetIndexMap;
#endif
				for (TPair<FName, int32> Entry : MorphMap) {
					LipShapeTable.Add(Entry.Key, LipShape_v2::None);
				}
			}
		}
	}
}
#endif

// Called when the game starts or when spawned
void ASRanipal_AvatarLipSample_v2::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASRanipal_AvatarLipSample_v2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateLipShapes();
}

void ASRanipal_AvatarLipSample_v2::UpdateLipShapes()
{
	USRanipal_FunctionLibrary_Lip_v2::GetLipWeightings(LipWeighting);
	RenderModelLipShape(HeadModel, LipShapeTable, LipWeighting);
}

void ASRanipal_AvatarLipSample_v2::RenderModelLipShape(USkeletalMeshComponent* Model, TMap<FName, LipShape_v2> lipShapeTable, TMap<LipShape_v2, float> Weighting)
{
	for (TPair<FName, LipShape_v2> Entry : lipShapeTable) {
		if (lipShapeTable[Entry.Key] != LipShape_v2::None) {
			Model->SetMorphTarget(Entry.Key, Weighting[lipShapeTable[Entry.Key]]);
		}
	}
}