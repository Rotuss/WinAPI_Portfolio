#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

// Ό³Έν : 
class Mushroom : public GameEngineActor
{
public:
	// constrcuter destructer
	Mushroom();
	~Mushroom();

	// delete Function
	Mushroom(const Mushroom& _Other) = delete;
	Mushroom(Mushroom&& _Other) noexcept = delete;
	Mushroom& operator=(const Mushroom& _Other) = delete;
	Mushroom& operator=(Mushroom&& _Other) noexcept = delete;

protected:

private:
	GameEngineCollision* MushroomCollision_;
	GameEngineRenderer* Actor_;

	float Time_;

	void Start() override;
	void Update() override;
	void Render() override;
};

