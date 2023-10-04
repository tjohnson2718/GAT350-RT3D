#include "World01.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"

namespace nc
{
    bool World01::Initialize()
    {
      /*  for (int i = 0; i <= 10; i++)
        {
            m_positions.push_back({ randomf(-1,1), randomf(-1,1) });
        }*/

        return true;
    }

    void World01::Shutdown()
    {
    }

    void World01::Update(float dt)
    {
        m_angle += 90 * dt;
        m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? -dt : 0;
        m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? dt : 0;

        m_position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? -dt : 0;
        m_position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? dt : 0;

        m_angle += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_Q) ? -dt * 90 : 0;
        m_angle += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_E) ? dt * 90 : 0;
       
        m_time += dt;
    }

    void World01::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();

        // render  
        glPushMatrix();
        glTranslatef(m_position.x, m_position.y, 0);
        glRotatef(m_angle, 1, 1, 1);
        glScalef(sin(m_time * 5) * 0.5f, 1, 1);

        glBegin(GL_TRIANGLES);

        glColor3f(1, 0, 0);
        glVertex2f(-0.5f, -0.5f);

        glColor3f(0, 1, 0);
        glVertex2f(0.0f, 0.5f);

        glColor3f(0, 0, 1);
        glVertex2f(0.5f, -0.5f);

        glEnd();
        glPopMatrix();

        //Pumpkin Body
        glPushMatrix();

        glBegin(GL_TRIANGLE_FAN);

        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex2f(0.0f, 0.0f);

        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex2f(-0.7f, -0.9f);
        
        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex2f(-0.9f, 0.0f);

        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex2f(0.0f, 0.8f);

        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex2f(0.9f, 0.0f);

        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex2f(0.7f, -0.9f);

        glEnd();
        glPopMatrix();

        glPushMatrix();

        glBegin(GL_TRIANGLES);

        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex2f(0.0f, 0.0f);

        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex2f(-0.7f, -0.9f);

        glColor3f(1.0f, 0.5f, 0.0f);
        glVertex2f(0.7f, -0.9f);

        glEnd();
        glPopMatrix();

        // Pumpkin Eyes
        glPushMatrix();

        glBegin(GL_TRIANGLES);

        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.5f, 0.1f);

        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.3f, 0.4f);

        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.1f, 0.1f);

        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.1f, 0.1f);

        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.3f, 0.4f);

        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.5f, 0.1f);

        glEnd();
        glPopMatrix();

        // Nose
        glPushMatrix();

        glBegin(GL_TRIANGLES);

        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.1f, -0.3f);

        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.0f, -0.1f);

        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.1f, -0.3f);

        glEnd();
        glPopMatrix();

        //Mouth 
        glPushMatrix();

        glBegin(GL_QUADS);

        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.4f, -0.4f);

        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.4f, -0.4f);

        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.3f, -0.8f);

        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.3f, -0.8f);

        glEnd();
        glPopMatrix();
        
        //Stem
        glPushMatrix();

        glBegin(GL_QUADS);

        glColor3f(0.0f, 0.1f, 0.0f);
        glVertex2f(-0.1f, 1.0f);

        glColor3f(0.0f, 0.1f, 0.0f);
        glVertex2f(0.1f, 1.0f);

        glColor3f(0.0f, 0.1f, 0.0f);
        glVertex2f(0.2f, 0.65f);

        glColor3f(0.0f, 0.1f, 0.0f);
        glVertex2f(-0.2f, 0.65f);

        glEnd();
        glPopMatrix();
        // post-render
        renderer.EndFrame();
    }
}
