#pragma once
#include "SnowLevel.h"
#include "FloorLogo.h"
#include "Life.h"
#include "Score.h"

// Ό³Έν : 
class Floor2 : public SnowLevel
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

