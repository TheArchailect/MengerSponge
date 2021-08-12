#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> v, std::vector<unsigned int> i)
{
    this->m_Verts = v;
    this->m_Indices = i;
    SetupMesh();
    m_Position = glm::vec3(0, 0, 0);
    m_Rotation = glm::vec3(0, 0, 0);
    m_Transform = glm::mat4(1.0f);
    m_Transform = glm::rotate
    (
        m_Transform,
        glm::radians(25.0f),
        glm::vec3(0.0f, 0.0f, 0.0f)
    );
}

void Mesh::SetupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_Verts.size() * sizeof(Vertex), m_Verts.data(), GL_STATIC_DRAW);

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
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
}

void Mesh::Draw(GLenum ShaderPrimitive)
{
    glBindVertexArray(VAO);
    glDrawElements(ShaderPrimitive, m_Indices.size(), GL_UNSIGNED_INT, 0);
    //glDrawArrays(ShaderPrimitive, 0, m_Verts.size());
}

void Mesh::DrawLegacy()
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat shininess[] = { 5.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glPushMatrix();
    //glTranslatef(Position.x, Position.y, Position.z);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < m_Indices.size(); ++i)
    {
        glVertex3f
        (
            m_Verts.at(m_Indices.at(i)).Position.x,
            m_Verts.at(m_Indices.at(i)).Position.y,
            m_Verts.at(m_Indices.at(i)).Position.z
        );
    }
    glEnd();
    glPopMatrix();
}

void Mesh::Update()
{
    m_Transform = glm::mat4(1.0f);
    m_Transform = glm::translate(m_Transform, m_Position);
    m_Transform = glm::rotate(m_Transform, m_Rotation.x, glm::vec3(1, 0, 0));
    m_Transform = glm::rotate(m_Transform, m_Rotation.y, glm::vec3(0, 1, 0));
    m_Transform = glm::rotate(m_Transform, m_Rotation.z, glm::vec3(0, 0, 1));
}

glm::mat4 Mesh::GetTransform()
{
	return m_Transform;
}