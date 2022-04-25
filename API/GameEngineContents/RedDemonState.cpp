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
		DamageCount_ -= 1;
		if (DamageCount_ < 0)
		{
			ChangeState(RedDemonState::SNOW1);
			return;
		}
	}
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
		DamageCount_ -= 1;
		if (DamageCount_ < 0)
		{
			ChangeState(RedDemonState::SNOW2);
			return;
		}
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
		DamageCount_ -= 1;
		if (DamageCount_ < 0)
		{
			ChangeState(RedDemonState::SNOW3);
			return;
		}
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
	if (2.5f < MeltingTime_ && MeltingTime_ > 0.0f)
	{
		if (true == RedDemonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
		{
			ChangeState(RedDemonState::SNOW3);
			return;
		}
	}
	if(MeltingTime_ <= 0.0f)
	{
		if (false == RedDemonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
		{
			ChangeState(RedDemonState::SNOW2);
			return;
		}
	}

	/*
	MeltingTime_ -= GameEngineTime::GetDeltaTime();
	if(MeltingTime_ <= 0.0f)
	{
		if (true == RedDemonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
		{
			ChangeState(RedDemonState::SNOW3);
			return;
		}
		if (false == RedDemonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
		{
			ChangeState(RedDemonState::SNOW2);
			return;
		}
	}
	*/

}

void RedDemon::ShakingSnowUpdate()
{
	ShakingTime_ -= GameEngineTime::GetDeltaTime();
	if (ShakingTime_ <= 0)
	{
		ChangeState(RedDemonState::IDLE);
		return;
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

	DamageCount_ = 3;
	MeltingTime_ = 1.5f;
}

void RedDemon::Snow2Start()
{
	AnimationName_ = "Snow2";
	RedDemonAnimationRender_->ChangeAnimation(AnimationName_);
	RedDemonAnimationRender_->SetPivot({ 0,20.0f });

	DamageCount_ = 3;
	MeltingTime_ = 1.5f;
}

void RedDemon::Snow3Start()
{
	AnimationName_ = "Snow3";
	RedDemonAnimationRender_->ChangeAnimation(AnimationName_);
	RedDemonAnimationRender_->SetPivot({ 0,5 });

	MeltingTime_ = 2.5f;
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