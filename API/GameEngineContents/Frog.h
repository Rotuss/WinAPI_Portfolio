#pragma once
#include <GameEngine/GameEngineActor.h>

enum class FrogState
{
	IDLE,
	MOVE,
	JUMP,
	DOWN,
	ATTACK,
	SHAKINGSNOW,
	DEFEATED,
	DEATH,

	MAX
};
enum class FrogDir
{
	LEFT,
	RIGHT,
};
// Ό³Έν : 
class GameEngineImage;
class GameEngineCollision;
class Frog : public GameEngineActor
{
public:
	// constrcuter destructer
	Frog();
	~Frog();

	// delete Function
	Frog(const Frog& _Other) = delete;
	Frog(Frog&& _Other) noexcept = delete;
	Frog& operator=(const Frog& _Other) = delete;
	Frog& operator=(Frog&& _Other) noexcept = delete;

protected:

private:
	GameEngineCollision*	FrogCollision_;
	GameEngineCollision*	FrogAttackCollision_;
	GameEngineRenderer*		FrogAnimationRender_;
	FrogDir					CurrentDir_;

	void Start() override;
	void Render() override;

	FrogState CurrentState_;
};

