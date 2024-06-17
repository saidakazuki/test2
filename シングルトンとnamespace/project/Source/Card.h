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
	/// マウス座標を受け取って、カード上にあるかを判定する関数
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns>カード上ならばtrue</returns>
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
		int number; // 1～13
	};
	Info info;

	bool front; // 表か？
	VECTOR position;
	int hImage;
	bool selected; // 選ばれています

	VECTOR start; // 移動開始位置
	VECTOR end; // 移動終了位置
	float maxTime; // 移動時間
	float currentTime; // 今の時間
};