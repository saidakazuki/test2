#pragma once
//Score.h
// どこからでも呼べるクラス
// スコアをリセットするReset()
// スコアに点を加えるAdd()
// スコアを取得するGet()

// ① C言語と同じ
#if 0
void ScoreReset();
void ScoreAdd(int v);
int Get();
#endif

// ② namespaceを使う
#if 0
namespace Score {
	void Reset();
	void Add(int v);
	int Get();
};
#endif

// ③ シングルトン(Singleton)を使う→インスタンスが唯一必ず存在
class Score {
private:
	Score(); // コンストラクターはprivate
public:
	void Reset();
	void Add(int v);
	int Get();
	static Score* GetInstance() { // staticで作る
		static Score* inst = nullptr; // staticで作る
		if (inst == nullptr) { // インスタンスがなければ作る
			inst = new Score();
		}
		return inst;
	};
private:
	int score;
};