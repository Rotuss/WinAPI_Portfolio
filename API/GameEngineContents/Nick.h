#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
class GameEngineImage;
class Nick : public GameEngineActor
{
public:
	// constrcuter destructer
	Nick();
	~Nick();

	// delete Function
	Nick(const Nick& _Other) = delete;
	Nick(Nick&& _Other) noexcept = delete;
	Nick& operator=(const Nick& _Other) = delete;
	Nick& operator=(Nick&& _Other) noexcept = delete;

protected:

private:
	float Speed_;
	float Gravity_;
	float AccGravity_;

	GameEngineImage* FloorColImage_;

	void Start() override;
	void Update() override;
	void Render() override;
};

