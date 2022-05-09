#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineActor.h>

enum class YellowTrollState
{
	STARTDOWN,
	IDLE,
	STARTMOVE,
	MOVE,
	JUMP,
	DOWN,
	SNOW1,
	SNOW2,
	SNOW3,
	SNOWBALL,
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

	void ChangeState(YellowTrollState _State);
	void StateUpdate();

protected:

private:
	float4	MoveDir_;
	float	Range_;
	float	Time_;
	float	MoveTime_;
	float	JumpTime_;
	float	MeltingTime_;
	float	ShakingTime_;
	float	SnowBallDeathTime_;
	float	DeathTime_;
	float	ItemTime_;
	float	Speed_;
	float	SnowSpeed_;
	bool	DeathCheck_;
	int		DamageCount_;
	int		StartMoveCount_;
	
	GameEngineImage*		FloorColImage_;
	GameEngineCollision*	YellowTrollCollision_;
	GameEngineCollision*	YellowTrollAttackCollision_;
	GameEngineCollision*	YellowTrollSnowCollision_;
	GameEngineCollision*	YellowTrollSnowRCollision_;
	GameEngineCollision*	YellowTrollSnowLCollision_;
	GameEngineCollision*	YellowTrollSnowBallCollision_;
	GameEngineCollision*	YellowTrollSnowBallRCollision_;
	GameEngineCollision*	YellowTrollSnowBallLCollision_;
	GameEngineRenderer*		YellowTrollAnimationRender_;
	YellowTrollDir			CurrentDir_;
	std::string				AnimationName_;
	std::string				ChangeDirText_;

	void Start() override;
	void Update() override;
	void Render() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void RandomItem();
	void CollisionFloorCheck();
	
	YellowTrollState CurrentState_;

	void StartDownUpdate();
	void IdleUpdate();
	void StartMoveUpdate();
	void MoveUpdate();
	void JumpUpdate();
	void DownUpdate();
	void Snow1Update();
	void Snow2Update();
	void Snow3Update();
	void SnowBallUpdate();
	void ShakingSnowUpdate();
	void DefeatedUpdate();
	void DeathUpdate();

	void StartDownStart();
	void IdleStart();
	void StartMoveStart();
	void MoveStart();
	void JumpStart();
	void DownStart();
	void Snow1Start();
	void Snow2Start();
	void Snow3Start();
	void SnowBallStart();
	void ShakingSnowStart();
	void DefeatedStart();
	void DeathStart();
};

