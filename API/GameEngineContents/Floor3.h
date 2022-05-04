#pragma once
#include "SnowLevel.h"
#include "FloorLogo.h"
#include "Life.h"
#include "Score.h"

// Ό³Έν : 
class Floor3 : public SnowLevel
{
public:
	// constrcuter destructer
	Floor3();
	~Floor3();

	// delete Function
	Floor3(const Floor3& _Other) = delete;
	Floor3(Floor3&& _Other) noexcept = delete;
	Floor3& operator=(const Floor3& _Other) = delete;
	Floor3& operator=(Floor3&& _Other) noexcept = delete;

	float LogoTime_;
	float NextFloorTime_;
	bool LogoShow_;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	FloorLogo* LogoActor;
	Life* LifeUI;
	Score* ScoreUI;
};

