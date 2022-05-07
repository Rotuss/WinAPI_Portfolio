#include "Boss.h"
#include "Son.h"
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
	JumpTime_ -= GameEngineTime::GetDeltaTime();
	if (JumpTime_ <= 0)
	{
		ChangeState(BossState::JUMP);
		JumpTime_ = static_cast<float>(RandomValue_.RandomInt(3, 5));
		return;
	}
	AttackTime_ -= GameEngineTime::GetDeltaTime();
	if (AttackTime_ <= 0)
	{
		ChangeState(BossState::ATTACK);
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
			ChangeState(BossState::DEFEATED);
			return;
		}
	}
	if (true == BossHeadCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		DamageCount_ -= 1;
		if (DamageCount_ <= 0)
		{
			Score::ScoreUI_ += 50000;
			ChangeState(BossState::DEFEATED);
			return;
		}
	}
	if (true == BossCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		DamageCount_ -= 1;
		if (DamageCount_ <= 0)
		{
			Score::ScoreUI_ += 50000;
			ChangeState(BossState::DEFEATED);
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
	// Á¡ÇÁ°¡ ³·À½(5¹ø ±øÃÑ)
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;

	if (true == BossCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		DamageCount_ -= 1;
		if (DamageCount_ <= 0)
		{
			Score::ScoreUI_ += 50000;
			ChangeState(BossState::DEFEATED);
			return;
		}
	}
	if (true == BossHeadCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		DamageCount_ -= 1;
		if (DamageCount_ <= 0)
		{
			Score::ScoreUI_ += 50000;
			ChangeState(BossState::DEFEATED);
			return;
		}
	}
	if (true == BossCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		DamageCount_ -= 1;
		if (DamageCount_ <= 0)
		{
			Score::ScoreUI_ += 50000;
			ChangeState(BossState::DEFEATED);
			return;
		}
	}
	
	float4 CheckPos = GetPosition() + float4(0.0f, 130.0f);

	int Color = FloorColImage_->GetImagePixel(CheckPos);
	if (RGB(0, 0, 0) == Color)
	{
		StandbyTIme_ -= GameEngineTime::GetDeltaTime();
		if (0 == JumpCount_)
		{
			JumpCount_ = 5;
			ChangeState(BossState::IDLE);
			return;
		}
		MoveDir_.y = 0.0f;
		BossAnimationRender_->ChangeAnimation("Idle");
		if (0 < JumpCount_ && StandbyTIme_ <= 0)
		{
			JumpCount_ -= 1;
			StandbyTIme_ = 0.12f;
			MoveDir_ = float4::UP * 520.0f;
			BossAnimationRender_->ChangeAnimation("Jump");
		}
	}
}

void Boss::AttackUpdate()
{
	// Á¡ÇÁ°¡ ³ôÀ½
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;

	if (true == BossCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		DamageCount_ -= 1;
		if (DamageCount_ <= 0)
		{
			Score::ScoreUI_ += 50000;
			ChangeState(BossState::DEFEATED);
			return;
		}
	}
	if (true == BossHeadCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		DamageCount_ -= 1;
		if (DamageCount_ <= 0)
		{
			Score::ScoreUI_ += 50000;
			ChangeState(BossState::DEFEATED);
			return;
		}
	}
	if (true == BossCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		DamageCount_ -= 1;
		if (DamageCount_ <= 0)
		{
			Score::ScoreUI_ += 50000;
			ChangeState(BossState::DEFEATED);
			return;
		}
	}
	
	float4 CheckPos = GetPosition() + float4(0.0f, 130.0f);
	
	int Color = FloorColImage_->GetImagePixel(CheckPos + float4(100.0f, 0.0f));
	int CColor = FloorColImage_->GetImagePixel(CheckPos + float4(100.0f,-3.0f));
	int BColor = FloorColImage_->GetImagePixel(CheckPos + float4(100.0f, 130.0f));
	int RColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ 115.0f, 0.0f });
	int LColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ -115.0f, 0.0f });
	if (RGB(0, 0, 0) == Color && RGB(255,255,255) == BColor)
	{
		if (false == AttackMoveCheck_ && RGB(255, 255, 255) == CColor)
		{
			MoveDir_.y = 0.0f;
			ChangeState(BossState::IDLE);
			AttackMoveCheck_ = true;
			return;
		}
		else if (true == AttackMoveCheck_)
		{
			return;
		}
	}
	else if (RGB(0, 0, 0) == Color && RGB(0, 0, 0) == BColor)
	{
		MoveDir_.y = 0.0f;
		AttackMoveCheck_ = false;
		ChangeState(BossState::IDLE);

		return;
	}

	if (RGB(0, 0, 255) == RColor)
	{
		CurrentDir_ = BossDir::LEFT;
		MoveDir_.x = -1.f * 10.0f;
	}
	if (RGB(0, 0, 255) == LColor)
	{
		CurrentDir_ = BossDir::RIGHT;
		MoveDir_.x = 1.f * 10.0f;
	}

	if (CurrentDir_ == BossDir::LEFT)
	{
		MoveDir_.x = -1.f * 10.0f;
	}
	if (CurrentDir_ == BossDir::RIGHT)
	{
		MoveDir_.x = 1.f * 10.0f;
	}
}

void Boss::DefeatedUpdate()
{
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;


	if (true == BossDeathCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
	}
	
	float4 CheckPos = GetPosition() + float4(0.0f, 130.0f);

	int Color = FloorColImage_->GetImagePixel(CheckPos);
	if (RGB(0, 0, 0) == Color)
	{
		MoveDir_.y = 0.0f;
	}
	
	DefeatedTime1_ -= GameEngineTime::GetDeltaTime();
	if (DefeatedTime1_ <= 0)
	{
		BossAnimationRender_->ChangeAnimation("Defeated");
		BossAnimationRender_->SetPivot({ 0, 50 });
		DefeatedTime2_ -= GameEngineTime::GetDeltaTime();
	}
	if (DefeatedTime2_ <= 0)
	{
		ChangeState(BossState::DEATH);
	}
}

void Boss::DeathUpdate()
{
	DeathTime_ -= GameEngineTime::GetDeltaTime();
	if (true == BossDeathCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
	}

	if (DeathTime_ <= 0)
	{
		Death();
	}
}

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

	MoveDir_ = float4::UP * 520.0f;
}

void Boss::AttackStart()
{
	AnimationName_ = "Jump";
	BossAnimationRender_->ChangeAnimation(AnimationName_);

	MoveDir_ = float4::UP * 800.0f;

	Son* Ptr = GetLevel()->CreateActor<Son>();
	Ptr->SetPosition(GetPosition());
}

void Boss::DefeatedStart()
{
	BossCollision_->Off();
	BossHeadCollision_->Off();
	AnimationName_ = "Jump";
	BossAnimationRender_->ChangeAnimation(AnimationName_);
	BossAnimationRender_->SetPivot({ 0, -50 });

	BossDeathCollision_ = CreateCollision("BossDeathBox", { 250,190 });
}

void Boss::DeathStart()
{
	AnimationName_ = "Death";
	BossAnimationRender_->ChangeAnimation(AnimationName_);
}