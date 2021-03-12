#include "Object2D.h"

#include <Core/Engine.h>
#include <iostream>

Mesh* Object2D::Drept(std::string name, glm::vec3 color)
{

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-2.32f, 2.3f, 0), color),
		VertexFormat(glm::vec3(-2.32f, 2.2f, 0), color),
		VertexFormat(glm::vec3(2, 2.2f, 0), color),
		VertexFormat(glm::vec3(2, 2.3f, 0), color)
	};

	Mesh* arrow = new Mesh(name);
	std::vector<unsigned short> indices = 
	{ 
		0, 1, 2,
		0, 2, 3,
	};

	arrow->InitFromData(vertices, indices);
	return arrow;
}

