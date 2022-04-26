#pragma once
#include <GameEngine/GameEngineActor.h>

// ��� ��ü�� 1���� 1���� ���¸��� ����
// �÷��̾�� 1���� 1���� �Լ� �ۿ� ������ �� ����

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

	MAX
};
enum class NickDir
{
	LEFT,
	RIGHT,
};
// ���� : 
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

	// �����ϱ� ���ϰ� static ����
	static Nick* MainPlayer;
	// static std::vector<InventoryItem>;
	
	//===========================FSM============================
	void ChangeState(NickState _State);
	void StateUpdate();
	void DirAnimationCheck();

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

	GameEngineImage*		FloorColImage_;
	GameEngineCollision*	PlayerCollision_;
	GameEngineCollision*	PlayerAttackCollision_;
	GameEngineRenderer*		NickAnimationRender_;
	NickDir					CurrentDir_;
	std::string				AnimationName_;
	std::string				ChangeDirText_;

	void Start() override;
	void Update() override;
	void Render() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	
	void CameraLock();
	
	void NextCheck();
	void WallCheck();

	void CollisionFloorCheck();

	// ���� Ȯ���� �ӽ� ���� :GameEngineRenderer* Render_;
	//===========================FSM============================
	// FSM ���ǻ��� : �� �ش� �Լ����� FSM �ٸ� �Լ� ��� �Ұ�
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

	void IdleStart();
	void MoveStart();
	void JumpStart();
	void DownStart();
	void AttackStart();
	void PushStart();
	void AppearStart();
	void DeathStart();

	//void FloorCollisionCheckMoveGround();
};

