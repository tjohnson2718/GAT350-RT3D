#include "World01.h"
#include "World02.h"
#include "World03.h"
#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

using namespace std;

std::string revearsedString(std::string& str, int index = 0)
{
	if (index == str.length())
	{
		return "";
	}
	else
	{
		return revearsedString(str, index + 1) + str[index];
	}
}


int main(int argc, char* argv[])
{
	// Recursion Practice
	std::string inputString = "Hello, World!";
	std::string revearsedSt = revearsedString(inputString);
	std::cout << "Original String: " << inputString << endl;
	std::cout << "Revearsed String: " << revearsedSt << endl;

	INFO_LOG("Initialize Engine...")

	//nc::MemoryTracker::Initialize();
	nc::seedRandom((unsigned int)time(nullptr));
	nc::setFilePath("assets");

	ENGINE.Initialize();

	auto world = make_unique<nc::World03>();
	world->Initialize();

	// main loop
	bool quit = false;
	while (!quit)
	{
		// update
		ENGINE.Update();
		quit = ENGINE.IsQuit();

		world->Update(ENGINE.GetTime().GetDeltaTime());

		// draw
		world->Draw(*ENGINE.GetSystem<nc::Renderer>());
	}

	world->Shutdown();
	ENGINE.Shutdown();

	return 0;
}
