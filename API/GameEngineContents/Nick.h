#pragma once
#include <GameEngine/GameEngineActor.h>

// 어떠한 객체는 1번에 1개의 상태만이 존재
// 플레이어는 1번에 1개의 함수 밖에 실행할 수 없음

enum NickState
{
	IDLE,
	MOVE,
	ATTACK,

	MAX
};
enum NickDir
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

	//===========================FSM============================
	void ChangeState(NickState _State);
	void StateUpdate();

protected:
	GameEngineRenderer* NickAnimationRender;
	NickDir CurrentDir_;
	std::string AnimationName_;
	
	void DirAnimationCheck();
	void NickStateUpdate();

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
	// FSM 주의사항 : 각 해당 함수에서 FSM 다른 함수 사용 불가
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

