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
		deck->Shuffle(); // �V���b�t��
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
		// �����ŃJ�[�h��z��
		Card* c = deck->GetNext();
		if (c != nullptr) {
			player[turn]->Add(c);
			turn = (turn + 1) % 2;
		}
		else {
			// �z��I�����
			player[0]->Sort();
			player[1]->Sort();
			isHandingOut = false;
		}
		counter = 5;
	}
}

//�z��֐������
// D�L�[����������A�t���O��true�ɂ���
// �t���O��true��������z��֐����Ă�
// �z��I�������ASort���Ă�ł���A�t���O��false�ɂ���
