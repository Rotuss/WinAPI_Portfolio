#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class BossEnterLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	BossEnterLevel();
	~BossEnterLevel();

	// delete Function
	BossEnterLevel(const BossEnterLevel& _Other) = delete;
	BossEnterLevel(BossEnterLevel&& _Other) noexcept = delete;
	BossEnterLevel& operator=(const BossEnterLevel& _Other) = delete;
	BossEnterLevel& operator=(BossEnterLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	float Time_;
};

