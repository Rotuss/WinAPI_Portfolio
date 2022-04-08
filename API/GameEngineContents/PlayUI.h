#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
class PlayUI : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayUI();
	~PlayUI();

	// delete Function
	PlayUI(const PlayUI& _Other) = delete;
	PlayUI(PlayUI&& _Other) noexcept = delete;
	PlayUI& operator=(const PlayUI& _Other) = delete;
	PlayUI& operator=(PlayUI&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
};

