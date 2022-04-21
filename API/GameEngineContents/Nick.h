#pragma once
#include <GameEngine/GameEngineActor.h>

// 어떠한 객체는 1번에 1개의 상태만이 존재
// 플레이어는 1번에 1개의 함수 밖에 실행할 수 없음

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
	// 알파 확인차 임시 생성 :GameEngineRenderer* Render_;
	//===========================FSM============================
	// FSM 주의사항 : 각 해당 함수에서 FSM 다른 함수 사용 불가
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

