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
        glm::radians(0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );
}

int Mesh::SelectMaterial(glm::vec3 n)
{

    if (abs(n.x) > abs(n.y) && abs(n.x) > abs(n.z)) return 0;
    if (abs(n.y) > abs(n.x) && abs(n.y) > abs(n.z)) return 1;
    if (abs(n.z) > abs(n.y) && abs(n.z) > abs(n.x)) return 2;
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
    // vertex normals OR packing morph target positions into Vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
}


void Mesh::Draw(GLenum ShaderPrimitive)
{
    glBindVertexArray(VAO);
    glDrawElements(ShaderPrimitive, m_Indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::DrawLegacy(std::vector<Material*> mats)
{
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    for (int i = 5; i < m_Indices.size(); i += 6)
    {
        glm::vec3 n = CalcNormal
        (
            m_Verts.at(m_Indices.at(i - 2)).Position,
            m_Verts.at(m_Indices.at(i - 1)).Position,
            m_Verts.at(m_Indices.at(i )).Position
        );
        SetMaterial(*mats.at(SelectMaterial(n)));
        glNormal3f
        (
            n.x,
            n.y,
            n.z
        );
        // Tri 1
        glVertex3f
        (
            m_Verts.at(m_Indices.at(i - 2)).Position.x,
            m_Verts.at(m_Indices.at(i - 2)).Position.y,
            m_Verts.at(m_Indices.at(i - 2)).Position.z
        );
        glNormal3f
        (
            n.x,
            n.y,
            n.z
        );
        glVertex3f
        (
            m_Verts.at(m_Indices.at(i - 1)).Position.x,
            m_Verts.at(m_Indices.at(i - 1)).Position.y,
            m_Verts.at(m_Indices.at(i - 1)).Position.z
        );
        glNormal3f
        (
            n.x,
            n.y,
            n.z
        );
        glVertex3f
        (
            m_Verts.at(m_Indices.at(i)).Position.x,
            m_Verts.at(m_Indices.at(i)).Position.y,
            m_Verts.at(m_Indices.at(i)).Position.z
        );
        glNormal3f
        (
            n.x,
            n.y,
            n.z
        );
        // tri 2
        glVertex3f
        (
            m_Verts.at(m_Indices.at(i - 5)).Position.x,
            m_Verts.at(m_Indices.at(i - 5)).Position.y,
            m_Verts.at(m_Indices.at(i - 5)).Position.z
        );
        glNormal3f
        (
            n.x,
            n.y,
            n.z
        );
        glVertex3f
        (
            m_Verts.at(m_Indices.at(i - 4)).Position.x,
            m_Verts.at(m_Indices.at(i - 4)).Position.y,
            m_Verts.at(m_Indices.at(i - 4)).Position.z
        );
        glNormal3f
        (
            n.x,
            n.y,
            n.z
        );
        glVertex3f
        (
            m_Verts.at(m_Indices.at(i - 3)).Position.x,
            m_Verts.at(m_Indices.at(i - 3)).Position.y,
            m_Verts.at(m_Indices.at(i - 3)).Position.z
        );
        glNormal3f
        (
            n.x, 
            n.y, 
            n.z
        );
    }
    glEnd();
    glPopMatrix();
}

void Mesh::DrawInstanced(int n)
{
    glBindVertexArray(VAO);
    glDrawElementsInstanced(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, (void*)0, n);
}

void Mesh::Update()
{
    m_Transform = glm::mat4(1.0f);
    m_Transform = glm::translate(m_Transform, m_Position);
    m_Transform = glm::rotate(m_Transform, m_Rotation.x, glm::vec3(1, 0, 0));
    m_Transform = glm::rotate(m_Transform, m_Rotation.y, glm::vec3(0, 1, 0));
    m_Transform = glm::rotate(m_Transform, m_Rotation.z, glm::vec3(0, 0, 1));
}

void Mesh::SetMaterial(const Material& m)
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, m.Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m.Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m.Ks);
    glMaterialfv(GL_FRONT, GL_SHININESS, m.n);
}

glm::mat4 Mesh::GetTransform() const
{
	return m_Transform;
}

int Mesh::GetElementCount()
{
    return m_Indices.size();
}

glm::vec3 Mesh::CalcNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
    glm::vec3 A = p2 - p1;
    glm::vec3 B = p3 - p1;
    return glm::normalize(glm::cross(A, B));
}