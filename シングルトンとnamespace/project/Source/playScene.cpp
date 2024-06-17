#include "playScene.h"
#include "../Library/sceneManager.h"
#include "DebugScreen.h"
#include <DxLib.h>
#include "Deck.h"
#include "PlayerCards.h"

PlayScene::PlayScene()
{
	deck = Instantiate<Deck>();
	player[0] = Instantiate<PlayerCards>();
	player[0]->SetPosition(100, 600);
	player[1] = Instantiate<PlayerCards>();
	player[1]->SetPosition(100, 100);
	turn = 0;
	counter = 20;
	isHandingOut = false;
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TitleScene");
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		deck->Shuffle(); // シャッフル
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		isHandingOut = true;
	}
	if (isHandingOut) {
		handOut();
	}
	SceneBase::Update();
}

void PlayScene::Draw()
{
	SceneBase::Draw();

	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}

void PlayScene::handOut()
{
	if (--counter <= 0) {
		// ここでカードを配る
		Card* c = deck->GetNext();
		if (c != nullptr) {
			player[turn]->Add(c);
			turn = (turn + 1) % 2;
		}
		else {
			// 配り終わった
			player[0]->Sort();
			player[1]->Sort();
			isHandingOut = false;
		}
		counter = 5;
	}
}

//配る関数を作る
// Dキーを押したら、フラグをtrueにする
// フラグがtrueだったら配る関数を呼ぶ
// 配り終わったら、Sortを呼んでから、フラグをfalseにする
