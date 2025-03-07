// ========= Copyright 2018, HTC Corporation. All rights reserved. ===========

#pragma once

#include "SRanipal_Lip.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SRanipal_AvatarLipSample.generated.h"


/**
* This is the sample actor to make an avatar with skeletal mesh.
* In this sample, demonstrate how to use SRanipal's Lip functions to achieve face expression animate.
*/
UCLASS()
class SRANIPAL_API ASRanipal_AvatarLipSample : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASRanipal_AvatarLipSample();

	// Declare your avatar component here.
	UPROPERTY(EditAnywhere)
		USceneComponent *Root;
	// The mesh components.
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent *HeadModel;
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent *EyeLeft;
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent *EyeRight;

	// Set your model's morph target and choose relative prediction weighting with it.
	UPROPERTY(EditAnywhere)
		TMap<FName, LipShape> LipShapeTable;

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
	// Used TMap to save return weightings.
	TMap<LipShape, float> LipWeighting;

	void UpdateLipShapes();
	void RenderModelLipShape(USkeletalMeshComponent* Model, TMap<FName, LipShape> LipShapeTable, TMap<LipShape, float> Weighting);
};
