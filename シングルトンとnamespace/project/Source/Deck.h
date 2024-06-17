#pragma once
#include "../Library/gameObject.h"
#include <vector>
class Card;

class Deck : public GameObject
{
public:
	Deck();
	~Deck();
	void Update() override;
	void Draw() override;

	Card* GetNext();
	// カードを取り出す関数

	void Shuffle();

private:

	int hImage;

	// トランプ５２枚を配列(vectorかlist)で管理する
	std::vector<Card*> cardlist;

	// その配列に全部のカードを並べる
	// 配列データを表示する
	long long uSeconds;
};