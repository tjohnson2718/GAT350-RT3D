#include "World01.h"
#include "World02.h"
#include "World03.h"
#include "World04.h"
#include "World05.h"
#include "World06.h"
#include "World07.h"
#include "World08.h"
#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

using namespace std;
int main(int argc, char* argv[])
{
	std::string strOne = "Hello";
	std::string strTwo = "HeLLo";

	cout << nc::StringUtils::ToUpperCase(strOne) << 
		"\n" + nc::StringUtils::ToLowerCase(strOne) << 
		"\n" + nc::StringUtils::IsEqualIgnoreCase(strOne, strTwo) <<
		"\n" + nc::StringUtils::CreateUnique(strOne);

	INFO_LOG("Initialize Engine...")

	//nc::MemoryTracker::Initialize();
	nc::seedRandom((unsigned int)time(nullptr));
	nc::setFilePath("assets");

	ENGINE.Initialize();

	auto world = make_unique<nc::World08>();
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
