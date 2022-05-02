#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

// Ό³Έν : 
class Candy : public GameEngineActor
{
public:
	// constrcuter destructer
	Candy();
	~Candy();

	// delete Function
	Candy(const Candy& _Other) = delete;
	Candy(Candy&& _Other) noexcept = delete;
	Candy& operator=(const Candy& _Other) = delete;
	Candy& operator=(Candy&& _Other) noexcept = delete;

protected:

private:
	GameEngineCollision* CandyCollision_;
	GameEngineRenderer* Actor_;

	float Time_;
	
	void Start() override;
	void Update() override;
	void Render() override;
};

