// ========= Copyright 2019, HTC Corporation. All rights reserved. ===========

#pragma once

#include "SRanipal_Eye_v2.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SRanipal_AvatarEyeSample_v2.generated.h"


/**
* This is the sample actor to make an avatar with skeletal mesh.
* In this sample, demonstrate how to use SRanipal's Eye and Lip API to achieve face expression animate.
*/
UCLASS()
class SRANIPAL_API ASRanipal_AvatarEyeSample_v2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASRanipal_AvatarEyeSample_v2();

	// Declare your avatar component here.
	UPROPERTY(EditAnywhere)
	USceneComponent *Root;

	// The mesh components.
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent *HeadModel;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent *EyeModelLeft;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent *EyeModelRight;

	// The dummy components, used as eye model's pivot.
	UPROPERTY(EditAnywhere)
	USceneComponent* EyeAnchorLeft;

	UPROPERTY(EditAnywhere)
	USceneComponent* EyeAnchorRight;

	// The array to save eye anchors.
	UPROPERTY(EditAnywhere)
	TArray<USceneComponent*> EyeAnchors;

	// Set your model's morph target and choose relative prediction weighting to it.
	UPROPERTY(EditAnywhere)
	TMap<FName, EyeShape> EyeShapeTable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif // WITH_EDITOR

private:
	const int EYE_NUMS = 2;
	// Used TMap to save return weightings.
	TMap<EyeShape, float> EyeWeighting;

	//int GetFrameworkStatus();
	void UpdateEyeShapes();
	void RenderModelEyeShape(USkeletalMeshComponent* Model, TMap<FName, EyeShape> EyeShapeTable, TMap<EyeShape, float> Weighting);
	void UpdateGazeRay();
};
