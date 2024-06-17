#include "titleScene.h"
#include "../Library/sceneManager.h"
#include "DebugScreen.h"
#include "../ImGui/imgui_impl_dxlib.hpp"

namespace {
	struct Circle
	{
		Circle() {}
		Circle(float _x , float _y , float _r) 
			: x{ _x}
			, y{ _y}
			, r{ _r} {}
		float x = 700, y = 500;
		float r = 5;
		ImVec4 clear_color = ImVec4(1.00f, 0.f, 0.f, 1.00f);
			void Draw() {
			unsigned int color = GetColor(255 * clear_color.x, 255 * clear_color.y, 255 * clear_color.z);
			DrawCircle(x, y, r, color);
		}
	};
	Circle cir1;
	Circle cir2(900,600,10);
	Circle cir3(500,200,50);
}

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	//çXêV
	ImGui::Begin("ImGui");
	ImGui::PushID("Circle1");
	if (ImGui::TreeNode("Circle1")) {

		static float vec[3];
		vec[0] = cir1.x;
		vec[1] = cir1.y;
		ImGui::InputFloat2("position", vec);
		ImGui::SliderFloat("r", &cir1.r, 1, 100);
		ImGui::ColorEdit3("clear color", (float*)&cir1.clear_color);

		cir1.x = vec[0];
		cir1.y = vec[1];

		ImGui::TreePop();
	}
	ImGui::PopID();
	ImGui::End();

	{
		ImGui::Begin("Circle2");
		ImGui::PushID("Circle2");
		static float vec[3];
		vec[0] = cir2.x;
		vec[1] = cir2.y;
		ImGui::InputFloat2("position", vec);
		ImGui::SliderFloat("r", &cir2.r, 1, 100);
		ImGui::ColorEdit3("clear color", (float*)&cir2.clear_color);

		cir2.x = vec[0];
		cir2.y = vec[1];
		ImGui::PopID();
		ImGui::End();
	}

	{
		ImGui::Begin("Circle3");
		ImGui::PushID("Circle3");
		static float vec[3];
		vec[0] = cir3.x;
		vec[1] = cir3.y;
		ImGui::InputFloat2("position", vec);
		ImGui::SliderFloat("r", &cir3.r, 1, 100);
		ImGui::ColorEdit3("clear color", (float*)&cir3.clear_color);

		cir3.x = vec[0];
		cir3.y = vec[1];
		ImGui::PopID();
		ImGui::End();
	}

	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PlayScene");
	}

	SceneBase::Update();
}


void TitleScene::Draw()
{
	cir1.Draw();
	cir2.Draw();
	cir3.Draw();

	SceneBase::Draw();
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}
