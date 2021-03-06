#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineActor.h>

enum class FrogState
{
	STARTDOWN,
	IDLE,
	STARTMOVE,
	MOVE,
	JUMP,
	DOWN,
	ATTACK,
	SNOW1,
	SNOW2,
	SNOW3,
	SNOWBALL,
	BLUESNOWBALL,
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
// ???? : 
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

	void ChangeState(FrogState _State);
	void StateUpdate();

protected:

private:
	float4	MoveDir_;
	float	Range_;
	float	Time_;
	float	MoveTime_;
	float	JumpTime_;
	float	AttackTime_;
	float	MeltingTime_;
	float	ShakingTime_;
	float	SnowBallDeathTime_;
	float	DeathTime_;
	float	ItemTime_;
	float	Speed_;
	float	SnowSpeed_;
	float	AccSpeed_;
	float	Gravity_;
	float	AccGravity_;
	bool	DeathCheck_;
	int		DamageCount_;
	int		StartMoveCount_;
	
	GameEngineImage*		FloorColImage_;
	GameEngineCollision*	FrogCollision_;
	GameEngineCollision*	FrogRCollision_;
	GameEngineCollision*	FrogLCollision_;
	GameEngineCollision*	FrogAttackCollision_;
	GameEngineCollision*	FrogSnowCollision_;
	GameEngineCollision*	FrogSnowRCollision_;
	GameEngineCollision*	FrogSnowLCollision_;
	GameEngineCollision*	FrogSnowBallCollision_;
	GameEngineCollision*	FrogSnowBallRCollision_;
	GameEngineCollision*	FrogSnowBallLCollision_;
	GameEngineCollision*	FrogBlueSnowBallCollision_;
	GameEngineRenderer*		FrogAnimationRender_;
	FrogDir					CurrentDir_;
	std::string				AnimationName_;
	std::string				ChangeDirText_;

	void Start() override;
	void Update() override;
	void Render() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void RandomItem();
	void CollisionFloorCheck();
	
	FrogState CurrentState_;

	void StartDownUpdate();
	void IdleUpdate();
	void StartMoveUpdate();
	void MoveUpdate();
	void JumpUpdate();
	void DownUpdate();
	void AttackUpdate();
	void Snow1Update();
	void Snow2Update();
	void Snow3Update();
	void SnowBallUpdate();
	void BlueSnowBallUpdate();
	void ShakingSnowUpdate();
	void DefeatedUpdate();
	void DeathUpdate();

	void StartDownStart();
	void IdleStart();
	void StartMoveStart();
	void MoveStart();
	void JumpStart();
	void DownStart();
	void AttackStart();
	void Snow1Start();
	void Snow2Start();
	void Snow3Start();
	void SnowBallStart();
	void BlueSnowBallStart();
	void ShakingSnowStart();
	void DefeatedStart();
	void DeathStart();
};

