#pragma once
#include <GameEngine/GameEngineActor.h>

enum class BossState
{
	STARTDOWN,
	IDLE,
	JUMP,
	ATTACK,
	DEFEATED,
	DEATH,

	MAX
};
// Ό³Έν : 
class GameEngineImage;
class GameEngineCollision;
class Boss : public GameEngineActor
{
public:
	// constrcuter destructer
	Boss();
	~Boss();

	// delete Function
	Boss(const Boss& _Other) = delete;
	Boss(Boss&& _Other) noexcept = delete;
	Boss& operator=(const Boss& _Other) = delete;
	Boss& operator=(Boss&& _Other) noexcept = delete;

	void ChangeState(BossState _State);
	void StateUpdate();

protected:

private:
	float4	MoveDir_;
	float	Range_;
	float	Time_;
	float	JumpTime_;
	float	AttackTime_;
	float	DefeatedTime_;
	float	DeathTime_;
	float	Speed_;
	float	AccSpeed_;
	float	Gravity_;
	float	AccGravity_;
	bool	DeathCheck_;
	int		DamageCount_;

	GameEngineImage*		FloorColImage_;
	GameEngineCollision*	BossCollision_;
	GameEngineCollision*	BossHeadCollision_;
	GameEngineCollision*	FrogAttackCollision_;
	GameEngineRenderer*		BossAnimationRender_;
	std::string				AnimationName_;
	std::string				ChangeDirText_;
	
	void Start() override;
	void Update() override;
	void Render() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void CollisionFloorCheck();

	BossState CurrentState_;

	void StartDownUpdate();
	void IdleUpdate();
	void JumpUpdate();
	void AttackUpdate();
	void DefeatedUpdate();
	void DeathUpdate();

	void StartDownStart();
	void IdleStart();
	void JumpStart();
	void AttackStart();
	void DefeatedStart();
	void DeathStart();
};

