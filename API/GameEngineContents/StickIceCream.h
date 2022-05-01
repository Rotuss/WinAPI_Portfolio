#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

// Ό³Έν : 
class StickIceCream : public GameEngineActor
{
public:
	// constrcuter destructer
	StickIceCream();
	~StickIceCream();

	// delete Function
	StickIceCream(const StickIceCream& _Other) = delete;
	StickIceCream(StickIceCream&& _Other) noexcept = delete;
	StickIceCream& operator=(const StickIceCream& _Other) = delete;
	StickIceCream& operator=(StickIceCream&& _Other) noexcept = delete;

protected:

private:
	GameEngineCollision* StickIceCreamCollision_;
	GameEngineRenderer* Actor_;

	float Time_;

	void Start() override;
	void Update() override;
	void Render() override;
};

