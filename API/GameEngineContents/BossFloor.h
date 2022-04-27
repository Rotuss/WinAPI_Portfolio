#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class BossFloor : public GameEngineLevel
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

	float BgmPlayTime_;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	GameEngineSoundPlayer BgmPlayer_;
};

