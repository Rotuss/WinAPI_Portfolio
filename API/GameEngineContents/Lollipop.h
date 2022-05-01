#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

// Ό³Έν : 
class Lollipop : public GameEngineActor
{
public:
	// constrcuter destructer
	Lollipop();
	~Lollipop();

	// delete Function
	Lollipop(const Lollipop& _Other) = delete;
	Lollipop(Lollipop&& _Other) noexcept = delete;
	Lollipop& operator=(const Lollipop& _Other) = delete;
	Lollipop& operator=(Lollipop&& _Other) noexcept = delete;

protected:

private:
	GameEngineCollision* LollipopCollision_;
	GameEngineRenderer* Actor_;

	float Time_;

	void Start() override;
	void Update() override;
	void Render() override;
};

