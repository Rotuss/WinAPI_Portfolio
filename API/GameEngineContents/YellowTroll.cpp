#include "YellowTroll.h"
#include "SnowLevel.h"
#include "Candy.h"
#include "Lollipop.h"
#include "Mushroom.h"
#include "StickIceCream.h"
#include "Sandwich.h"
#include "Cake.h"
#include "RedPotion.h"
#include "BluePotion.h"
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

YellowTroll::YellowTroll()
	: MoveDir_(float4::ZERO)
	, Range_(30.f)
	, Speed_(150.0f)
	, SnowSpeed_(100.0f)
	, Time_(0.0f)
	, MoveTime_(0.3f)
	, JumpTime_(10.0f)
	, MeltingTime_(3.0f)
	, ShakingTime_(1.0f)
	, SnowBallDeathTime_(5.0f)
	, DeathTime_(0.5f)
	, ItemTime_(3.0f)
	, DamageCount_(2)
	, StartMoveCount_(3)
	, DeathCheck_(true)
{
}

YellowTroll::~YellowTroll()
{
	SnowLevel* Level_ = reinterpret_cast<SnowLevel*>(GetLevel());
	Level_->Enemycount_ -= 1;
}

void YellowTroll::ChangeState(YellowTrollState _State)
{
	if (CurrentState_ != _State)
	{
		switch (_State)
		{
		case YellowTrollState::STARTDOWN:
			StartDownStart();
			break;
		case YellowTrollState::IDLE:
			IdleStart();
			break;
		case YellowTrollState::STARTMOVE:
			StartMoveStart();
			break;
		case YellowTrollState::MOVE:
			MoveStart();
			break;
		case YellowTrollState::JUMP:
			JumpStart();
			break;
		case YellowTrollState::DOWN:
			DownStart();
			break;
		case YellowTrollState::SNOW1:
			Snow1Start();
			break;
		case YellowTrollState::SNOW2:
			Snow2Start();
			break;
		case YellowTrollState::SNOW3:
			Snow3Start();
			break;
		case YellowTrollState::SNOWBALL:
			SnowBallStart();
			break;
		case YellowTrollState::SHAKINGSNOW:
			ShakingSnowStart();
			break;
		case YellowTrollState::DEFEATED:
			DefeatedStart();
			break;
		case YellowTrollState::DEATH:
			DeathStart();
			break;
		case YellowTrollState::MAX:
			break;
		default:
			break;
		}
	}

	CurrentState_ = _State;
}

void YellowTroll::StateUpdate()
{
	switch (CurrentState_)
	{
	case YellowTrollState::STARTDOWN:
		StartDownUpdate();
		break;
	case YellowTrollState::IDLE:
		IdleUpdate();
		break;
	case YellowTrollState::STARTMOVE:
		StartMoveUpdate();
		break;
	case YellowTrollState::MOVE:
		MoveUpdate();
		break;
	case YellowTrollState::JUMP:
		JumpUpdate();
		break;
	case YellowTrollState::DOWN:
		DownUpdate();
		break;
	case YellowTrollState::SNOW1:
		Snow1Update();
		break;
	case YellowTrollState::SNOW2:
		Snow2Update();
		break;
	case YellowTrollState::SNOW3:
		Snow3Update();
		break;
	case YellowTrollState::SNOWBALL:
		SnowBallUpdate();
		break;
	case YellowTrollState::SHAKINGSNOW:
		ShakingSnowUpdate();
		break;
	case YellowTrollState::DEFEATED:
		DefeatedUpdate();
		break;
	case YellowTrollState::DEATH:
		DeathUpdate();
		break;
	case YellowTrollState::MAX:
		break;
	default:
		break;
	}
}

void YellowTroll::Start()
{
	YellowTrollCollision_ = CreateCollision("EnemyHitBox", { 70, 90 });
	YellowTrollRCollision_ = CreateCollision("EnemyRHitBox", { 5, 10 }, { -50, 0 });
	YellowTrollLCollision_ = CreateCollision("EnemyLHitBox", { 5, 10 }, { -50, 0 });
	YellowTrollSnowCollision_ = CreateCollision("SnowBox", { 96, 96 });
	YellowTrollSnowCollision_->Off();

	// 애니메이션
	YellowTrollAnimationRender_ = CreateRenderer();

	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Idle_Right.bmp", "Idle_Right", 0, 0, 0.0f, false);
	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Idle_Left.bmp", "Idle_Left", 0, 0, 0.0f, false);

	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Move_Right.bmp", "Move_Right", 0, 1, 0.12f, true);
	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Move_Left.bmp", "Move_Left", 0, 1, 0.12f, true);

	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Jump_Right.bmp", "Jump_Right", 0, 1, 0.1f, false);
	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Jump_Left.bmp", "Jump_Left", 0, 1, 0.1f, false);

	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Down_Right.bmp", "Down_Right", 0, 0, 0.0f, false);
	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Down_Left.bmp", "Down_Left", 0, 0, 0.0f, false);

	YellowTrollAnimationRender_->CreateAnimation("Snow1.bmp", "Snow1", 0, 0, 0.0f, false);
	YellowTrollAnimationRender_->CreateAnimation("Snow2.bmp", "Snow2", 0, 0, 0.0f, false);
	YellowTrollAnimationRender_->CreateAnimation("Snow3.bmp", "Snow3", 0, 0, 0.0f, false);
	YellowTrollAnimationRender_->CreateAnimation("SnowballRolling.bmp", "SnowballRolling", 0, 3, 0.1f, true);
	YellowTrollAnimationRender_->CreateAnimation("SnowBallEffect.bmp", "SnowBallEffect", 0, 1, 0.2f, true);
	
	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_ShakingSnow.bmp", "ShakingSnow", 0, 1, 0.1f, true);

	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Defeated.bmp", "Defeated", 0, 3, 0.1f, true);

	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Death.bmp", "Death", 0, 0, 0.0f, false);

	YellowTrollAnimationRender_->ChangeAnimation("Down_Right");
	YellowTrollAnimationRender_->SetPivotType(RenderPivot::CENTER);

	//AnimationName_ = "Idle_";
	CurrentDir_ = YellowTrollDir::RIGHT;
	CurrentState_ = YellowTrollState::STARTDOWN;

	if (false == GameEngineInput::GetInst()->IsKey("ColDamage"))
	{
		GameEngineInput::GetInst()->CreateKey("ColDamage", VK_SPACE);
	}
}

void YellowTroll::Update()
{
	CollisionFloorCheck();
	StateUpdate();
}

void YellowTroll::Render()
{
	//DebugRectRender();
}

void YellowTroll::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void YellowTroll::RandomItem()
{
	GameEngineRandom RandomValue_;
	int RandomItemNum = RandomValue_.RandomInt(0, 7);

	if (0 == RandomItemNum)
	{
		Candy* CandyActor = GetLevel()->CreateActor<Candy>(1);
		CandyActor->SetPosition(GetPosition());

	}
	else if (1 == RandomItemNum)
	{
		Lollipop* LollipopActor = GetLevel()->CreateActor<Lollipop>(1);
		LollipopActor->SetPosition(GetPosition());
	}
	else if (2 == RandomItemNum)
	{
		Mushroom* MushroomActor = GetLevel()->CreateActor<Mushroom>(1);
		MushroomActor->SetPosition(GetPosition());
	}
	else if (3 == RandomItemNum)
	{
		StickIceCream* StickIceCreamActor = GetLevel()->CreateActor<StickIceCream>(1);
		StickIceCreamActor->SetPosition(GetPosition());
	}
	else if (4 == RandomItemNum)
	{
		Sandwich* SandwichActor = GetLevel()->CreateActor<Sandwich>(1);
		SandwichActor->SetPosition(GetPosition());
	}
	else if (5 == RandomItemNum)
	{
		Cake* CakeActor = GetLevel()->CreateActor<Cake>(1);
		CakeActor->SetPosition(GetPosition());
	}
	else if (6 == RandomItemNum)
	{
		RedPotion* RedPotionActor = GetLevel()->CreateActor<RedPotion>(1);
		RedPotionActor->SetPosition(GetPosition());
	}
	else if (7 == RandomItemNum)
	{
		BluePotion* BluePotionActor = GetLevel()->CreateActor<BluePotion>(1);
		BluePotionActor->SetPosition(GetPosition());
	}
}

void YellowTroll::CollisionFloorCheck()
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
