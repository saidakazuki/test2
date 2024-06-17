#include "Deck.h"
#include <assert.h>
#include "Card.h"
#include <thread>
#include <chrono>
#include "Score.h"
#include "fstream"

using namespace std;

Deck::Deck()
{
	//ScoreReset(); // ①Cの呼び方
	//Score::Reset(); // ②namespaceの呼び方
	Score* score = Score::GetInstance(); // ③シングルトンの呼び方
	score->Reset();

	hImage = LoadGraph("data/textures/trump.png");
	assert(hImage > 0);

	cardlist.clear();
	int order = 200;
	for (int s = Card::SUIT::SPADE; s < Card::SUIT::MAX; s++)
	{
		for (int n = 1; n <= 13; n++) {
//			Card* c = Instantiate<Card>();
			Card* c = new Card();
			c->info.suit = (Card::SUIT)s;
			c->info.number = n;
			c->hImage = hImage;
			c->position = VGet(0, 0, 0);
			c->MoveTo(VGet(n * 50, s * 50,0), 10.0f);

			cardlist.emplace_back(c);
			c->front = true;
			SceneManager::CurrentScene()->SetDrawOrder(c, order);
			order--;
		}
	}
}

Deck::~Deck()
{
}

void ThreadUpdate(Card* c)
{
	c->Update();
}

void Deck::Update()
{
	// この時点での時間を取得
	auto start = chrono::system_clock::now();

	vector<thread> threads;
	threads.reserve(cardlist.size());
	// cardリストにあるすべてのカードのUpdate()を呼ぶ
	for (auto c : cardlist) {
		c->Update();
//		std::thread th(ThreadUpdate, c);
//		threads.emplace_back(std::move(th));
	}
	// 全部のthreadをjoinする
//	for (auto& th : threads) {
//		th.join();
//	}

	// ここで時間を取得して、差を求める→変数にしてDrawで表示
	auto end = std::chrono::system_clock::now();       // 計測終了時刻を保存
	auto dur = end - start;        // 要した時間を計算
	auto usec = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
	uSeconds = usec;
}

void Deck::Draw()
{
	// cardリストにあるすべてのカードのDraw()を呼ぶ
	for (auto c : cardlist) {
		c->Draw();
	}
	DrawFormatString(200, 100, 0x00ffff, "%6d", uSeconds);
}

Card* Deck::GetNext()
{
	if (cardlist.size() == 0)
		return nullptr;
	Card* c = cardlist[0];
	cardlist.erase(cardlist.begin());
	return c;
}

void Deck::Shuffle()
{
	for (int cl = 0; cl < cardlist.size(); cl++) {
		int cr = rand() % cardlist.size();
		//cardlist[cr]とcardlist[cl]の入れ替え
		Card::Info temp = cardlist[cr]->info;
		cardlist[cr]->info = cardlist[cl]->info;
		cardlist[cl]->info = temp;
	}
}
