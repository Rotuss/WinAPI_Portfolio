#pragma once
#include <GameEngineBase/GameEngineSound.h>
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
enum class BossDir
{
	LEFT,
	RIGHT,
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
	float	StandbyTIme_;
	float	AttackTime_;
	float	DefeatedTime1_;
	float	DefeatedTime2_;
	float	DeathTime_;
	float	Speed_;
	bool	AttackStart1_;
	bool	AttackStart2_;
	bool	AttackStart3_;
	bool	AttackMoveCheck_;
	bool	DeathCheck_;
	int		SonNum_;
	int		DamageCount_;
	int		JumpCount_;

	GameEngineImage*		FloorColImage_;
	GameEngineCollision*	BossCollision_;
	GameEngineCollision*	BossHeadCollision_;
	GameEngineCollision*	BossAttackCollision_;
	GameEngineCollision*	BossDeathCollision_;
	GameEngineRenderer*		BossAnimationRender_;
	BossDir					CurrentDir_;
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

