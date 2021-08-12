#include "Box.h"
#include <iostream>

Box::Box(glm::vec3 pos, float s)
{
	float x = pos.x;
	float y = pos.y;
	float z = pos.z;
	Size = s - 0.001;
	Position = pos;

	// vert pos
	v.push_back(glm::vec3(x + s, y - s, z - s));
	v.push_back(glm::vec3(x + s, y + s, z - s));
	v.push_back(glm::vec3(x + s, y + s, z + s));
	v.push_back(glm::vec3(x + s, y - s, z + s));
	v.push_back(glm::vec3(x - s, y - s, z - s));
	v.push_back(glm::vec3(x - s, y - s, z + s));
	v.push_back(glm::vec3(x - s, y + s, z + s));
	v.push_back(glm::vec3(x - s, y + s, z - s));
	Convert();
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
		v.at(0),
		v.at(1),
		v.at(3)
	);
	glColor4f(normal.x, normal.y, normal.z, 1);
	glVertex3f(v.at(0).x, v.at(0).y, v.at(0).z);
	glVertex3f(v.at(1).x, v.at(1).y, v.at(1).z);
	glVertex3f(v.at(3).x, v.at(3).y, v.at(3).z);
	glVertex3f(v.at(1).x, v.at(1).y, v.at(1).z);
	glVertex3f(v.at(2).x, v.at(2).y, v.at(2).z);
	glVertex3f(v.at(3).x, v.at(3).y, v.at(3).z);
	glNormal3f(normal.x, normal.y, normal.z);

	normal = CalcNormal
	(
		v.at(3),
		v.at(2),
		v.at(5)
	);
	glColor4f(normal.x, normal.y, normal.z, 1);
	glVertex3f(v.at(3).x, v.at(3).y, v.at(3).z);
	glVertex3f(v.at(2).x, v.at(2).y, v.at(2).z);
	glVertex3f(v.at(5).x, v.at(5).y, v.at(5).z);
	glVertex3f(v.at(2).x, v.at(2).y, v.at(2).z);
	glVertex3f(v.at(6).x, v.at(6).y, v.at(6).z);
	glVertex3f(v.at(5).x, v.at(5).y, v.at(5).z);
	glNormal3f(normal.x, normal.y, normal.z);

	normal = CalcNormal
	(
		v.at(4),
		v.at(0),
		v.at(5)
	);
	glColor4f(normal.x, normal.y, normal.z, 1);
	glVertex3f(v.at(4).x, v.at(4).y, v.at(4).z);
	glVertex3f(v.at(0).x, v.at(0).y, v.at(0).z);
	glVertex3f(v.at(5).x, v.at(5).y, v.at(5).z);
	glVertex3f(v.at(5).x, v.at(5).y, v.at(5).z);
	glVertex3f(v.at(0).x, v.at(0).y, v.at(0).z);
	glVertex3f(v.at(3).x, v.at(3).y, v.at(3).z);
	glNormal3f(normal.x, normal.y, normal.z);

	normal = CalcNormal
	(
		v.at(1),
		v.at(7),
		v.at(6)
	);
	glColor4f(normal.x, normal.y, normal.z, 1);
	glVertex3f(v.at(1).x, v.at(1).y, v.at(1).z);
	glVertex3f(v.at(7).x, v.at(7).y, v.at(7).z);
	glVertex3f(v.at(6).x, v.at(6).y, v.at(6).z);
	glVertex3f(v.at(1).x, v.at(1).y, v.at(1).z);
	glVertex3f(v.at(6).x, v.at(6).y, v.at(6).z);
	glVertex3f(v.at(2).x, v.at(2).y, v.at(2).z);
	glNormal3f(normal.x, normal.y, normal.z);

	normal = CalcNormal
	(
		v.at(7),
		v.at(4),
		v.at(5)
	);
	glColor4f(normal.x, normal.y, normal.z, 1);
	glVertex3f(v.at(7).x, v.at(7).y, v.at(7).z);
	glVertex3f(v.at(4).x, v.at(4).y, v.at(4).z);
	glVertex3f(v.at(5).x, v.at(5).y, v.at(5).z);
	glVertex3f(v.at(7).x, v.at(7).y, v.at(7).z);
	glVertex3f(v.at(5).x, v.at(5).y, v.at(5).z);
	glVertex3f(v.at(6).x, v.at(6).y, v.at(6).z);
	glNormal3f(normal.x, normal.y, normal.z);

	normal = CalcNormal
	(
		v.at(7),
		v.at(1),
		v.at(0)
	);
	glColor4f(normal.x, normal.y, normal.z, 1);
	glVertex3f(v.at(7).x, v.at(7).y, v.at(7).z);
	glVertex3f(v.at(1).x, v.at(1).y, v.at(1).z);
	glVertex3f(v.at(0).x, v.at(0).y, v.at(0).z);
	glVertex3f(v.at(7).x, v.at(7).y, v.at(7).z);
	glVertex3f(v.at(0).x, v.at(0).y, v.at(0).z);
	glVertex3f(v.at(4).x, v.at(4).y, v.at(4).z);
	glNormal3f(normal.x, normal.y, normal.z);

	glEnd();
	glPopMatrix();
}

void Box::Convert()
{
	Vertices.push_back(v.at(0) + Position);
	Vertices.push_back(v.at(1) + Position);
	Vertices.push_back(v.at(3) + Position);
	Vertices.push_back(v.at(1) + Position);
	Vertices.push_back(v.at(2) + Position);
	Vertices.push_back(v.at(3) + Position);

	Vertices.push_back(v.at(3) + Position);
	Vertices.push_back(v.at(2) + Position);
	Vertices.push_back(v.at(5) + Position);
	Vertices.push_back(v.at(2) + Position);
	Vertices.push_back(v.at(6) + Position);
	Vertices.push_back(v.at(5) + Position);

	Vertices.push_back(v.at(4) + Position);
	Vertices.push_back(v.at(0) + Position);
	Vertices.push_back(v.at(5) + Position);
	Vertices.push_back(v.at(5) + Position);
	Vertices.push_back(v.at(0) + Position);
	Vertices.push_back(v.at(3) + Position);

	Vertices.push_back(v.at(1) + Position);
	Vertices.push_back(v.at(7) + Position);
	Vertices.push_back(v.at(6) + Position);
	Vertices.push_back(v.at(1) + Position);
	Vertices.push_back(v.at(6) + Position);
	Vertices.push_back(v.at(2) + Position);

	Vertices.push_back(v.at(7) + Position);
	Vertices.push_back(v.at(4) + Position);
	Vertices.push_back(v.at(5) + Position);
	Vertices.push_back(v.at(7) + Position);
	Vertices.push_back(v.at(5) + Position);
	Vertices.push_back(v.at(6) + Position);

	Vertices.push_back(v.at(7) + Position);
	Vertices.push_back(v.at(1) + Position);
	Vertices.push_back(v.at(0) + Position);
	Vertices.push_back(v.at(7) + Position);
	Vertices.push_back(v.at(0) + Position);
	Vertices.push_back(v.at(4) + Position);

	for (int i = 0; i < 6; ++i)
	Normals.push_back(CalcNormal
	(
		v.at(0),
		v.at(1),
		v.at(3)
	));
	for (int i = 0; i < 6; ++i)
	Normals.push_back(CalcNormal
	(
		v.at(3),
		v.at(2),
		v.at(5)
	));
	for (int i = 0; i < 6; ++i)
	Normals.push_back(CalcNormal
	(
		v.at(4),
		v.at(0),
		v.at(5)
	));
	for (int i = 0; i < 6; ++i)
	Normals.push_back(CalcNormal
	(
		v.at(1),
		v.at(7),
		v.at(6)
	));
	for (int i = 0; i < 6; ++i)
	Normals.push_back(CalcNormal
	(
		v.at(7),
		v.at(4),
		v.at(5)
	));
	for (int i = 0; i < 6; ++i)
	Normals.push_back(CalcNormal
	(
		v.at(7),
		v.at(1),
		v.at(0)
	));
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
				if (check > 1) 
				{
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
