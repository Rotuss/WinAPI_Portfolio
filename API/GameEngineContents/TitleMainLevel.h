#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineLevel.h>

// 설명 : 
class TitleMainLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleMainLevel();
	~TitleMainLevel();

	// delete Function
	TitleMainLevel(const TitleMainLevel& _Other) = delete;
	TitleMainLevel(TitleMainLevel&& _Other) noexcept = delete;
	TitleMainLevel& operator=(const TitleMainLevel& _Other) = delete;
	TitleMainLevel& operator=(TitleMainLevel&& _Other) noexcept = delete;

	GameEngineSoundPlayer BgmPlayer_;

protected:
	// 보통 상속 받은 것은 protected에 넣어둠. Engine에서 Loading을 실행시켜주려 하는 것. 그렇지만 다른 곳에서 Loading을 또 실행시키면 안됨(할 수 있지만 하면 안됨)
	void Loading() override;
	void Update() override;

	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:
};

