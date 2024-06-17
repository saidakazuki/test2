#include <DxLib.h>
#include "App.h"
#include "../Source/config.h"
#include "../ImGui/imgui_impl_dxlib.hpp"

#define CoGVersion (2.2)

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	SetOutApplicationLogValidFlag(FALSE); // ログを出さない

	SetMainWindowText(WINDOW_NAME);
	SetWindowSizeExtendRate(WINDOW_EXTEND);
	ChangeWindowMode(WINDOW_MODE); // Windowモードの場合

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SetAlwaysRunFlag(TRUE);
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	// ユーザーの入力をImGuiも扱えるようにする
	SetHookWinProc([](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT /*CALLBACK*/
	{
		// DxLibとImGuiのウィンドウプロシージャを両立させる
		SetUseHookWinProcReturnValue(FALSE);
		return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
	});

	// imgui init
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ImGui_ImplDXlib_Init();

	AppInit();

	int mStartTime = GetNowCount();

	int screen = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, true);

	while (true) {
		if (ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE) != 0)//ESCAPEキーが押すされたらApplicationを終了
			break;

		//120fps対策
		int cur = GetNowCount();
		if (cur < mStartTime + 16)
			continue;
		mStartTime = cur;

		ImGui_ImplDXlib_NewFrame();
		ImGui::NewFrame();

		AppUpdate();

//		SetDrawScreen(screen);
//		ClearDrawScreen();
//		AppDraw();

//		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		AppDraw();
		//描画
//		DrawGraph(0, 0, screen, true);
//		SetDrawScreen(DX_SCREEN_BACK);

		ImGui::EndFrame();
		ImGui::Render();

		ImGui_ImplDXlib_RenderDrawData();


		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
		RefreshDxLibDirect3DSetting();

		//裏画面描写
		ScreenFlip();
	}
	AppRelease();

	//Imguiの終了処理
	ImGui_ImplDXlib_Shutdown();
	ImGui::DestroyContext();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}