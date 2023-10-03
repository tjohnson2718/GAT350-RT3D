#include "World01.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"

namespace nc
{
    bool World01::Initialize()
    {
        return true;
    }

    void World01::Shutdown()
    {
    }

    void World01::Update(float dt)
    {
    }

    void World01::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.SetColor(0, 0, 0, 0);
        renderer.BeginFrame();

        // render
        renderer.SetColor(255, 255, 255, 255);
        renderer.DrawPoint(random(renderer.GetWidth()), random(renderer.GetHeight()));

        // post-render
        renderer.EndFrame();
    }
}
