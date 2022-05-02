#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

// Ό³Έν : 
class Score : public GameEngineActor
{
public:
	// constrcuter destructer
	Score();
	~Score();

	// delete Function
	Score(const Score& _Other) = delete;
	Score(Score&& _Other) noexcept = delete;
	Score& operator=(const Score& _Other) = delete;
	Score& operator=(Score&& _Other) noexcept = delete;

	static int ScoreUI_;

	void ScoreNum(const int& _Other)
	{
		ScoreUI_ += _Other;
	}

protected:

private:
	GameEngineRenderer* Actor_1P;
	GameEngineRenderer* Number0;
	GameEngineRenderer* Number1;
	GameEngineRenderer* Number2;
	GameEngineRenderer* Number3;
	GameEngineRenderer* Number4;
	GameEngineRenderer* Number5;
	GameEngineRenderer* Number6;

	GameEngineRenderer* Actor_HI;
	GameEngineRenderer* HNumber0;
	GameEngineRenderer* HNumber1;
	GameEngineRenderer* HNumber2;
	GameEngineRenderer* HNumber3;
	GameEngineRenderer* HNumber4;
	GameEngineRenderer* HNumber5;
	GameEngineRenderer* HNumber6;

	void Start() override;
	void Update() override;
	void Render() override;
};

