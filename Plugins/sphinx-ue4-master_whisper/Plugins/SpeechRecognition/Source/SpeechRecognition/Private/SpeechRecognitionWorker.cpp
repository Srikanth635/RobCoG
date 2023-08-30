#include "SpeechRecognition.h"
#include "SpeechRecognitionWorker.h"

//General Log
DEFINE_LOG_CATEGORY(SpeechRecognitionPlugin);

FSpeechRecognitionWorker::FSpeechRecognitionWorker() {}

FSpeechRecognitionWorker::~FSpeechRecognitionWorker() {
	delete Thread;
	Thread = NULL;
}

void FSpeechRecognitionWorker::ShutDown() {
	Stop();
	Thread->WaitForCompletion();
	delete Thread;
}


void FSpeechRecognitionWorker::InitConfig() {
	argFilePath = contentPath_str + +"model/" + langStr + "/" + langStr + ".args";
	logPath = contentPath_str + "log/";
	modelPath = contentPath_str + "model/" + langStr + "/" + langStr;
	languageModel = contentPath_str + "model/" + langStr + "/" + langStr + ".lm";
	dictionaryPath = contentPath_str + "model/" + langStr + "/" + langStr + ".dict";
}

void FSpeechRecognitionWorker::Stop() {
	StopTaskCounter.Increment();
}

bool FSpeechRecognitionWorker::StartThread(ASpeechRecognitionActor* manager) {
	Manager = manager;
	int32 threadIdx = ISpeechRecognition::Get().GetInstanceCounter();
	FString threadName = FString("FSpeechRecognitionWorker:") + FString::FromInt(threadIdx);
	Thread = FRunnableThread::Create(this, *threadName, 0U, TPri_Highest);
	return true;
}

void FSpeechRecognitionWorker::ClientMessage(FString text) {
	UE_LOG(SpeechRecognitionPlugin, Log, TEXT("%s"), *text);
}


uint32 FSpeechRecognitionWorker::Run() {
	while (StopTaskCounter.GetValue() == 0) {
		UE_LOG(LogTemp, WARNING , TEXT("WARNING: RUN GOT EXECUTED "));
		FString status = FString("SUCCESS")
		UE_LOG(SpeechRecognitionPlugin, Log, TEXT("%s"), *status);
	}
	
}