#include "World03.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"

#define INTERLEAVE

namespace nc
{
    bool World03::Initialize()
    {
        m_program = GET_RESOURCE(Program, "shaders/unlit_color.prog");
        m_program->Use();
        
#ifdef INTERLEAVE
        float vertexData[] = {
           -0.8f, -0.8f, 0.0f, 1.0f, -0.3f, -0.1f,
            -0.8f, 0.8f, 0.0f,  -1.0f, 0.0f, 0.5f,
            0.0f, -0.8f, 0.0f, 0.0f, 1.0f, 1.0f,
            0.0f,  0.8f, 0.0f, 0.0f, 0.0f, 0.3f
        };

        GLuint vbo;
        glGenBuffers(1, &vbo);

        // position 1
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glBindVertexBuffer(0, vbo, 0, sizeof(GLfloat) * 6);

        // position 1
        glEnableVertexAttribArray(0);
        glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexAttribBinding(0, 0);

        // color 1
        glEnableVertexAttribArray(1);
        glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat));
        glVertexAttribBinding(1, 0);
#else
        float positionData1[] = {
           -0.8f, -0.8f, 0.0f,
           -0.8f, 0.8f, 0.0f,
            0.0f, -0.8f, 0.0f,
            0.0f,  0.8f, 0.0f
        };

        float colorData1[] =
        {
            1.0f, 0.5f, 0.3f,
            0.7f, -1.0f, 0.5f,
            0.8f, 0.8f, 0.8f,
            1.0f, 1.0f, 0.0f
        };

        GLuint vbo[2];
        glGenBuffers(2, vbo);

        // position 1
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positionData1), positionData1, GL_STATIC_DRAW);

        // color 1
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colorData1), colorData1, GL_STATIC_DRAW);


        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        // position 1
        glEnableVertexAttribArray(0);
        glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
        glBindVertexBuffer(0, vbo[0], 0, sizeof(GLfloat) * 3);
        glVertexAttribBinding(0, 0);

        // color 1
        glEnableVertexAttribArray(1);
        glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 0);
        glBindVertexBuffer(1, vbo[1], 0, sizeof(GLfloat) * 3);
        glVertexAttribBinding(1, 1);
#endif
        return true;
    }

    void World03::Shutdown()
    {
    }

    void World03::Update(float dt)
    {
        m_angle += 90 * dt;
        m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_A) ? -dt : 0;
        m_position.x += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_D) ? dt : 0;

        m_position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_S) ? -dt : 0;
        m_position.y += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_W) ? dt : 0;

        m_angle += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_Q) ? -dt * 90 : 0;
        m_angle += ENGINE.GetSystem<InputSystem>()->GetKeyDown(SDL_SCANCODE_E) ? dt * 90 : 0;
       
        m_time += dt;

        GLint uniform = glGetUniformLocation(m_program->m_program, "time");
        glUniform1f(uniform, m_time);
    }

    void World03::Draw(Renderer& renderer)
    {
        // pre-render
        renderer.BeginFrame();

        // render
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        // post-render
        renderer.EndFrame();
    }
}
