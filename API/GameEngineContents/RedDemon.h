#pragma once
#include <GameEngine/GameEngineActor.h>

enum class RedDemonState
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
	float	Range_;
	float	Time_;
	float	MoveTime_;
	float	JumpTime_;
	float	MeltingTime_;
	float	ShakingTime_;
	float	Speed_;
	float	SnowSpeed_;
	float	AccSpeed_;
	float	Gravity_;
	float	AccGravity_;
	int		DamageCount_;
	int		StartMoveCount_;


	GameEngineImage*		FloorColImage_;
	GameEngineCollision*	RedDemonCollision_;
	GameEngineCollision*	RedDemonSnowRCollision_;
	GameEngineCollision*	RedDemonSnowLCollision_;
	GameEngineRenderer*		RedDemonAnimationRender_;
	RedDemonDir				CurrentDir_;
	std::string				AnimationName_;
	std::string				ChangeDirText_;

	void Start() override;
	void Update() override;
	void Render() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	void CollisionFloorCheck();

	// 알파 확인차 임시 생성 :GameEngineRenderer* Render_;
	//===========================FSM============================
	// FSM 주의사항 : 각 해당 함수에서 FSM 다른 함수 사용 불가
	RedDemonState CurrentState_;
	//bool IsMoveKey();

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
	void ShakingSnowStart();
	void DefeatedStart();
	void DeathStart();
};

