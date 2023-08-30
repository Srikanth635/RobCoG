#pragma once

#include "whisper/whisper.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>

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
#include <thread>
#include <mutex>
#include <cassert>


//General Log
//DECLARE_LOG_CATEGORY_EXTERN(SpeechRecognitionPlugin, Log, All);

#define SENSCR_SHIFT 10

class AMySpeechActor;


class FMySpeechWorker :public FRunnable
{

private:

	//Thread
	FRunnableThread* Thread;

	//Pointer to our manager
	AMySpeechActor* Manager;

public:
	FMySpeechWorker();
	virtual ~FMySpeechWorker();

	//FRunnable interface
	virtual void Stop();
	virtual uint32 Run();

	bool StartThread(AMySpeechActor* manager);

	static void ClientMessage(FString txt);

	void ShutDown();

	
};

