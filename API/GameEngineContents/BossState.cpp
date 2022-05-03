#include "Boss.h"
// son.h
#include "Score.h"
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

void Boss::StartDownUpdate()
{
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;
	float4 CheckPos = GetPosition() + float4(0.0f, 130.0f);

	int DColor = FloorColImage_->GetImagePixel(CheckPos + float4(0.0f, 1.0f));
	if (RGB(0, 255, 0) != DColor)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	}
	if (RGB(0, 255, 0) == DColor)
	{
		MoveDir_ = float4::ZERO;
		ChangeState(BossState::IDLE);
		return;
	}
}

void Boss::IdleUpdate()
{
	GameEngineRandom RandomValue_;
	AttackTime_ -= GameEngineTime::GetDeltaTime();
	if (AttackTime_ <= 0)
	{
		//ChangeState(BossState::ATTACK);
		AttackTime_ = static_cast<float>(RandomValue_.RandomInt(1, 3));
		return;
	}
	if (true == BossCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		DamageCount_ -= 1;
		if (DamageCount_ <= 0)
		{
			Score::ScoreUI_ += 50000;
			//ChangeState(BossState::DEFEATED);
			return;
		}
	}
	if (true == BossHeadCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		DamageCount_ -= 1;
		if (DamageCount_ <= 0)
		{
			Score::ScoreUI_ += 50000;
			//ChangeState(BossState::DEFEATED);
			return;
		}
	}
	if (true == BossCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		DamageCount_ -= 1;
		if (DamageCount_ <= 0)
		{
			Score::ScoreUI_ += 50000;
			//ChangeState(BossState::DEFEATED);
			return;
		}
	}

	float4 CheckPos = GetPosition() + float4(0.0f, 130.0f);

	int DColor = FloorColImage_->GetImagePixel(CheckPos + float4(0.0f, 5.0f));
	if (RGB(0, 0, 0) != DColor && CurrentState_ != BossState::JUMP)
	{
		//ChangeState(FrogState::DOWN);
		return;
	}
}

void Boss::JumpUpdate()
{
	// 점프가 낮음
}

void Boss::AttackUpdate()
{
	// 점프가 높음
}

void Boss::DefeatedUpdate()
{

}

void Boss::DeathUpdate()
{}

//===========================Start==========================
void Boss::StartDownStart()
{}

void Boss::IdleStart()
{
	AnimationName_ = "Idle";
	BossAnimationRender_->ChangeAnimation(AnimationName_);
}

void Boss::JumpStart()
{
	AnimationName_ = "Jump";
	BossAnimationRender_->ChangeAnimation(AnimationName_);
}

void Boss::AttackStart()
{}

void Boss::DefeatedStart()
{
	AnimationName_ = "Defeated";
	BossAnimationRender_->ChangeAnimation(AnimationName_);
}

void Boss::DeathStart()
{
	AnimationName_ = "Death";
	BossAnimationRender_->ChangeAnimation(AnimationName_);
}