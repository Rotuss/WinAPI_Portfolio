#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "Life.h"
#include "Score.h"

// Ό³Έν : 
class Floor2 : public GameEngineLevel
{
public:
	// constrcuter destructer
	Floor2();
	~Floor2();

	// delete Function
	Floor2(const Floor2& _Other) = delete;
	Floor2(Floor2&& _Other) noexcept = delete;
	Floor2& operator=(const Floor2& _Other) = delete;
	Floor2& operator=(Floor2&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	Life* LifeUI;
	Score* ScoreUI;
};

