#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class GameOverLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	GameOverLevel();
	~GameOverLevel();

	// delete Function
	GameOverLevel(const GameOverLevel& _Other) = delete;
	GameOverLevel(GameOverLevel&& _Other) noexcept = delete;
	GameOverLevel& operator=(const GameOverLevel& _Other) = delete;
	GameOverLevel& operator=(GameOverLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	float Time_;
};

