#pragma once

#include <sphinxbase/err.h>
#include <sphinxbase/ad.h>
#include <pocketsphinx.h>
#include <stdio.h>
#include <time.h>
#include <regex>
#include <string>
#include <set>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <locale>
#include <cstdio>
#include <vector>
#include <utility>

//General Log
DECLARE_LOG_CATEGORY_EXTERN(SpeechRecognitionPlugin, Log, All);

#define SENSCR_SHIFT 10

class ASpeechRecognitionActor;

using namespace std;

//Common structures and enumerations
struct FSpeechRecognitionParam
{
	char* name;
	ESpeechRecognitionParamType type;
	char* value;

	// constructor
	FSpeechRecognitionParam(char* name, ESpeechRecognitionParamType type, char* value) {
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
		this->type = type;
		this->value = new char[strlen(value) + 1];
		strcpy(this->value, value);
	}
};

class FSpeechRecognitionWorker :public FRunnable
{

private:

	//Thread
	FRunnableThread* Thread;

	//Pointer to our manager
	ASpeechRecognitionActor* Manager;

	//Thread safe counter 
	FThreadSafeCounter StopTaskCounter;

	//Language
	// const char* langStr = NULL;

	//Paths
	std::string argFilePath;
	std::string contentPath_str;
	std::string logPath;
	std::string modelPath;
	std::string languageModel;
	std::string dictionaryPath;

/
public:
	FSpeechRecognitionWorker();
	virtual ~FSpeechRecognitionWorker();

	//FRunnable interface
	virtual void Stop();
	virtual uint32 Run();

	//Action methods
	void InitConfig();
	
	//Below 2 methods are being called from the SpeechRecognitionActor.cpp
	bool StartThread(ASpeechRecognitionActor* manager);
	void ShutDown();

	// Print Debug Text
	static void ClientMessage(FString txt);

};

