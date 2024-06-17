#include "PlayerCards.h"
#include "Card.h"
#include <algorithm>

PlayerCards::PlayerCards()
{
}

PlayerCards::~PlayerCards()
{
}

void PlayerCards::Update()
{
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY); // �}�E�X�̍��W�擾
		// Card�N���X�ɁA�}�E�X�̍��W���J�[�h�ォ�𔻒肳����
		// cardlist���C�e���[�^�[�ŉ�
		for (Card* c : cardlist) // �S�����I���ɂ���
			c->Select(false);
		for (auto itr = cardlist.rbegin(); itr != cardlist.rend(); itr++) {
			Card* c = *itr;
			if (c->InCard(mouseX, mouseY)) {
				// �����ŃJ�[�h���I�΂ꂽ
				c->Select(true);
				// �y�A�ɂȂ�J�[�h��T���āA������I������
				int num = c->info.number; // �I�񂾐���
				for (Card* c2 : cardlist) {
					if (c2->info.number == num && !c2->IsSelected()) {
						c2->Select(true);
						break;
					}
				}
				break;
			}
		}
	}
}

void PlayerCards::Draw()
{
}

void PlayerCards::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

void PlayerCards::Add(Card* c)
{
	cardlist.emplace_back(c);
	// �J�[�h��ǉ�
	// c->position�ɍ��̍��W�i�܂�deck�̍��W�j�������Ă���
	VECTOR target = VGet(position.x + cardlist.size() * 30,
		position.y, 0);
	c->MoveTo(target, 1.0f);
}

void PlayerCards::Sort()
{
	auto func =
		[](Card* a, Card* b) {
		if (a->info.suit != b->info.suit) { // �}�[�N���Ⴄ
			return (a->info.suit < b->info.suit);
		}
		else // �}�[�N������
		{
			return (a->info.number < b->info.number);
		}
	};
	std::sort(cardlist.begin(), cardlist.end(), func);

	OutputDebugString("SORT\n");
	for (int i = 0; i < cardlist.size(); i++) {
		SceneManager::CurrentScene()->SetDrawOrder(cardlist[i], 100 + i);
		Card* c = cardlist[i];
		c->MoveTo(
			VGet(position.x + i * 30, position.y, 0), 0.5f);
	}
};
