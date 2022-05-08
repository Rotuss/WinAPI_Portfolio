#include "Son.h"
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

Son::Son()
	: Time(0.8f)
	, MoveDir_(float4::ZERO)
	, LandingTime_(0.1f)
	, MeltingTime_(3.0f)
	, DeathTime_(0.5f)
	, ItemTime_(3.0f)
	, Speed_(150.0f)
	, StartSpeed_(800.0f)
	, SnowSpeed_(100.0f)
	, StartLandingCheck_(false)
	, DeathCheck_(true)
	, DamageCount_(2)
{
}

Son::~Son()
{
}

void Son::ChangeState(SonState _State)
{
	if (CurrentState_ != _State)
	{
		switch (_State)
		{
		case SonState::START:
			StartStart();
			break;
		case SonState::MOVE:
			MoveStart();
			break;
		case SonState::DOWN:
			DownStart();
			break;
		case SonState::LANDING:
			LandingStart();
			break;
		case SonState::SNOW1:
			Snow1Start();
			break;
		case SonState::SNOW2:
			Snow2Start();
			break;
		case SonState::SNOW3:
			Snow3Start();
			break;
		case SonState::SNOWBALL:
			SnowBallStart();
			break;
		case SonState::DEATH:
			DeathStart();
			break;
		case SonState::MAX:
			break;
		default:
			break;
		}
	}
	CurrentState_ = _State;
}

void Son::StateUpdate()
{
	switch (CurrentState_)
	{
	case SonState::START:
		StartUpdate();
		break;
	case SonState::MOVE:
		MoveUpdate();
		break;
	case SonState::DOWN:
		DownUpdate();
		break;
	case SonState::LANDING:
		LandingUpdate();
		break;
	case SonState::SNOW1:
		Snow1Update();
		break;
	case SonState::SNOW2:
		Snow2Update();
		break;
	case SonState::SNOW3:
		Snow3Update();
		break;
	case SonState::SNOWBALL:
		SnowBallUpdate();
		break;
	case SonState::DEATH:
		DeathUpdate();
		break;
	case SonState::MAX:
		break;
	default:
		break;
	}
}

void Son::Start()
{
	SonCollision_ = CreateCollision("EnemyHitBox", { 64, 80 });
	SonSnowCollision_ = CreateCollision("SnowBox", { 96, 96 });
	SonSnowCollision_->Off();

	// 애니메이션
	SonAnimationRender_ = CreateRenderer();

	SonAnimationRender_->CreateAnimation("Son_Move_Right.bmp", "Move_Right", 0, 1, 0.12f, true);
	SonAnimationRender_->CreateAnimation("Son_Move_Left.bmp", "Move_Left", 0, 1, 0.12f, true);
	
	SonAnimationRender_->CreateAnimation("Son_Down_Right.bmp", "Down_Right", 0, 0, 0.0f, false);
	SonAnimationRender_->CreateAnimation("Son_Down_Left.bmp", "Down_Left", 0, 0, 0.0f, false);

	SonAnimationRender_->CreateAnimation("Son_Landing_Right.bmp", "Landing_Right", 0, 0, 0.0f, false);
	SonAnimationRender_->CreateAnimation("Son_Landing_Left.bmp", "Landing_Left", 0, 0, 0.0f, false);

	SonAnimationRender_->CreateAnimation("Snow1.bmp", "Snow1", 0, 0, 0.0f, false);
	SonAnimationRender_->CreateAnimation("Snow2.bmp", "Snow2", 0, 0, 0.0f, false);
	SonAnimationRender_->CreateAnimation("Snow3.bmp", "Snow3", 0, 0, 0.0f, false);
	SonAnimationRender_->CreateAnimation("SnowballRolling.bmp", "SnowballRolling", 0, 3, 0.1f, true);
	SonAnimationRender_->CreateAnimation("SnowBallEffect.bmp", "SnowBallEffect", 0, 1, 0.2f, true);

	SonAnimationRender_->ChangeAnimation("Down_Left");
	SonAnimationRender_->SetPivotType(RenderPivot::CENTER);

	//AnimationName_ = "Idle_";
	CurrentDir_ = SonDir::LEFT;
	CurrentState_ = SonState::START;

	if (false == GameEngineInput::GetInst()->IsKey("ColDamage"))
	{
		GameEngineInput::GetInst()->CreateKey("ColDamage", VK_SPACE);
	}
}

void Son::Update()
{
	CollisionFloorCheck();
	StateUpdate();
}

void Son::Render()
{
}

void Son::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void Son::RandomItem()
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

void Son::CollisionFloorCheck()
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
