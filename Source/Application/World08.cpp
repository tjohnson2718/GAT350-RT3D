#include "World08.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include <glm/glm/gtx/color_space.hpp>

namespace nc
{
    bool World08::Initialize()
    {
        m_scene = std::make_unique<Scene>();
        m_scene->Load("scenes/scene_editor.json");
        m_scene->Initialize();

        m_editor = std::make_unique<Editor>();

        //create depth texture
        auto texture = std::make_shared<Texture>();
        texture->CreateDepthTexture(1024, 1024);
        ADD_RESOURCE("depth_texture", texture);

        // create depth buffer
        auto framebuffer = std::make_shared<Framebuffer>();
        framebuffer->CreateDepthbuffer(texture);
        ADD_RESOURCE("depth_buffer", framebuffer);

        // set depth texture to debug sprite
        auto material = GET_RESOURCE(Material, "materials/sprite.mtrl");
        if (material)
        {
            material->albedoTexture = texture;
        }

        
        auto materials = GET_RESOURCES(Material);
        for (auto material : materials)
        {
            material->depthTexture = texture;
        }
        

        return true;
    }

    void World08::Shutdown()
    {
    }

    void World08::Update(float dt)
    {
        ENGINE.GetSystem<Gui>()->BeginFrame();
        m_scene->Update(dt);
        m_editor->ProcessGui(m_scene.get());
        m_editor->Update();

        ENGINE.GetSystem<Gui>()->EndFrame();

        //ImGui::Begin("Cel");
        //ImGui::SliderInt("Levels", &m_celLevels, 1, 8);

    }

    void World08::Draw(Renderer& renderer)
    {
        // ** Pass 1 **
        auto framebuffer = GET_RESOURCE(Framebuffer, "depth_buffer");
        renderer.SetViewport(framebuffer->GetSize().x, framebuffer->GetSize().y);
        framebuffer->Bind();

        renderer.ClearDepth();
        auto program = GET_RESOURCE(Program, "shaders/shadow_depth.prog");
        program->Use();

        auto lights = m_scene->GetComponents<LightComponent>();
        for (auto light : lights)
        {
            if (light->castShadow)
            {
                glm::mat4 shadowMatrix = light->GetShadowMatrix();
                program->SetUniform("shadowVP", shadowMatrix);
            }
        }

        auto models = m_scene->GetComponents<ModelComponent>();
        for (auto model : models)
        {
            glCullFace(GL_FRONT);
            program->SetUniform("model", model->m_owner->transform.GetMatrix());
            model->model->Draw();
        }

        framebuffer->Unbind();
        

        // *** PASS 2 ***
        renderer.ResetViewport();
        renderer.BeginFrame();
        m_scene->Draw(renderer);

        // post-render
        ENGINE.GetSystem<Gui>()->Draw();
        renderer.EndFrame();
    }
}
