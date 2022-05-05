#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

// Ό³Έν : 
class RedPotion : public GameEngineActor
{
public:
	// constrcuter destructer
	RedPotion();
	~RedPotion();

	// delete Function
	RedPotion(const RedPotion& _Other) = delete;
	RedPotion(RedPotion&& _Other) noexcept = delete;
	RedPotion& operator=(const RedPotion& _Other) = delete;
	RedPotion& operator=(RedPotion&& _Other) noexcept = delete;

protected:

private:
	GameEngineCollision* RedPotionCollision_;
	GameEngineRenderer* Actor_;

	float Time_;

	void Start() override;
	void Update() override;
	void Render() override;
};

