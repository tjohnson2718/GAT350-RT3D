#include "Memory.h"
#include <iostream>

namespace nc
{
	bool MemoryTracker::Initialize()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		return true;
	}

	void MemoryTracker::DisplayInfo()
	{
		_CrtMemDumpAllObjectsSince(NULL);
	}
}
