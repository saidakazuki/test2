#include "Card.h"
#include "../Library/time.h"

Card::Card()
{
	front = true;
	selected = false;
}

Card::~Card()
{
}

void Card::Update()
{
	currentTime += Time::DeltaTime();
	if (currentTime >= maxTime) {
		currentTime = maxTime;
		position = end;
		return;
	}
	float t = currentTime / maxTime; // tは0から1へ変化
	float rate = -t * t + 2 * t; // イージングを入れるならここで
	position = (end - start) * rate + start;
}

void Card::Draw()
{
	int offset = selected ? -5 : 0;

	if (front) {
		DrawRectGraph(
			position.x, position.y+offset, 
			info.number * 56, info.suit * 80, 56, 80,
			hImage, TRUE);
	}
	else {
		DrawRectGraph(
			position.x, position.y+offset, 0*56, 0*80, 56, 80,
			hImage, TRUE);
	}
}

void Card::MoveTo(VECTOR target, float time)
{
	start = position;
	end = target;
	maxTime = time;
	currentTime = 0.0f;
}

bool Card::InCard(int x, int y)
{
	x -= position.x;
	y -= position.y;
	if (x >= 0 && x < 56 && y >= 0 && y < 80) {
		return true;
	}
	return false;
}
