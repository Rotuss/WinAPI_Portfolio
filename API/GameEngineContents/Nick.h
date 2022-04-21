#pragma once
#include <GameEngine/GameEngineActor.h>

// ��� ��ü�� 1���� 1���� ���¸��� ����
// �÷��̾�� 1���� 1���� �Լ� �ۿ� ������ �� ����

enum class NickState
{
	IDLE,
	MOVE,
	JUMP,
	ATTACK,
	DIE,

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

	static Nick* MainPlayer;
	// static std::vector<InventoryItem>;
	
	//===========================FSM============================
	void ChangeState(NickState _State);
	void StateUpdate();

protected:
	void DirAnimationCheck();

private:
	float4 MoveDir_;
	float Time_;
	float Speed_;
	float AccSpeed_;
	float Gravity_;
	float AccGravity_;

	GameEngineImage*		FloorColImage_;
	GameEngineCollision*	PlayerCollision_;
	GameEngineRenderer*		NickAnimationRender_;
	NickDir					CurrentDir_;
	std::string				AnimationName_;
	std::string				ChangeDirText_;

	void Start() override;
	void Update() override;
	void Render() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	
	void NextCheck();
	void WallCheck();
	// ���� Ȯ���� �ӽ� ���� :GameEngineRenderer* Render_;
	//===========================FSM============================
	// FSM ���ǻ��� : �� �ش� �Լ����� FSM �ٸ� �Լ� ��� �Ұ�
	NickState CurrentState_;
	bool IsMoveKey();

	void IdleUpdate();
	void MoveUpdate();
	void JumpUpdate();
	void AttackUpdate();

	void IdleStart();
	void MoveStart();
	void JumpStart();
	void AttackStart();

	void KeyMove();
};

