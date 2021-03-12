#pragma once
#include <Component/SimpleScene.h>
#include "LabCamera.h"

class Laborator5 : public SimpleScene
{
	public:
		Laborator5();
		~Laborator5();

		void Init() override;
		glm::mat3 model_Matrix;
		float x[6];
		float z_platforme[6] = { -4.5f, -10, -20, -25, -35, -32 };
		float speed[6] = { 0, 0, 0, 0, 0, 0 };
		int n = 6;
		int speed_up_down = 2;
		int colors[6] = { 1, 1, 1, 1, 1, 1 };
		glm::vec3 sphere_color = glm::vec3(0.64, 1, 0.23);
		float move_sphere = 0;
		int jump = 0;
		float up_position = 0;
		int jump_up = 0;
		int jump_down = 0;
		int coliziune[6] = { 0, 0, 0, 0, 0, 0 };
		int prev_color[6] = { 1, 1, 1, 1, 1, 1 };
		float fuel = 1;
		int fast = 0;
		int out = 0;
		float v_init = 5;
		int camera1 = 0;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;
		void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		Laborator::Camera *camera;
		glm::mat4 projectionMatrix;
		bool renderCameraTarget;
};
