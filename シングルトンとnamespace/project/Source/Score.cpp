#include "Score.h"

// �@C言語と同じ
#if 0
int score = 0;

void ScoreReset()
{
    score = 0;
}

void ScoreAdd(int v)
{
    score += v;
}

int Get()
{
    return score;
    return 0;
}
#endif

// �Anamespaceを使う
#if 0
namespace { // 無名ネームスペースで隠す(このソース内のみ使える）
    int score;
};

void Score::Reset()
{
    score = 0;
}

void Score::Add(int v)
{
    score += v;
}

int Score::Get()
{
    return score;
}
#endif

// �Bシングルトンを使う
Score::Score()
{
}

void Score::Reset()
{
    score = 0;
}

void Score::Add(int v)
{
    score += v;
}

int Score::Get()
{
    return score;
}
