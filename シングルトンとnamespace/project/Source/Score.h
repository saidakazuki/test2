#pragma once
//Score.h
// �ǂ�����ł��Ăׂ�N���X
// �X�R�A�����Z�b�g����Reset()
// �X�R�A�ɓ_��������Add()
// �X�R�A���擾����Get()

// �@ C����Ɠ���
#if 0
void ScoreReset();
void ScoreAdd(int v);
int Get();
#endif

// �A namespace���g��
#if 0
namespace Score {
	void Reset();
	void Add(int v);
	int Get();
};
#endif

// �B �V���O���g��(Singleton)���g�����C���X�^���X���B��K������
class Score {
private:
	Score(); // �R���X�g���N�^�[��private
public:
	void Reset();
	void Add(int v);
	int Get();
	static Score* GetInstance() { // static�ō��
		static Score* inst = nullptr; // static�ō��
		if (inst == nullptr) { // �C���X�^���X���Ȃ���΍��
			inst = new Score();
		}
		return inst;
	};
private:
	int score;
};