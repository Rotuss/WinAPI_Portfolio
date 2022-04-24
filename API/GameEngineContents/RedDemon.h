#pragma once
#include <GameEngine/GameEngineActor.h>

enum class RedDemonState
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
enum class RedDemonDir
{
	LEFT,
	RIGHT,
};
// 설명 : 
class GameEngineImage;
class GameEngineCollision;
class RedDemon : public GameEngineActor
{
public:
	// constrcuter destructer
	RedDemon();
	~RedDemon();

	// delete Function
	RedDemon(const RedDemon& _Other) = delete;
	RedDemon(RedDemon&& _Other) noexcept = delete;
	RedDemon& operator=(const RedDemon& _Other) = delete;
	RedDemon& operator=(RedDemon&& _Other) noexcept = delete;


	void ChangeState(RedDemonState _State);
	void StateUpdate();
	//void DirAnimationCheck();

protected:

private:
	float4	MoveDir_;
	float	Time_;
	float	Speed_;
	float	AccSpeed_;
	float	Gravity_;
	float	AccGravity_;
	int		AttackCount_;


	GameEngineImage*		FloorColImage_;
	GameEngineCollision*	RedDemonCollision_;
	GameEngineCollision*	RedDemonAttackCollision_;
	GameEngineRenderer*		RedDemonAnimationRender_;
	RedDemonDir				CurrentDir_;
	std::string				AnimationName_;
	std::string				ChangeDirText_;

	void Start() override;
	void Update() override;
	void Render() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	//void CollisionFloorCheck();

	// 알파 확인차 임시 생성 :GameEngineRenderer* Render_;
	//===========================FSM============================
	// FSM 주의사항 : 각 해당 함수에서 FSM 다른 함수 사용 불가
	RedDemonState CurrentState_;
	//bool IsMoveKey();

	void IdleUpdate();
	void MoveUpdate();
	void JumpUpdate();
	void DownUpdate();
	void AttackUpdate();
	void ShakingSnowUpdate();
	void DefeatedUpdate();
	void DeathUpdate();

	void IdleStart();
	void MoveStart();
	void JumpStart();
	void DownStart();
	void AttackStart();
	void ShakingSnowStart();
	void DefeatedStart();
	void DeathStart();
};

