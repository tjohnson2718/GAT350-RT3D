#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <memory>

#ifdef _DEBUG
	#define DEBUG_NEW   new( _CLIENT_BLOCK, __FILE__, __LINE__)
	#define new DEBUG_NEW
#endif // _DEBUG

namespace nc
{
	// Windows memory tracker
	class MemoryTracker
	{
	public:
		static bool Initialize();
		static void DisplayInfo();
	};
}

