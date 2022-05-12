#pragma once
#include <GameEngine/GameEngineActor.h>

enum class SonState
{
	START,
	MOVE,
	DOWN,
	LANDING,
	SNOW1,
	SNOW2,
	SNOW3,
	SNOWBALL,
	BLUESNOWBALL,
	DEATH,

	MAX
};
enum class SonDir
{
	LEFT,
	RIGHT,
};
// Ό³Έν : 
class GameEngineImage;
class GameEngineCollision;
class Son :public GameEngineActor
{
public:
	// constrcuter destructer
	Son();
	~Son();

	// delete Function
	Son(const Son& _Other) = delete;
	Son(Son&& _Other) noexcept = delete;
	Son& operator=(const Son& _Other) = delete;
	Son& operator=(Son&& _Other) noexcept = delete;

	float Time;
	void ChangeState(SonState _State);
	void StateUpdate();

protected:

private:
	float4	MoveDir_;
	float	Time_;
	float	LandingTime_;
	float	MeltingTime_;
	float	DeathTime_;
	float	ItemTime_;
	float	Speed_;
	float	StartSpeed_;
	float	SnowSpeed_;
	bool	StartLandingCheck_;
	bool	DeathCheck_;
	int		DamageCount_;

	GameEngineImage*		FloorColImage_;
	GameEngineCollision*	SonCollision_;
	GameEngineCollision*	SonRCollision_;
	GameEngineCollision*	SonLCollision_;
	GameEngineCollision*	SonAttackCollision_;
	GameEngineCollision*	SonSnowCollision_;
	GameEngineCollision*	SonSnowRCollision_;
	GameEngineCollision*	SonSnowLCollision_;
	GameEngineCollision*	SonSnowBallCollision_;
	GameEngineCollision*	SonSnowBallRCollision_;
	GameEngineCollision*	SonSnowBallLCollision_;
	GameEngineCollision*	SonBlueSnowBallCollision_;
	GameEngineRenderer*		SonAnimationRender_;
	SonDir					CurrentDir_;
	std::string				AnimationName_;
	std::string				ChangeDirText_;
	
	void Start() override;
	void Update() override;
	void Render() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void RandomItem();
	void CollisionFloorCheck();

	SonState CurrentState_;

	void StartUpdate();
	void MoveUpdate();
	void DownUpdate();
	void LandingUpdate();
	void Snow1Update();
	void Snow2Update();
	void Snow3Update();
	void SnowBallUpdate();
	void BlueSnowBallUpdate();
	void DeathUpdate();

	void StartStart();
	void MoveStart();
	void DownStart();
	void LandingStart();
	void Snow1Start();
	void Snow2Start();
	void Snow3Start();
	void SnowBallStart();
	void BlueSnowBallStart();
	void DeathStart();
};

