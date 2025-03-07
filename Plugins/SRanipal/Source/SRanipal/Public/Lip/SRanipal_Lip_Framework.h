// ========= Copyright 2018, HTC Corporation. All rights reserved. ===========

#pragma once
#include "SRanipal_Enums.h"
#include "SRanipal_API.h"
#include "SRanipal_Lip_Enums.h"

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "SRanipal_Lip_Framework.generated.h"


UCLASS()
class SRANIPAL_API ASRanipal_Lip_Framework : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASRanipal_Lip_Framework();

	/** Enable the lip engine or not. */
	UPROPERTY(EditAnywhere)
		bool EnableLip;
	/** choose the lip version */
	UPROPERTY(EditAnywhere)
		SupportedLipVersion EnableLipVersion = SupportedLipVersion::version1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type) override;

	/** Start the framework. */
	void StartFramework();
	/** Stop the framework and release all resource. */
	void StopFramework();

private:
	int Status;
	const FString AnipalTypeName = "Lip";
	const FString AnipalTypeName_v2 = "Lip_v2";
	enum FrameworkStatus {
		STOP,
		START,
		WORKING,
		ERROR,
	};
};
