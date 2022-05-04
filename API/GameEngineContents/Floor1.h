#pragma once
#include "SnowLevel.h"
#include "FloorLogo.h"
#include "Life.h"
#include "Score.h"

// Ό³Έν : 
class Floor1 : public SnowLevel
{
public:
	// constrcuter destructer
	Floor1();
	~Floor1();

	// delete Function
	Floor1(const Floor1& _Other) = delete;
	Floor1(Floor1&& _Other) noexcept = delete;
	Floor1& operator=(const Floor1& _Other) = delete;
	Floor1& operator=(Floor1&& _Other) noexcept = delete;

	float Time_;
	float LogoTime_;
	float NextFloorTime_;
	bool LogoShow_;
	bool CameraCheck_;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	FloorLogo* LogoActor;
	Life* LifeUI;
	Score* ScoreUI;

	void CameraMoveUp();
};

