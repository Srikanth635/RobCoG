#include "MySpeechWorker.h"
#include "SpeechRecognition.h"
#include "SpeechRecognitionWorker.h"

//General Log
//DEFINE_LOG_CATEGORY(SpeechRecognitionPlugin);

FMySpeechWorker::FMySpeechWorker() {}

FMySpeechWorker::~FMySpeechWorker() {
	delete Thread;
	Thread = NULL;
}

void FMySpeechWorker::ShutDown() {
	Stop();
	Thread->WaitForCompletion();
	delete Thread;
}

void FMySpeechWorker::Stop() {
	ClientMessage(FString("Thread Stopped"));
}

bool FMySpeechWorker::StartThread(AMySpeechActor* manager) {
	Manager = manager;
	FString threadName = FString("FSpeechRecognitionWorker:") + FString::FromInt(8);
	Thread = FRunnableThread::Create(this, *threadName, 0U, TPri_Highest);
	return true;
}

void FMySpeechWorker::ClientMessage(FString text) {
	UE_LOG(LogTemp, Warning, TEXT("%s"), *text);
}


uint32 FMySpeechWorker::Run() {
	ClientMessage(FString("RUN IS CALLED"));
	int counter = 0;
	while (counter < 5) {
		ClientMessage(FString("Inside while"));
		//FString executable = TEXT("C:\\workspace\\Malineni\\Sphinx_UE4_Demo\\working_content\\a.exe");
		//FProcHandle procHandle = FPlatformProcess::CreateProc(*executable,nullptr,false,true,true,nullptr,0,nullptr,nullptr);
		counter = counter +1;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *FString::FromInt(counter));
		//break;
	}
	return 0;
}


