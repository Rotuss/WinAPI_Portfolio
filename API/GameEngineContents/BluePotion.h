#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

// Ό³Έν : 
class BluePotion : public GameEngineActor
{
public:
	// constrcuter destructer
	BluePotion();
	~BluePotion();

	// delete Function
	BluePotion(const BluePotion& _Other) = delete;
	BluePotion(BluePotion&& _Other) noexcept = delete;
	BluePotion& operator=(const BluePotion& _Other) = delete;
	BluePotion& operator=(BluePotion&& _Other) noexcept = delete;

	static bool BPCheck_;

protected:

private:
	GameEngineCollision* BluePotionCollision_;
	GameEngineRenderer* Actor_;

	float Time_;

	void Start() override;
	void Update() override;
	void Render() override;
};

