#include "Box.h"
#include <iostream>

Box::Box(glm::vec3 pos, float s)
{
	float x = pos.x;
	float y = pos.y;
	float z = pos.z;
	Size = s;
	Position = pos;

	// vert pos
	v.push_back(Vertex(glm::vec3(x + s, y - s, z - s)));
	v.push_back(Vertex(glm::vec3(x + s, y + s, z - s)));
	v.push_back(Vertex(glm::vec3(x + s, y + s, z + s)));
	v.push_back(Vertex(glm::vec3(x + s, y - s, z + s)));
	v.push_back(Vertex(glm::vec3(x - s, y - s, z - s)));
	v.push_back(Vertex(glm::vec3(x - s, y - s, z + s)));
	v.push_back(Vertex(glm::vec3(x - s, y + s, z + s)));
	v.push_back(Vertex(glm::vec3(x - s, y + s, z - s)));
}

void Box::Draw()
{
	GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat shininess[] = {5.0};
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glPushMatrix();
	glTranslatef(Position.x, Position.y, Position.z);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);

	glm::vec3 normal = CalcNormal
	(
		v.at(0).Position,
		v.at(1).Position,
		v.at(3).Position
	);
	glColor4f(normal.x, normal.y, normal.z, 1);
	glVertex3f(v.at(0).Position.x, v.at(0).Position.y, v.at(0).Position.z);
	glVertex3f(v.at(1).Position.x, v.at(1).Position.y, v.at(1).Position.z);
	glVertex3f(v.at(3).Position.x, v.at(3).Position.y, v.at(3).Position.z);
	glVertex3f(v.at(1).Position.x, v.at(1).Position.y, v.at(1).Position.z);
	glVertex3f(v.at(2).Position.x, v.at(2).Position.y, v.at(2).Position.z);
	glVertex3f(v.at(3).Position.x, v.at(3).Position.y, v.at(3).Position.z);
	glNormal3f(normal.x, normal.y, normal.z);

	normal = CalcNormal
	(
		v.at(3).Position,
		v.at(2).Position,
		v.at(5).Position
	);
	glColor4f(normal.x, normal.y, normal.z, 1);
	glVertex3f(v.at(3).Position.x, v.at(3).Position.y, v.at(3).Position.z);
	glVertex3f(v.at(2).Position.x, v.at(2).Position.y, v.at(2).Position.z);
	glVertex3f(v.at(5).Position.x, v.at(5).Position.y, v.at(5).Position.z);
	glVertex3f(v.at(2).Position.x, v.at(2).Position.y, v.at(2).Position.z);
	glVertex3f(v.at(6).Position.x, v.at(6).Position.y, v.at(6).Position.z);
	glVertex3f(v.at(5).Position.x, v.at(5).Position.y, v.at(5).Position.z);
	glNormal3f(normal.x, normal.y, normal.z);

	normal = CalcNormal
	(
		v.at(4).Position,
		v.at(0).Position,
		v.at(5).Position
	);
	glColor4f(normal.x, normal.y, normal.z, 1);
	glVertex3f(v.at(4).Position.x, v.at(4).Position.y, v.at(4).Position.z);
	glVertex3f(v.at(0).Position.x, v.at(0).Position.y, v.at(0).Position.z);
	glVertex3f(v.at(5).Position.x, v.at(5).Position.y, v.at(5).Position.z);
	glVertex3f(v.at(5).Position.x, v.at(5).Position.y, v.at(5).Position.z);
	glVertex3f(v.at(0).Position.x, v.at(0).Position.y, v.at(0).Position.z);
	glVertex3f(v.at(3).Position.x, v.at(3).Position.y, v.at(3).Position.z);
	glNormal3f(normal.x, normal.y, normal.z);

	normal = CalcNormal
	(
		v.at(1).Position,
		v.at(7).Position,
		v.at(6).Position
	);
	glColor4f(normal.x, normal.y, normal.z, 1);
	glVertex3f(v.at(1).Position.x, v.at(1).Position.y, v.at(1).Position.z);
	glVertex3f(v.at(7).Position.x, v.at(7).Position.y, v.at(7).Position.z);
	glVertex3f(v.at(6).Position.x, v.at(6).Position.y, v.at(6).Position.z);
	glVertex3f(v.at(1).Position.x, v.at(1).Position.y, v.at(1).Position.z);
	glVertex3f(v.at(6).Position.x, v.at(6).Position.y, v.at(6).Position.z);
	glVertex3f(v.at(2).Position.x, v.at(2).Position.y, v.at(2).Position.z);
	glNormal3f(normal.x, normal.y, normal.z);

	normal = CalcNormal
	(
		v.at(7).Position,
		v.at(4).Position,
		v.at(5).Position
	);
	glColor4f(normal.x, normal.y, normal.z, 1);
	glVertex3f(v.at(7).Position.x, v.at(7).Position.y, v.at(7).Position.z);
	glVertex3f(v.at(4).Position.x, v.at(4).Position.y, v.at(4).Position.z);
	glVertex3f(v.at(5).Position.x, v.at(5).Position.y, v.at(5).Position.z);
	glVertex3f(v.at(7).Position.x, v.at(7).Position.y, v.at(7).Position.z);
	glVertex3f(v.at(5).Position.x, v.at(5).Position.y, v.at(5).Position.z);
	glVertex3f(v.at(6).Position.x, v.at(6).Position.y, v.at(6).Position.z);
	glNormal3f(normal.x, normal.y, normal.z);

	normal = CalcNormal
	(
		v.at(7).Position,
		v.at(1).Position,
		v.at(0).Position
	);
	glColor4f(normal.x, normal.y, normal.z, 1);
	glVertex3f(v.at(7).Position.x, v.at(7).Position.y, v.at(7).Position.z);
	glVertex3f(v.at(1).Position.x, v.at(1).Position.y, v.at(1).Position.z);
	glVertex3f(v.at(0).Position.x, v.at(0).Position.y, v.at(0).Position.z);
	glVertex3f(v.at(7).Position.x, v.at(7).Position.y, v.at(7).Position.z);
	glVertex3f(v.at(0).Position.x, v.at(0).Position.y, v.at(0).Position.z);
	glVertex3f(v.at(4).Position.x, v.at(4).Position.y, v.at(4).Position.z);
	glNormal3f(normal.x, normal.y, normal.z);

	glEnd();
	glPopMatrix();
}

std::vector<Box*> Box::Generate() // 27 boxes sub-d
{
	std::vector<Box*> boxes;
	for (int x = -1; x < 2; ++x)
	{
		for (int y = -1; y < 2; ++y)
		{
			for (int z = -1; z < 2; ++z)
			{
				int check = abs(x) + abs(y) + abs(z);
				if (check > 1) {
					float s = (Size / 3);
					float newx = Position.x + x * s;
					float newy = Position.y + y * s;
					float newz = Position.z + z * s;
					Box* b = new Box(glm::vec3(newx, newy, newz), s);
					boxes.push_back(b);
				}
			}
		}
	}
	return boxes;
}

glm::vec3 Box::CalcNormal(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	glm::vec3 A = p2 - p1;
	glm::vec3 B = p3 - p1;
	return glm::normalize(glm::cross(A, B));
}
