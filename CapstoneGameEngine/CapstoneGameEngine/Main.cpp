#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#include <memory>
#include <string>
#include "SceneManager.h"
#include "Debug.h"
  
int main(int argc, char* args[]) {
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//_crtBreakAlloc = 12118;

	Debug::DebugInit("GameEngineLog.txt");
	
	{
		std::unique_ptr<SceneManager> gsm = std::make_unique<SceneManager>();
		if (gsm->Initialize("Game Engine", 1280, 720) == true) {
			gsm->Run();
		}
	}
	
	//_CrtDumpMemoryLeaks();
	exit(0);
}