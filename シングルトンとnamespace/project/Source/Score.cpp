#include "Score.h"

// �@C����Ɠ���
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

// �Anamespace���g��
#if 0
namespace { // �����l�[���X�y�[�X�ŉB��(���̃\�[�X���̂ݎg����j
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

// �B�V���O���g�����g��
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
