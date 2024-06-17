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
	// �J�[�h�����o���֐�

	void Shuffle();

private:

	int hImage;

	// �g�����v�T�Q����z��(vector��list)�ŊǗ�����
	std::vector<Card*> cardlist;

	// ���̔z��ɑS���̃J�[�h����ׂ�
	// �z��f�[�^��\������
	long long uSeconds;
};