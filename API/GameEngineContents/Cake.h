#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

// Ό³Έν : 
class Cake :public GameEngineActor
{
public:
	// constrcuter destructer
	Cake();
	~Cake();

	// delete Function
	Cake(const Cake& _Other) = delete;
	Cake(Cake&& _Other) noexcept = delete;
	Cake& operator=(const Cake& _Other) = delete;
	Cake& operator=(Cake&& _Other) noexcept = delete;

protected:

private:
	GameEngineCollision* CakeCollision_;
	GameEngineRenderer* Actor_;

	float Time_;

	void Start() override;
	void Update() override;
	void Render() override;
};

