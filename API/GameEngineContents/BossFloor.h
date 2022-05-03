#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include "SnowLevel.h"
#include "Life.h"
#include "Score.h"

// Ό³Έν : 
class BossFloor : public SnowLevel
{
public:
	// constrcuter destructer
	BossFloor();
	~BossFloor();

	// delete Function
	BossFloor(const BossFloor& _Other) = delete;
	BossFloor(BossFloor&& _Other) noexcept = delete;
	BossFloor& operator=(const BossFloor& _Other) = delete;
	BossFloor& operator=(BossFloor&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	GameEngineSoundPlayer BgmPlayer_;

	Life* LifeUI;
	Score* ScoreUI;
};

