#include "SnowBullet.h"
#include "BluePotion.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>

SnowBullet::SnowBullet()
	: Time(0.8f)
	, YDir_(float4::DOWN * 500.0f)
{
}

SnowBullet::~SnowBullet()
{
}

void SnowBullet::DirBulletCheck()
{
	BulletDir BCheckDir_ = BCurrentDir_;

	if (ChangeBDirText_ == "Right")
	{
		if (true == BluePotion::BPCheck_)
		{
			BulletAnimationRender_->ChangeAnimation("BP_SnowBullet_Right");
			return;
		}
		BCheckDir_ = BulletDir::RIGHT;
	}
	if (ChangeBDirText_ == "Left")
	{
		if (true == BluePotion::BPCheck_)
		{
			BulletAnimationRender_->ChangeAnimation("BP_SnowBullet_Left");
			return;
		}
		BCheckDir_ = BulletDir::LEFT;
	}

	if (BCheckDir_ != BCurrentDir_)
	{
		if (false == BluePotion::BPCheck_)
		{
			BulletAnimationRender_->ChangeAnimation("SnowBullet_" + ChangeBDirText_);
			BCurrentDir_ = BCheckDir_;
		}
		else if (true == BluePotion::BPCheck_)
		{
			BulletAnimationRender_->ChangeAnimation("BP_SnowBullet_" + ChangeBDirText_);
			BCurrentDir_ = BCheckDir_;
		}
	}
}

void SnowBullet::Start()
{
	BulletCollision_ = CreateCollision("BulletHitBox", { 24, 44 });
	
	//CreateRenderer("Snow_Bullet.bmp");
	BulletAnimationRender_ = CreateRenderer();
	BulletAnimationRender_->CreateAnimation("SnowBullet_Left.bmp", "SnowBullet_Left", 0, 1, 0.12f, true);
	BulletAnimationRender_->CreateAnimation("SnowBullet_Right.bmp", "SnowBullet_Right", 0, 1, 0.12f, true);
	BulletAnimationRender_->CreateAnimation("BP_SnowBullet_Left.bmp", "BP_SnowBullet_Left", 0, 1, 0.12f, true);
	BulletAnimationRender_->CreateAnimation("BP_SnowBullet_Right.bmp", "BP_SnowBullet_Right", 0, 1, 0.12f, true);
	BulletAnimationRender_->ChangeAnimation("SnowBullet_Left");
	//Time = 2.0f;
	Death(0.8f);

	XSpeed_ = 500.0f;
	YSpeed_ = 500.0f;
}

void SnowBullet::Update()
{
	DirBulletCheck();
	CollisionFloorCheck();
	float4 ResultDir = float4::ZERO;
	// 모든 힘은 뭘해도 float4
	ResultDir = SnowBulletDir_ * GameEngineTime::GetDeltaTime() * XSpeed_;
	Time -= GameEngineTime::GetDeltaTime();
	
	if (true == BulletCollision_->CollisionCheck("EnemyHitBox", CollisionType::RECT, CollisionType::RECT)
		|| true == BulletCollision_->CollisionCheck("SnowBox", CollisionType::RECT, CollisionType::RECT)
		|| true == BulletCollision_->CollisionCheck("BossHitBox", CollisionType::RECT, CollisionType::RECT)
		|| true == BulletCollision_->CollisionCheck("BossHeadHitBox", CollisionType::RECT, CollisionType::RECT)
		|| true == BulletCollision_->CollisionCheck("BossDeathBox", CollisionType::RECT, CollisionType::RECT))
	{
		Death();
		return;
	}
	
	int Color = FloorColImage_->GetImagePixel(GetPosition());
	if (RGB(0, 0, 0) == Color)
	{
		Death();
		return;
	}
	
	if (Time <= 0.3f)
	{
		ResultDir = YDir_ * GameEngineTime::GetDeltaTime();
	}
	else if (0.42f >= Time)
	{
		ResultDir += YDir_ * GameEngineTime::GetDeltaTime();
	}
	
	SetMove(ResultDir);
}

void SnowBullet::CollisionFloorCheck()
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
