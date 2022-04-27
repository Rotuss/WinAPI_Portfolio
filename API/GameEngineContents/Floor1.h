#pragma once
#include <GameEngine/GameEngineLevel.h>

// ���� : 
class Floor1 : public GameEngineLevel
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

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
};

