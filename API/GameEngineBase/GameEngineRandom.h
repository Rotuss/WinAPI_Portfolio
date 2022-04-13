#pragma once
#include <random>

// ���׷�����, ������

// ���� : 
class GameEngineRandom
{
	// ���׷�����
	// �޸��� Ʈ�������� �˰������� ��Ʈ�� �ڼ��� ��
	std::mt19937_64 mt_;

	// ������
	// ����
	//std::uniform_int_distribution<int> Uniform_;

public:
	// constrcuter destructer
	GameEngineRandom();
	~GameEngineRandom();

	// delete Function
	GameEngineRandom(const GameEngineRandom& _Other) = delete;
	GameEngineRandom(GameEngineRandom&& _Other) noexcept = delete;
	GameEngineRandom& operator=(const GameEngineRandom& _Other) = delete;
	GameEngineRandom& operator=(GameEngineRandom&& _Other) noexcept = delete;

	int RandomInt(int _Min, int _Max)
	{
		std::uniform_int_distribution<int> Uniform_(_Min, _Max);
		return Uniform_(mt_);
	}
	float RandomFloat(float _Min, float _Max)
	{
		// �Ǽ��� �����Ⱑ Real
		std::uniform_real_distribution<float> Uniform_(_Min, _Max);
		return Uniform_(mt_);
	}

protected:

private:
	
};

