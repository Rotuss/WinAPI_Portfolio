#include "RedDemon.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

RedDemon::RedDemon()
	: MoveDir_(float4::ZERO)
	, Range_(100.f)
	, Speed_(200.0f)
	, SnowSpeed_(100.0f)
	, AccSpeed_(500.0f)
	, Gravity_(100.0f)
	, Time_(0.0f)
	, MoveTime_(0.3f)
	, JumpTime_(10.0f)
	, MeltingTime_(3.0f)
	, ShakingTime_(1.0f)
	, DeathTime_(0.5f)
	, DamageCount_(2)
	, StartMoveCount_(3)
	, DeathCheck_(true)
{
}

RedDemon::~RedDemon()
{
}

void RedDemon::ChangeState(RedDemonState _State)
{
	if (CurrentState_ != _State)
	{
		switch (_State)
		{
		case RedDemonState::STARTDOWN:
			StartDownStart();
			break;
		case RedDemonState::IDLE:
			IdleStart();
			break;
		case RedDemonState::STARTMOVE:
			StartMoveStart();
			break;
		case RedDemonState::MOVE:
			MoveStart();
			break;
		case RedDemonState::JUMP:
			JumpStart();
			break;
		case RedDemonState::DOWN:
			DownStart();
			break;
		case RedDemonState::ATTACK:
			AttackStart();
			break;
		case RedDemonState::SNOW1:
			Snow1Start();
			break;
		case RedDemonState::SNOW2:
			Snow2Start();
			break;
		case RedDemonState::SNOW3:
			Snow3Start();
			break;
		case RedDemonState::SNOWBALL:
			SnowBallStart();
			break;
		case RedDemonState::SHAKINGSNOW:
			ShakingSnowStart();
			break;
		case RedDemonState::DEFEATED:
			DefeatedStart();
			break;
		case RedDemonState::DEATH:
			DeathStart();
			break;
		case RedDemonState::MAX:
			break;
		default:
			break;
		}
	}

	CurrentState_ = _State;
}

void RedDemon::StateUpdate()
{
	switch (CurrentState_)
	{
	case RedDemonState::STARTDOWN:
		StartDownUpdate();
		break;
	case RedDemonState::IDLE:
		IdleUpdate();
		break;
	case RedDemonState::STARTMOVE:
		StartMoveUpdate();
		break;
	case RedDemonState::MOVE:
		MoveUpdate();
		break;
	case RedDemonState::JUMP:
		JumpUpdate();
		break;
	case RedDemonState::DOWN:
		DownUpdate();
		break;
	case RedDemonState::ATTACK:
		AttackUpdate();
		break;
	case RedDemonState::SNOW1:
		Snow1Update();
		break;
	case RedDemonState::SNOW2:
		Snow2Update();
		break;
	case RedDemonState::SNOW3:
		Snow3Update();
		break;
	case RedDemonState::SNOWBALL:
		SnowBallUpdate();
		break;
	case RedDemonState::SHAKINGSNOW:
		ShakingSnowUpdate();
		break;
	case RedDemonState::DEFEATED:
		DefeatedUpdate();
		break;
	case RedDemonState::DEATH:
		DeathUpdate();
		break;
	case RedDemonState::MAX:
		break;
	default:
		break;
	}
}

void RedDemon::Start()
{
	RedDemonCollision_ = CreateCollision("RedDemonHitBox", { 96, 96 });

	RedDemonAnimationRender_ = CreateRenderer();

	RedDemonAnimationRender_->CreateAnimation("RedDemon_Idle_Right.bmp", "Idle_Right", 0, 0, 0.0f, false);
	RedDemonAnimationRender_->CreateAnimation("RedDemon_Idle_Left.bmp", "Idle_Left", 0, 0, 0.0f, false);

	RedDemonAnimationRender_->CreateAnimation("RedDemon_Move_Right.bmp", "Move_Right", 0, 1, 0.12f, true);
	RedDemonAnimationRender_->CreateAnimation("RedDemon_Move_Left.bmp", "Move_Left", 0, 1, 0.12f, true);

	RedDemonAnimationRender_->CreateAnimation("RedDemon_Jump_Right.bmp", "Jump_Right", 0, 1, 0.1f, false);
	RedDemonAnimationRender_->CreateAnimation("RedDemon_Jump_Left.bmp", "Jump_Left", 0, 1, 0.1f, false);

	RedDemonAnimationRender_->CreateAnimation("RedDemon_Down_Right.bmp", "Down_Right", 0, 0, 0.0f, false);
	RedDemonAnimationRender_->CreateAnimation("RedDemon_Down_Left.bmp", "Down_Left", 0, 0, 0.0f, false);

	RedDemonAnimationRender_->CreateAnimation("RedDemon_Rolling.bmp", "Attack", 0, 3, 0.1f, false);

	RedDemonAnimationRender_->CreateAnimation("Snow1.bmp", "Snow1", 0, 0, 0.0f, false);
	RedDemonAnimationRender_->CreateAnimation("Snow2.bmp", "Snow2", 0, 0, 0.0f, false);
	RedDemonAnimationRender_->CreateAnimation("Snow3.bmp", "Snow3", 0, 0, 0.0f, false);
	RedDemonAnimationRender_->CreateAnimation("SnowballRolling.bmp", "SnowballRolling", 0, 3, 0.1f, true);
	RedDemonAnimationRender_->CreateAnimation("SnowBallEffect.bmp", "SnowBallEffect", 0, 1, 0.2f, true);

	RedDemonAnimationRender_->CreateAnimation("RedDemon_ShakingSnow.bmp", "ShakingSnow", 0, 1, 0.1f, true);

	RedDemonAnimationRender_->CreateAnimation("RedDemon_Defeated.bmp", "Defeated", 0, 3, 0.1f, true);

	RedDemonAnimationRender_->CreateAnimation("RedDemon_Death.bmp", "Death", 0, 0, 0.0f, false);

	RedDemonAnimationRender_->ChangeAnimation("Down_Right");
	RedDemonAnimationRender_->SetPivotType(RenderPivot::CENTER);

	//AnimationName_ = "Idle_";
	CurrentDir_ = RedDemonDir::RIGHT;
	CurrentState_ = RedDemonState::STARTDOWN;

	if (false == GameEngineInput::GetInst()->IsKey("ColDamage"))
	{
		GameEngineInput::GetInst()->CreateKey("ColDamage", VK_SPACE);
	}
}

void RedDemon::Update()
{
	//DirAnimationCheck();
	CollisionFloorCheck();
	StateUpdate();
}

void RedDemon::Render()
{
	//DebugRectRender();
}

void RedDemon::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void RedDemon::CollisionFloorCheck()
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