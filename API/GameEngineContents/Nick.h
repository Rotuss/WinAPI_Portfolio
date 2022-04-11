#pragma once
#include <GameEngine/GameEngineActor.h>

// ��� ��ü�� 1���� 1���� ���¸��� ����
// �÷��̾�� 1���� 1���� �Լ� �ۿ� ������ �� ����

enum NickState
{
	IDLE,
	MOVE,
	ATTACK,

	MAX
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

	//===========================FSM============================
	void ChangeState(NickState _State);
	void StateUpdate();

protected:

private:
	float Speed_;
	float Gravity_;
	float AccGravity_;

	GameEngineImage* FloorColImage_;
	GameEngineCollision* PlayerCollision_;

	void Start() override;
	void Update() override;
	void Render() override;

	void NextCheck();
	void WallCheck();

	//===========================FSM============================
	// FSM ���ǻ��� : �� �ش� �Լ����� FSM �ٸ� �Լ� ��� �Ұ�
	NickState CurrentState_;
	bool IsMoveKey();

	void IdleUpdate();
	void MoveUpdate();
	void AttackUpdate();

	void IdleStart();
	void MoveStart();
	void AttackStart();

	void KeyMove();
};

