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
		GetMousePoint(&mouseX, &mouseY); // マウスの座標取得
		// Cardクラスに、マウスの座標がカード上かを判定させる
		// cardlistをイテレーターで回す
		for (Card* c : cardlist) // 全部を非選択にする
			c->Select(false);
		for (auto itr = cardlist.rbegin(); itr != cardlist.rend(); itr++) {
			Card* c = *itr;
			if (c->InCard(mouseX, mouseY)) {
				// ここでカードが選ばれた
				c->Select(true);
				// ペアになるカードを探して、それも選択する
				int num = c->info.number; // 選んだ数字
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
	// カードを追加
	// c->positionに今の座標（つまりdeckの座標）が入っている
	VECTOR target = VGet(position.x + cardlist.size() * 30,
		position.y, 0);
	c->MoveTo(target, 1.0f);
}

void PlayerCards::Sort()
{
	auto func =
		[](Card* a, Card* b) {
		if (a->info.suit != b->info.suit) { // マークが違う
			return (a->info.suit < b->info.suit);
		}
		else // マークが同じ
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
