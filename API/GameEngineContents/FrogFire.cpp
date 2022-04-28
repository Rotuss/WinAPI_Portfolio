#include "FrogFire.h"
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

	Death(DeathTime_);

	XSpeed_ = 500.0f;
}

void FrogFire::Update()
{
	DeathTime_ -= GameEngineTime::GetDeltaTime();
	DirFireCheck();
	float4 ResultDir = float4::ZERO;
	// 모든 힘은 뭘해도 float4
	ResultDir += FireDir_ * GameEngineTime::GetDeltaTime() * XSpeed_;

	if (true == FireCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		//FireAnimationRender_->ChangeAnimation("FrogFire_Boom");
		Death();
		return;
	}
	// 수정할 것
	/*
	if (DeathTime_ <= 0)
	{
		ResultDir = float4::ZERO;
		FireAnimationRender_->ChangeAnimation("FrogFire_Boom");
	}
	*/
	SetMove(ResultDir);
}
