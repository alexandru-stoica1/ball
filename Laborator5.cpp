#include "Laborator5.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "Object2D.h"
#include "Transform2D.h"
using namespace std;

Laborator5::Laborator5()
{
}

Laborator5::~Laborator5()
{
}

void Laborator5::Init()
{
	renderCameraTarget = false;

	camera = new Laborator::Camera();
	camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* dr1 = Object2D::Drept("dr1", glm::vec3(1, 1, 1));
		AddMeshToList(dr1);
		Mesh* dr2 = Object2D::Drept("dr2", glm::vec3(0, 1, 0));
		AddMeshToList(dr2);
	}
	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Shader* shader = new Shader("Shader");
		shader->AddShader("Source/Laboratoare/Laborator5/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Laborator5/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}

void Laborator5::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.68, 0.84, 0.92, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator5::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	// render an object using the specified shader and the specified position
	//glUseProgram(shader->program);

	glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));

	// Draw the object
	mesh->Render();
}

void Laborator5::Update(float deltaTimeSeconds)
{
	if (camera1 == 1)
	{
		camera->Set(glm::vec3(move_sphere, up_position + 0.2f, -0.5f), glm::vec3(move_sphere, up_position, -2), glm::vec3(0, 1, 0));
	}
	else
	{
		camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
	}

	for (int i = 0; i < n; i++)
	{
		if (fast == 2000)
		{
			fast = 0;
		}

		if (fast != 0)
		{
			speed[i] += 0.2f;
			fast++;
		}
		
		if (fast == 0)
		{
			if (speed_up_down == 2)
				speed[i] += 0.1f;
			if (speed_up_down == 1)
				speed[i] += 0.05f;
			if (speed_up_down == 3)
				speed[i] += 0.2f;
		}
	}

	int k = 0;
	
	for (int i = 0; i < n; i++)
	{
		if (z_platforme[i] + speed[i] - 5 >= 1.5f)
		{
			int minim = z_platforme[0] + speed[0] - 5;

			for (int j = 0; j < n; j++)
			{
				if (z_platforme[j] + speed[j] - 5 < minim)
				{
					minim = z_platforme[j] + speed[j] - 5;
				}
			}
			z_platforme[i] = -(rand() % 2 + std::abs(minim) + 1);
			speed[i] = 0;

			int random = rand() % 20;

			if (random == 10 && i >= 1 && colors[i - 1] != 2)
			{
				colors[i] = 2;
				prev_color[i] = 2;
			}
			
			else if (random == 12)
			{
				colors[i] = 3;
				prev_color[i] = 3;
			}
			
			else if (random == 15)
			{
				colors[i] = 4;
				prev_color[i] = 4;
			}
			
			else if (random == 8 || random == 5 || random == 14 || random == 6 || random == 2)
			{
				colors[i] = 5;
				prev_color[i] = 5;
			}
			
			else
			{
				colors[i] = 1;
				prev_color[i] = 1;
			}
		}
					
		if (i % 3 == 0)
		{
			x[i] = 0;
		}
		else if (i % 3 == 1)
		{
			x[i] = 1.5f;
		}
		else
		{
			x[i] = -1.5f;
		}

		glm::vec3 color;
		//albastru
		if (colors[i] == 1)
		{
			color = glm::vec3(0, 0, 1);
		}
		//rosu
		else if (colors[i] == 2)
		{
			color = glm::vec3(1, 0, 0);
		}
		//galben
		else if (colors[i] == 3)
		{
			color = glm::vec3(1, 1, 0);
		}
		//portocaliu
		else if (colors[i] == 4)
		{
			color = glm::vec3(1, 0.64, 0);
		}
		//verde
		else if (colors[i] == 5)
		{
			color = glm::vec3(0, 1, 0);
		}

		if (coliziune[i] == 1)
		{
			color = glm::vec3(1, 0, 1);
		}

		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, speed[i]));
		modelMatrix = glm::translate(modelMatrix, glm::vec3(x[i], 0, z_platforme[i]));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1, 0.1f, 10));

		// Attention! The RenderMesh function overrides the usual RenderMesh that we used until now
		// It uses the viewMatrix from Laborator::Camera instance and the local projectionMatrix
		RenderSimpleMesh(meshes["box"], shaders["Shader"], modelMatrix, color);
	}

	if (jump == 1)
	{
		if (jump_up == 1)
		{
			v_init -= 9.81 * deltaTimeSeconds;
			up_position += v_init * deltaTimeSeconds + (9.81f * deltaTimeSeconds * deltaTimeSeconds) / 2;
		}

		if (up_position < 0.1f)
		{
			jump = 0;
			jump_up = 0;
			v_init = 5;
		}
	}
	
	if (jump == 0 && up_position >= 0)
	{
		for (int i = 0; i < n; i++)
		{
			if (z_platforme[i] + speed[i] - 5 < 0 && z_platforme[i] + speed[i] + 5 >= 0)
			{
				if (x[i] == 0 && move_sphere <= 0.5f && move_sphere >= -0.5f)
				{
					coliziune[i] = 1;
					
					if (prev_color[i] == 2)
					{
						cout << "GAME OVER!";
						exit(0);
					}

					if (prev_color[i] == 3)
					{
						fuel -= 0.01f;
					}

					if (prev_color[i] == 4)
					{
						fast++;
					}

					if ((prev_color[i] == 5 || prev_color[i] == 14 || prev_color[i] == 6 || prev_color[i] == 2) && fuel <= 1)
					{
						fuel += 0.01f;
					}
				}
				else if (x[i] == -1.5f && move_sphere <= -1 && move_sphere >= -2)
				{
					coliziune[i] = 1;

					if (prev_color[i] == 2)
					{
						cout << "GAME OVER!";
						exit(0);
					}

					if (prev_color[i] == 3)
					{
						fuel -= 0.01f;
					}

					if (prev_color[i] == 4)
					{
						fast++;
					}

					if ((prev_color[i] == 5 || prev_color[i] == 14 || prev_color[i] == 6 || prev_color[i] == 2) && fuel <= 1)
					{
						fuel += 0.01f;
					}
				}
				else if (x[i] == 1.5f && move_sphere <= 2 && move_sphere >= 1)
				{
					coliziune[i] = 1;

					if (prev_color[i] == 2)
					{
						cout << "GAME OVER!";
						exit(0);
					}

					if (prev_color[i] == 3)
					{
						fuel -= 0.01f;
					}

					if (prev_color[i] == 4)
					{
						fast++;
					}

					if ((prev_color[i] == 5 || prev_color[i] == 14 || prev_color[i] == 6 || prev_color[i] == 2) && fuel <= 1)
					{
						fuel += 0.01f;
					}
				}
				else
				{
					coliziune[i] = 0;
				}
			}
			else
			{
				coliziune[i] = 0;
			}
		}
	}

	if (jump == 1)
	{
		for (int i = 0; i < 6; i++)
		{
			coliziune[i] = 0;
		}
	}

	out = 0;
	for (int i = 0; i < n; i++)
	{
		if (coliziune[i] == 1 || jump == 1)
		{
			out = 1;
		}
	}

	if (out == 0)
	{
		up_position -= 0.1f;
	}

	if (up_position < -0.5f)
	{
		cout << "GAME OVER!";
		exit(0);
	}

	glm::mat4 modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(move_sphere, up_position, 0));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.3f, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
	RenderSimpleMesh(meshes["sphere"], shaders["Shader"], modelMatrix, sphere_color);
	
	if (speed_up_down == 2)
		fuel -= 0.0005f;
	if (speed_up_down == 1)
		fuel -= 0.0003f;
	if (speed_up_down == 3)
		fuel -= 0.0007f;

	if (fuel < 0)
	{	
		cout << "GAME OVER!";
		exit(0);
	}

	model_Matrix = glm::mat3(1);
	model_Matrix *= Transform2D::Translate(-2.3f, 0);
	model_Matrix *= Transform2D::Scale(fuel, 1);
	RenderMesh2D(meshes["dr2"], shaders["VertexColor"], model_Matrix);

	model_Matrix = glm::mat3(1);
	model_Matrix *= Transform2D::Translate(-2.3f, 0);
	RenderMesh2D(meshes["dr1"], shaders["VertexColor"], model_Matrix);
}

void Laborator5::FrameEnd()
{

}

void Laborator5::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator5::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_A))
	{
		move_sphere -= 0.1f;
	}

	if (window->KeyHold(GLFW_KEY_D))
	{
		move_sphere += 0.1f;
	}
}

void Laborator5::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_T)
	{
		renderCameraTarget = !renderCameraTarget;
	}

	if (key == GLFW_KEY_C)
	{
		if (camera1 == 0)
		{
			camera1 = 1;
		}

		else
		{
			camera1 = 0;
		}
	}

	if (key == GLFW_KEY_W && speed_up_down < 3)
	{
		speed_up_down++;
	}

	if (key == GLFW_KEY_S && speed_up_down > 1)
	{
		speed_up_down -= 1;
	}

	if (key == GLFW_KEY_SPACE)
	{
		jump = 1;
		jump_up = 1;
	}
}

void Laborator5::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator5::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
		}

	}
}

void Laborator5::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator5::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator5::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator5::OnWindowResize(int width, int height)
{
}
