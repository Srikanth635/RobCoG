// Fill out your copyright notice in the Description page of Project Settings.

#include "MySpeechActor.h"
#include "SpeechRecognition.h"


// Sets default values
AMySpeechActor::AMySpeechActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMySpeechActor::BeginPlay()
{
	Super::BeginPlay();
	listenerThread = new FMySpeechWorker();
	bool threadSuccess = listenerThread->StartThread(this);
	
}

// Called every frame
void AMySpeechActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



bool AMySpeechActor::Shutdown()
{
	if (listenerThread != NULL) {
		listenerThread->ShutDown();
		listenerThread = NULL;
		return true;
	}
	else {
		return false;
	}
}
