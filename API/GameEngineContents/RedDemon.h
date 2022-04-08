#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
class RedDemon : public GameEngineActor
{
public:
	// constrcuter destructer
	RedDemon();
	~RedDemon();

	// delete Function
	RedDemon(const RedDemon& _Other) = delete;
	RedDemon(RedDemon&& _Other) noexcept = delete;
	RedDemon& operator=(const RedDemon& _Other) = delete;
	RedDemon& operator=(RedDemon&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Render() override;
};

