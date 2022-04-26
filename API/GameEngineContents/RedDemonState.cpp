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

void RedDemon::IdleUpdate()
{
	if (true == RedDemonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		if (DamageCount_ < 0)
		{
			ChangeState(RedDemonState::SNOW1);
			return;
		}
		DamageCount_ -= 1;
	}

	/*
	float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	float4 CheckPos = NextPos + float4(0.0f, 44.0f);

	int Color = FloorColImage_->GetImagePixel(CheckPos);
	int DColor = FloorColImage_->GetImagePixel(CheckPos + float4(0.0f, 0.0f));
	if (RGB(0, 0, 0) != Color && RGB(0, 255, 0) != Color)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (RGB(255, 255, 255) == DColor)
	{
		MoveDir_ = float4::DOWN * 2.0f;
		return;
	}
	*/
}

void RedDemon::MoveUpdate()
{}

void RedDemon::JumpUpdate()
{}

void RedDemon::DownUpdate()
{}

void RedDemon::AttackUpdate()
{}

void RedDemon::Snow1Update()
{
	if (true == RedDemonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		if (DamageCount_ < 0)
		{
			ChangeState(RedDemonState::SNOW2);
			return;
		}
		DamageCount_ -= 1;
	}
	if (false == RedDemonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		MeltingTime_ -= GameEngineTime::GetDeltaTime();
		if (MeltingTime_ < 0)
		{
			ChangeState(RedDemonState::SHAKINGSNOW);
			return;
		}
	}
}

void RedDemon::Snow2Update()
{
	if (true == RedDemonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		if (DamageCount_ < 0)
		{
			ChangeState(RedDemonState::SNOW3);
			return;
		}
		DamageCount_ -= 1;
	}
	if (false == RedDemonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		MeltingTime_ -= GameEngineTime::GetDeltaTime();
		if (MeltingTime_ < 0)
		{
			ChangeState(RedDemonState::SNOW1);
			return;
		}
	}
}

void RedDemon::Snow3Update()
{
	// MeltingTime_ 시간 동안 한 번이라도 부딪히면 Snow3, 한 번도 안 부딪히면 Snow2
	MeltingTime_ -= GameEngineTime::GetDeltaTime();
	if (MeltingTime_ > 0.0f)
	{
		if (true == RedDemonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
		{
			MeltingTime_ = 5.0f;
			return;
		}
	}
	else if(MeltingTime_ <= 0.0f)
	{
		if (false == RedDemonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
		{
			ChangeState(RedDemonState::SNOW2);
			RedDemonSnowRCollision_->Death();
			RedDemonSnowLCollision_->Death();
			return;
		}
	}

	if (true == RedDemonSnowRCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		MoveDir_ = float4::RIGHT;
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * SnowSpeed_);
	}
	if (true == RedDemonSnowLCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		MoveDir_ = float4::LEFT;
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * SnowSpeed_);
	}

	float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	float4 CheckPos = NextPos + float4(0.0f, 44.0f);

	int Color = FloorColImage_->GetImagePixel(CheckPos);
	int DColor = FloorColImage_->GetImagePixel(CheckPos + float4(0.0f, 0.0f));
	if (RGB(0, 0, 0) != Color && RGB(0, 255, 0) != Color)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (RGB(255, 255, 255) == DColor)
	{
		MoveDir_ = float4::DOWN * 2.0f;
		return;
	}
}

void RedDemon::ShakingSnowUpdate()
{
	ShakingTime_ -= GameEngineTime::GetDeltaTime();
	if (ShakingTime_ <= 0)
	{
		ChangeState(RedDemonState::IDLE);
		return;
	}

	if (true == RedDemonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		if (DamageCount_ < 0)
		{
			ChangeState(RedDemonState::SNOW1);
			return;
		}
		DamageCount_ -= 1;
	}
}

void RedDemon::DefeatedUpdate()
{}

void RedDemon::DeathUpdate()
{}

//===========================Start==========================
void RedDemon::IdleStart()
{
	AnimationName_ = "Idle_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Right";
	}
	RedDemonAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
	RedDemonAnimationRender_->SetPivot({ 0,0 });
}

void RedDemon::MoveStart()
{}

void RedDemon::JumpStart()
{}

void RedDemon::DownStart()
{}

void RedDemon::AttackStart()
{}

void RedDemon::Snow1Start()
{
	AnimationName_ = "Snow1";
	RedDemonAnimationRender_->ChangeAnimation(AnimationName_);
	RedDemonAnimationRender_->SetPivot({ 0,20.0f });

	DamageCount_ = 2;
	MeltingTime_ = 3.0f;
}

void RedDemon::Snow2Start()
{
	AnimationName_ = "Snow2";
	RedDemonAnimationRender_->ChangeAnimation(AnimationName_);
	RedDemonAnimationRender_->SetPivot({ 0,20.0f });

	DamageCount_ = 2;
	MeltingTime_ = 3.0f;
}

void RedDemon::Snow3Start()
{
	AnimationName_ = "Snow3";
	RedDemonAnimationRender_->ChangeAnimation(AnimationName_);
	RedDemonAnimationRender_->SetPivot({ 0,5 });

	RedDemonSnowRCollision_ = CreateCollision("SnowRColBox", { 5, 10 }, { -15, 0 });
	RedDemonSnowLCollision_ = CreateCollision("SnowLColBox", { 5, 10 }, { 15, 0 });

	MeltingTime_ = 5.0f;
}

void RedDemon::ShakingSnowStart()
{
	AnimationName_ = "ShakingSnow";
	RedDemonAnimationRender_->ChangeAnimation(AnimationName_);
	RedDemonAnimationRender_->SetPivot({ 0,0 });

	ShakingTime_ = 1.0f;
}

void RedDemon::DefeatedStart()
{}

void RedDemon::DeathStart()
{}