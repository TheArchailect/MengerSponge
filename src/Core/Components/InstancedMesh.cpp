#include "InstancedMesh.h"

InstancedMesh::InstancedMesh(std::vector<Vertex> v, std::vector<unsigned int> i)
{
    m_Instances = 9;
    m_Verts = v;
    m_Indices = i;
    m_Transforms = new glm::mat4[m_Instances];
    m_Position = glm::vec3(0, 0, 0);
    m_Rotation = glm::vec3(0, 0, 0);
    {
        int idx = 0;
        int offset = 35;
        for (int x = -1; x < 2; ++x)
        {
            for (int y = -1; y < 2; ++y)
            {
                m_Transforms[idx] = glm::translate(glm::mat4(1.0f), glm::vec3(x * offset, y * offset, 0));
                idx++;
            }
        }
    }
    SetupMesh(); 
}

void InstancedMesh::DrawInstanced()
{
    glBindVertexArray(VAO);
    glDrawElementsInstanced(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, (void*)0, m_Instances);
}

void InstancedMesh::Update()
{
    int z = 0;
    int idx = 0;
    int offset = 35;
    glm::vec3 rot[9];
    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            rot[x + y] = glm::vec3(x, y, 1);
        }
    }
    for (int x = -1; x < 2; ++x)
    {
        for (int y = -1; y < 2; ++y)
        {
            m_Transforms[idx] = glm::rotate
            (
                glm::translate(glm::mat4(1.0f), glm::vec3(x * offset, y * offset, 0)),
                glm::radians((SDL_GetTicks() / 100.0f)),
                rot[idx]
            );
            idx++;
        }
    }
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, MBO);
    glBufferData
    (
        GL_ARRAY_BUFFER,
        m_Instances * sizeof(glm::mat4),
        &m_Transforms[0],
        GL_STATIC_DRAW
    );
}

int InstancedMesh::GetElementCount()
{
    return m_Indices.size();
}

void InstancedMesh::SetupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData
    (
        GL_ARRAY_BUFFER, 
        m_Verts.size() * sizeof(Vertex), 
        m_Verts.data(), 
        GL_STATIC_DRAW
    );
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData
    (
        GL_ELEMENT_ARRAY_BUFFER,
        m_Indices.size() * sizeof(unsigned int),
        &m_Indices[0], GL_STATIC_DRAW
    );
    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // model matrix buffer
    glBindVertexArray(VAO);
    glGenBuffers(1, &MBO);
    glBindBuffer(GL_ARRAY_BUFFER, MBO);
    glBufferData
    (
        GL_ARRAY_BUFFER, 
        m_Instances * sizeof(glm::mat4), 
        &m_Transforms[0], 
        GL_STATIC_DRAW
    );
    // model matrix attributes
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
    glVertexAttribDivisor(1, 1);
    glVertexAttribDivisor(2, 1);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
}
