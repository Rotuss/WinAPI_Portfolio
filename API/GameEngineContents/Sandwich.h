#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

// Ό³Έν : 
class Sandwich : public GameEngineActor
{
public:
	// constrcuter destructer
	Sandwich();
	~Sandwich();

	// delete Function
	Sandwich(const Sandwich& _Other) = delete;
	Sandwich(Sandwich&& _Other) noexcept = delete;
	Sandwich& operator=(const Sandwich& _Other) = delete;
	Sandwich& operator=(Sandwich&& _Other) noexcept = delete;

protected:

private:
	GameEngineCollision* SandwichCollision_;
	GameEngineRenderer* Actor_;

	float Time_;

	void Start() override;
	void Update() override;
	void Render() override;
};

