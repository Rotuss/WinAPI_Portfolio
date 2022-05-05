#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineActor.h>

// 어떠한 객체는 1번에 1개의 상태만이 존재
// 플레이어는 1번에 1개의 함수 밖에 실행할 수 없음

enum class NickState
{
	IDLE,
	MOVE,
	JUMP,
	DOWN,
	ATTACK,
	PUSH,
	APPEAR,
	DEATH,
	NEXTFLOOR,

	MAX
};
enum class NickDir
{
	LEFT,
	RIGHT,
};
// 설명 : 
class GameEngineImage;
class GameEngineCollision;
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

	// 접근하기 편리하게 static 선언
	static Nick* MainPlayer;
	// static std::vector<InventoryItem>;
	static GameEngineSoundPlayer BgmPlayer_;

	//===========================FSM============================
	void ChangeState(NickState _State);
	void StateUpdate();
	void DirAnimationCheck();
	void NoDamage();

	float NextFloorTime_;

protected:
	

private:
	float4	MoveDir_;
	float	Time_;
	float	AppTime_;
	float	DTime_;
	float	Speed_;
	float	PushSpeed_;
	//float	Gravity_;
	//float	AccGravity_;
	int		LifeCount_;
	bool	NoDamageCheck_;

	GameEngineImage*		FloorColImage_;
	GameEngineCollision*	PlayerCollision_;
	GameEngineCollision*	PlayerAttackCollision_;
	GameEngineCollision*	PushTargetCollision_;
	GameEngineRenderer*		NickAnimationRender_;
	NickDir					CurrentDir_;
	std::string				AnimationName_;
	std::string				ChangeDirText_;

	void Start() override;
	void Update() override;
	void Render() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	
	void CameraLock();
	
	void FloorOut();

	void CollisionFloorCheck();

	// 알파 확인차 임시 생성 :GameEngineRenderer* Render_;
	//===========================FSM============================
	// FSM 주의사항 : 각 해당 함수에서 FSM 다른 함수 사용 불가
	NickState PrevState_;
	NickState CurrentState_;
	bool IsMoveKey();

	void IdleUpdate();
	void MoveUpdate();
	void JumpUpdate();
	void DownUpdate();
	void AttackUpdate();
	void PushUpdate();
	void AppearUpdate();
	void DeathUpdate();
	void NextFloorUpdate();

	void IdleStart();
	void MoveStart();
	void JumpStart();
	void DownStart();
	void AttackStart();
	void PushStart();
	void AppearStart();
	void DeathStart();
	void NextFloorStart();
	//void FloorCollisionCheckMoveGround();
};

