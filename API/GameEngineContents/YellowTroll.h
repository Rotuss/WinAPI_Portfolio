#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
class YellowTroll : public GameEngineActor
{
public:
	// constrcuter destructer
	YellowTroll();
	~YellowTroll();

	// delete Function
	YellowTroll(const YellowTroll& _Other) = delete;
	YellowTroll(YellowTroll&& _Other) noexcept = delete;
	YellowTroll& operator=(const YellowTroll& _Other) = delete;
	YellowTroll& operator=(YellowTroll&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Render() override;
};

