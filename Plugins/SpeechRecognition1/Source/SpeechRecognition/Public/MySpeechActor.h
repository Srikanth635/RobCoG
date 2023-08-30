// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySpeechWorker.h"
#include "MySpeechActor.generated.h"

UCLASS()
class SPEECHRECOGNITION_API AMySpeechActor : public AActor
{
	GENERATED_BODY()
	
	FMySpeechWorker* listenerThread;

public:	
	// Sets default values for this actor's properties
	AMySpeechActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Audio", meta = (DisplayName = "Shutdown", Keywords = "Speech Recognition Shutdown"))
	bool Shutdown();
};
