// ========= Copyright 2018, HTC Corporation. All rights reserved. ===========

#include "SRanipal_AvatarLipSample.h"
#include "SRanipal_FunctionLibrary_Lip.h"

#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/Public/DrawDebugHelpers.h"
#include "Engine/Classes/Kismet/KismetMathLibrary.h"
#include "EngineUtils.h"


// Sets default values
ASRanipal_AvatarLipSample::ASRanipal_AvatarLipSample()
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
void ASRanipal_AvatarLipSample::PostEditChangeProperty(struct FPropertyChangedEvent& Event)
{
	Super::PostEditChangeProperty(Event);

	FName PropertyName = Event.GetPropertyName();
	// When change model, reset the model's morph target and binding predict weighting.
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ASRanipal_AvatarLipSample, HeadModel)) {
		if (HeadModel != nullptr) {
			USkeletalMesh* HeadModelSkelMesh = HeadModel->SkeletalMesh;
			if (HeadModelSkelMesh) {
#if ENGINE_MINOR_VERSION > 26 || ENGINE_MAJOR_VERSION > 4			
				TMap<FName, int32> MorphMap = HeadModelSkelMesh->GetMorphTargetIndexMap();
#else 			
				TMap<FName, int32> MorphMap = HeadModelSkelMesh->MorphTargetIndexMap;
#endif
				for (TPair<FName, int32> Entry : MorphMap) {
					LipShapeTable.Add(Entry.Key, LipShape::None);
				}
			}
		}
	}
}
#endif

// Called when the game starts or when spawned
void ASRanipal_AvatarLipSample::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASRanipal_AvatarLipSample::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateLipShapes();
}

void ASRanipal_AvatarLipSample::UpdateLipShapes()
{
	USRanipal_FunctionLibrary_Lip::GetLipWeightings(LipWeighting);
	RenderModelLipShape(HeadModel, LipShapeTable, LipWeighting);
}

void ASRanipal_AvatarLipSample::RenderModelLipShape(USkeletalMeshComponent* Model, TMap<FName, LipShape> lipShapeTable, TMap<LipShape, float> Weighting)
{
	for (TPair<FName, LipShape> Entry : lipShapeTable) {
		if (lipShapeTable[Entry.Key] != LipShape::None) {
			Model->SetMorphTarget(Entry.Key, Weighting[lipShapeTable[Entry.Key]]);
		}
	}
}