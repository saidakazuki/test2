#pragma once
//Card.h
#include "../Library/gameObject.h"

class Card : public GameObject {
public:
	Card();
	~Card();
	void Update() override;
	void Draw() override;
	void MoveTo(VECTOR target, float time);

	void Select(bool select) { selected = select; };
	bool IsSelected() { return selected; }

	/// <summary>
	/// �}�E�X���W���󂯎���āA�J�[�h��ɂ��邩�𔻒肷��֐�
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns>�J�[�h��Ȃ��true</returns>
	bool InCard(int x, int y);

	enum SUIT {
		SPADE = 0,
		HEART,
		CLUB,
		DIA,
		MAX
	};
	struct Info {
		SUIT suit;
		int number; // 1�`13
	};
	Info info;

	bool front; // �\���H
	VECTOR position;
	int hImage;
	bool selected; // �I�΂�Ă��܂�

	VECTOR start; // �ړ��J�n�ʒu
	VECTOR end; // �ړ��I���ʒu
	float maxTime; // �ړ�����
	float currentTime; // ���̎���
};