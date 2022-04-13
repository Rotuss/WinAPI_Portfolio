#pragma once
#include <random>

// 제네레이터, 유니폼

// 설명 : 
class GameEngineRandom
{
	// 제네레이터
	// 메르센 트위스터의 알고리즘으로 비트를 뒤섞는 것
	std::mt19937_64 mt_;

	// 유니폼
	// 제한
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
		// 실수는 생성기가 Real
		std::uniform_real_distribution<float> Uniform_(_Min, _Max);
		return Uniform_(mt_);
	}

protected:

private:
	
};

