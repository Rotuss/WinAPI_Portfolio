#include "SnowBullet.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineCollision.h>

SnowBullet::SnowBullet()
	: Time(0.42f)
	, YDir_(float4::DOWN * 200.0f)
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
		BCheckDir_ = BulletDir::RIGHT;
	}
	if (ChangeBDirText_ == "Left")
	{
		BCheckDir_ = BulletDir::LEFT;
	}

	if (BCheckDir_ != BCurrentDir_)
	{
		BulletAnimationRender_->ChangeAnimation("SnowBullet_" + ChangeBDirText_);
		BCurrentDir_ = BCheckDir_;
	}
}

void SnowBullet::Start()
{
	BulletCollision_ = CreateCollision("BulletHitBox", { 24, 44 });
	
	//CreateRenderer("Snow_Bullet.bmp");
	BulletAnimationRender_ = CreateRenderer();
	BulletAnimationRender_->CreateAnimation("SnowBullet_Left.bmp", "SnowBullet_Left", 0, 1, 0.12f, true);
	BulletAnimationRender_->CreateAnimation("SnowBullet_Right.bmp", "SnowBullet_Right", 0, 1, 0.12f, true);
	BulletAnimationRender_->ChangeAnimation("SnowBullet_Left");
	//Time = 2.0f;
	Death(0.5f);

	XSpeed_ = 500.0f;
	YSpeed_ = 500.0f;
}

void SnowBullet::Update()
{
	DirBulletCheck();
	float4 ResultDir = float4::ZERO;
	// ¸ðµç ÈûÀº ¹»ÇØµµ float4
	ResultDir += SnowBulletDir_ * GameEngineTime::GetDeltaTime() * XSpeed_;
	Time -= GameEngineTime::GetDeltaTime();
	
	if (true == BulletCollision_->CollisionCheck("RedDemonHitBox", CollisionType::RECT, CollisionType::RECT)
		|| true == BulletCollision_->CollisionCheck("FrogHitBox", CollisionType::RECT, CollisionType::RECT)
		|| true == BulletCollision_->CollisionCheck("SnowBox", CollisionType::RECT, CollisionType::RECT)
		|| true == BulletCollision_->CollisionCheck("BossHitBox", CollisionType::RECT, CollisionType::RECT)
		|| true == BulletCollision_->CollisionCheck("BossHeadHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Death();
		return;
	}
	
	if (0.0f >= Time)
	{
		ResultDir += YDir_ * GameEngineTime::GetDeltaTime();
	}
	
	SetMove(ResultDir);
}
