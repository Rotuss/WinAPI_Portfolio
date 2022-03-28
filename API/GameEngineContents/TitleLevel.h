#pragma once
#include <GameEngine/GameEngineLevel.h>

// 설명 : 
class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	// 보통 상속 받은 것은 protected에 넣어둠. Engine에서 Loading을 실행시켜주려 하는 것. 그렇지만 다른 곳에서 Loading을 또 실행시키면 안됨(할 수 있지만 하면 안됨)
	void Loading() override;
	void Update() override;

private:
};

