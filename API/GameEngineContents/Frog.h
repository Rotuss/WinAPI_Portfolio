#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
class Frog : public GameEngineActor
{
public:
	// constrcuter destructer
	Frog();
	~Frog();

	// delete Function
	Frog(const Frog& _Other) = delete;
	Frog(Frog&& _Other) noexcept = delete;
	Frog& operator=(const Frog& _Other) = delete;
	Frog& operator=(Frog&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Render() override;
};

