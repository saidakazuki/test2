#pragma once
// PlayerCards.h
#include "../Library/gameObject.h"
#include <vector>
class Card;

class PlayerCards : public GameObject {
public:
	PlayerCards();
	~PlayerCards();
	void Update() override;
	void Draw() override;
	void SetPosition(int x, int y);
	void Add(Card* c);

	void Sort();

private:
	std::vector<Card*> cardlist;
	VECTOR position;
};