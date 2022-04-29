#include "Frog.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

Frog::Frog()
	: MoveDir_(float4::ZERO)
	, Range_(30.f)
	, Speed_(150.0f)
	, SnowSpeed_(100.0f)
	, AccSpeed_(500.0f)
	, Gravity_(100.0f)
	, Time_(0.0f)
	, MoveTime_(0.3f)
	, JumpTime_(10.0f)
	, AttackTime_(1.5f)
	, MeltingTime_(3.0f)
	, ShakingTime_(1.0f)
	, DeathTime_(0.5f)
	, DamageCount_(2)
	, StartMoveCount_(3)
	, DeathCheck_(true)
{
}

Frog::~Frog()
{
}

void Frog::ChangeState(FrogState _State)
{
	if (CurrentState_ != _State)
	{
		switch (_State)
		{
		case FrogState::STARTDOWN:
			StartDownStart();
			break;
		case FrogState::IDLE:
			IdleStart();
			break;
		case FrogState::STARTMOVE:
			StartMoveStart();
			break;
		case FrogState::MOVE:
			MoveStart();
			break;
		case FrogState::JUMP:
			JumpStart();
			break;
		case FrogState::DOWN:
			DownStart();
			break;
		case FrogState::ATTACK:
			AttackStart();
			break;
		case FrogState::SNOW1:
			Snow1Start();
			break;
		case FrogState::SNOW2:
			Snow2Start();
			break;
		case FrogState::SNOW3:
			Snow3Start();
			break;
		case FrogState::SNOWBALL:
			SnowBallStart();
			break;
		case FrogState::SHAKINGSNOW:
			ShakingSnowStart();
			break;
		case FrogState::DEFEATED:
			DefeatedStart();
			break;
		case FrogState::DEATH:
			DeathStart();
			break;
		case FrogState::MAX:
			break;
		default:
			break;
		}
	}

	CurrentState_ = _State;
}

void Frog::StateUpdate()
{
	switch (CurrentState_)
	{
	case FrogState::STARTDOWN:
		StartDownUpdate();
		break;
	case FrogState::IDLE:
		IdleUpdate();
		break;
	case FrogState::STARTMOVE:
		StartMoveUpdate();
		break;
	case FrogState::MOVE:
		MoveUpdate();
		break;
	case FrogState::JUMP:
		JumpUpdate();
		break;
	case FrogState::DOWN:
		DownUpdate();
		break;
	case FrogState::ATTACK:
		AttackUpdate();
		break;
	case FrogState::SNOW1:
		Snow1Update();
		break;
	case FrogState::SNOW2:
		Snow2Update();
		break;
	case FrogState::SNOW3:
		Snow3Update();
		break;
	case FrogState::SNOWBALL:
		SnowBallUpdate();
		break;
	case FrogState::SHAKINGSNOW:
		ShakingSnowUpdate();
		break;
	case FrogState::DEFEATED:
		DefeatedUpdate();
		break;
	case FrogState::DEATH:
		DeathUpdate();
		break;
	case FrogState::MAX:
		break;
	default:
		break;
	}
}

void Frog::Start()
{
	FrogCollision_ = CreateCollision("FrogHitBox", { 96, 104 });

	// 애니메이션
	FrogAnimationRender_ = CreateRenderer();

	FrogAnimationRender_->CreateAnimation("Frog_Idle_Right.bmp", "Idle_Right", 0, 0, 0.0f, false);
	FrogAnimationRender_->CreateAnimation("Frog_Idle_Left.bmp", "Idle_Left", 0, 0, 0.0f, false);

	FrogAnimationRender_->CreateAnimation("Frog_Move_Right.bmp", "Move_Right", 0, 1, 0.12f, true);
	FrogAnimationRender_->CreateAnimation("Frog_Move_Left.bmp", "Move_Left", 0, 1, 0.12f, true);

	FrogAnimationRender_->CreateAnimation("Frog_Jump_Right.bmp", "Jump_Right", 0, 0, 0.0f, false);
	FrogAnimationRender_->CreateAnimation("Frog_Jump_Left.bmp", "Jump_Left", 0, 0, 0.0f, false);

	//EnemyAnimationRender_->CreateAnimation("Frog_Jump_Right.bmp", "Down_Right", 0, 0, 0.0f, false);
	//EnemyAnimationRender_->CreateAnimation("Frog_Jump_Left.bmp", "Down_Left", 0, 0, 0.0f, false);

	FrogAnimationRender_->CreateAnimation("Frog_ThrowingFire_Right.bmp", "Attack_Right", 0, 0, 0.0f, false);
	FrogAnimationRender_->CreateAnimation("Frog_ThrowingFire_Left.bmp", "Attack_Left", 0, 0, 0.0f, false);

	FrogAnimationRender_->CreateAnimation("Snow1.bmp", "Snow1", 0, 0, 0.0f, false);
	FrogAnimationRender_->CreateAnimation("Snow2.bmp", "Snow2", 0, 0, 0.0f, false);
	FrogAnimationRender_->CreateAnimation("Snow3.bmp", "Snow3", 0, 0, 0.0f, false);
	FrogAnimationRender_->CreateAnimation("SnowballRolling.bmp", "SnowballRolling", 0, 3, 0.1f, true);
	FrogAnimationRender_->CreateAnimation("SnowBallEffect.bmp", "SnowBallEffect", 0, 1, 0.2f, true);
	
	FrogAnimationRender_->CreateAnimation("Frog_ShakingSnow.bmp", "ShakingSnow", 0, 1, 0.1f, true);

	FrogAnimationRender_->CreateAnimation("Frog_Defeated.bmp", "Defeated", 0, 3, 0.1f, true);

	FrogAnimationRender_->CreateAnimation("Frog_Death.bmp", "Death", 0, 0, 0.0f, false);

	FrogAnimationRender_->ChangeAnimation("Jump_Right");
	FrogAnimationRender_->SetPivotType(RenderPivot::CENTER);

	//AnimationName_ = "Idle_";
	CurrentDir_ = FrogDir::RIGHT;
	CurrentState_ = FrogState::STARTDOWN;

	if (false == GameEngineInput::GetInst()->IsKey("ColDamage"))
	{
		GameEngineInput::GetInst()->CreateKey("ColDamage", VK_SPACE);
	}
}

void Frog::Update()
{
	CollisionFloorCheck();
	StateUpdate();
}

void Frog::Render()
{
	//DebugRectRender();
}

void Frog::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void Frog::CollisionFloorCheck()
{
	if (strcmp(GetLevel()->GetNameConstPtr(), "Floor1") == 0)
	{
		FloorColImage_ = GameEngineImageManager::GetInst()->Find("ColFloor1.bmp");
	}
	else if (strcmp(GetLevel()->GetNameConstPtr(), "Floor2") == 0)
	{
		FloorColImage_ = GameEngineImageManager::GetInst()->Find("ColFloor2.bmp");
	}
	else if (strcmp(GetLevel()->GetNameConstPtr(), "Floor3") == 0)
	{
		FloorColImage_ = GameEngineImageManager::GetInst()->Find("ColFloor3.bmp");
	}

	if (nullptr == FloorColImage_)
	{
		MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다.");
	}
}