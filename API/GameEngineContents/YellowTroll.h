#pragma once
#include <GameEngine/GameEngineActor.h>

enum class YellowTrollState
{
	IDLE,
	MOVE,
	JUMP,
	DOWN,
	SHAKINGSNOW,
	DEFEATED,
	DEATH,

	MAX
};
enum class YellowTrollDir
{
	LEFT,
	RIGHT,
};
// Ό³Έν : 
class GameEngineImage;
class GameEngineCollision;
class YellowTroll : public GameEngineActor
{
public:
	// constrcuter destructer
	YellowTroll();
	~YellowTroll();

	// delete Function
	YellowTroll(const YellowTroll& _Other) = delete;
	YellowTroll(YellowTroll&& _Other) noexcept = delete;
	YellowTroll& operator=(const YellowTroll& _Other) = delete;
	YellowTroll& operator=(YellowTroll&& _Other) noexcept = delete;

protected:

private:
	GameEngineCollision*	YellowTrollCollision_;
	GameEngineCollision*	YellowTrollAttackCollision_;
	GameEngineRenderer*		YellowTrollAnimationRender_;
	YellowTrollDir			CurrentDir_;
	
	void Start() override;
	void Render() override;

	YellowTrollState CurrentState_;
};

