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
	//ScoreReset(); // �@C�̌Ăѕ�
	//Score::Reset(); // �Anamespace�̌Ăѕ�
	Score* score = Score::GetInstance(); // �B�V���O���g���̌Ăѕ�
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
	// ���̎��_�ł̎��Ԃ��擾
	auto start = chrono::system_clock::now();

	vector<thread> threads;
	threads.reserve(cardlist.size());
	// card���X�g�ɂ��邷�ׂẴJ�[�h��Update()���Ă�
	for (auto c : cardlist) {
		c->Update();
//		std::thread th(ThreadUpdate, c);
//		threads.emplace_back(std::move(th));
	}
	// �S����thread��join����
//	for (auto& th : threads) {
//		th.join();
//	}

	// �����Ŏ��Ԃ��擾���āA�������߂遨�ϐ��ɂ���Draw�ŕ\��
	auto end = std::chrono::system_clock::now();       // �v���I��������ۑ�
	auto dur = end - start;        // �v�������Ԃ��v�Z
	auto usec = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
	uSeconds = usec;
}

void Deck::Draw()
{
	// card���X�g�ɂ��邷�ׂẴJ�[�h��Draw()���Ă�
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
		//cardlist[cr]��cardlist[cl]�̓���ւ�
		Card::Info temp = cardlist[cr]->info;
		cardlist[cr]->info = cardlist[cl]->info;
		cardlist[cl]->info = temp;
	}
}
