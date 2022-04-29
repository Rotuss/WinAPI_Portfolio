#include "FrogFire.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>

FrogFire::FrogFire()
	:DeathTime_(0.5f)
{
}

FrogFire::~FrogFire()
{
}

void FrogFire::DirFireCheck()
{
	FireDir FCheckDir_ = FCurrentDir_;

	if (ChangeFDirText_ == "Right")
	{
		FCheckDir_ = FireDir::RIGHT;
	}
	if (ChangeFDirText_ == "Left")
	{
		FCheckDir_ = FireDir::LEFT;
	}

	if (FCheckDir_ != FCurrentDir_)
	{
		FireAnimationRender_->ChangeAnimation("FrogFire_" + ChangeFDirText_);
		FCurrentDir_ = FCheckDir_;
	}
}

void FrogFire::Start()
{
	FireCollision_ = CreateCollision("FireHitBox", { 96, 64 });

	FireAnimationRender_ = CreateRenderer();
	FireAnimationRender_->CreateAnimation("FrogFire_Left.bmp", "FrogFire_Left", 0, 0, 0.0f, false);
	FireAnimationRender_->CreateAnimation("FrogFire_Right.bmp", "FrogFire_Right", 0, 0, 0.0f, false);
	FireAnimationRender_->CreateAnimation("FrogFire_Boom.bmp", "FrogFire_Boom", 0, 0, 0.0f, false);
	FireAnimationRender_->ChangeAnimation("FrogFire_Left");
	//Time = 2.0f;

	XSpeed_ = 500.0f;
}

void FrogFire::Update()
{
	DeathTime_ -= GameEngineTime::GetDeltaTime();
	DirFireCheck();
	CollisionFloorCheck();
	float4 ResultDir = float4::ZERO;
	// ��� ���� ���ص� float4
	ResultDir += FireDir_ * GameEngineTime::GetDeltaTime() * XSpeed_;

	int RColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ 15.0f, 0.0f });
	int LColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ -15.0f, 0.0f });
	if (RGB(0, 0, 0) == RColor || RGB(0, 0, 0) == LColor || true == FireCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		ResultDir = float4::ZERO;
		FireAnimationRender_->ChangeAnimation("FrogFire_Boom");
		DeathTime_ = 0.5f;
		if (DeathTime_ <= 0)
		{
			int a = 0;
			//FireAnimationRender_->Off();
		}
		return;
	}
	if (DeathTime_ <= 0)
	{
		//FireAnimationRender_->Off();
		Death();
	}
	
	SetMove(ResultDir);
}

void FrogFire::CollisionFloorCheck()
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
		MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�.");
	}
}
