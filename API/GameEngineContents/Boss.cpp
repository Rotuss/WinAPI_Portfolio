#include "Boss.h"
#include "SnowLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

Boss::Boss()
	: JumpTime_(5.0f)
	, StandbyTIme_(0.12f)
	, AttackTime_(3.0f)
	, DefeatedTime1_(1.0f)
	, DefeatedTime2_(1.0f)
	, DamageCount_(3)
	, JumpCount_(5)
{
}

Boss::~Boss()
{
	SnowLevel* Level_ = reinterpret_cast<SnowLevel*>(GetLevel());
	Level_->Enemycount_ -= 1;
}

void Boss::ChangeState(BossState _State)
{
	if (CurrentState_ != _State)
	{
		switch (_State)
		{
		case BossState::STARTDOWN:
			StartDownStart();
			break;
		case BossState::IDLE:
			IdleStart();
			break;
		case BossState::JUMP:
			JumpStart();
			break;
		case BossState::ATTACK:
			AttackStart();
			break;
		case BossState::DEFEATED:
			DefeatedStart();
			break;
		case BossState::DEATH:
			DeathStart();
			break;
		case BossState::MAX:
			break;
		default:
			break;
		}
	}

	CurrentState_ = _State;
}

void Boss::StateUpdate()
{
	switch (CurrentState_)
	{
	case BossState::STARTDOWN:
		StartDownUpdate();
		break;
	case BossState::IDLE:
		IdleUpdate();
		break;
	case BossState::JUMP:
		JumpUpdate();
		break;
	case BossState::ATTACK:
		AttackUpdate();
		break;
	case BossState::DEFEATED:
		DefeatedUpdate();
		break;
	case BossState::DEATH:
		DeathUpdate();
		break;
	case BossState::MAX:
		break;
	default:
		break;
	}
}

void Boss::Start()
{
	BossCollision_ = CreateCollision("BossHitBox", { 224,160 }, { 0,60 });
	BossHeadCollision_ = CreateCollision("BossHeadHitBox", { 150,125 }, { -37,-82 });

	BossAnimationRender_ = CreateRenderer();

	BossAnimationRender_->CreateAnimation("Boss_Idle.bmp", "Idle", 0, 0, 0.0f, false);
	BossAnimationRender_->CreateAnimation("Boss_Jump.bmp", "Jump", 0, 0, 0.0f, false);
	BossAnimationRender_->CreateAnimation("Boss_Defeated.bmp", "Defeated", 0, 0, 0.0f, false);
	BossAnimationRender_->CreateAnimation("Boss_Death.bmp", "Death", 0, 1, 1.0f, false);

	BossAnimationRender_->ChangeAnimation("Idle");
	BossAnimationRender_->SetPivotType(RenderPivot::CENTER);

	CurrentDir_ = BossDir::LEFT;
	CurrentState_ = BossState::STARTDOWN;
}

void Boss::Update()
{
	CollisionFloorCheck();
	StateUpdate();
}

void Boss::Render()
{
	//DebugRectRender();
}

void Boss::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void Boss::CollisionFloorCheck()
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
	else if (strcmp(GetLevel()->GetNameConstPtr(), "BossFloor") == 0)
	{
		FloorColImage_ = GameEngineImageManager::GetInst()->Find("ColFloorBoss.bmp");
	}

	if (nullptr == FloorColImage_)
	{
		MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다.");
	}
}
