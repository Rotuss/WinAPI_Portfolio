#include "Frog.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void Frog::IdleUpdate()
{
	MoveTime_ -= GameEngineTime::GetDeltaTime();
	if (MoveTime_ <= 0)
	{
		if (StartMoveCount_ <= 0)
		{
			ChangeState(FrogState::MOVE);
			MoveTime_ = 0.3f;
			return;
		}
		else
		{
			ChangeState(FrogState::STARTMOVE);
			MoveTime_ = 0.3f;
			return;
		}
	}
	if (true == FrogCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		DamageCount_ -= 1;
		if (DamageCount_ <= 0)
		{
			ChangeState(FrogState::SNOW1);
			return;
		}
	}

	float4 CheckPos = GetPosition() + float4(0.0f, 44.0f);

	int DColor = FloorColImage_->GetImagePixel(CheckPos + float4(0.0f, 1.0f));
	if (RGB(0, 0, 0) != DColor && RGB(0, 255, 0) != DColor && CurrentState_ != FrogState::JUMP)
	{
		ChangeState(FrogState::DOWN);
		return;
	}
}

void Frog::StartMoveUpdate()
{
	if (true == FrogCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		DamageCount_ -= 1;
		if (DamageCount_ <= 0)
		{
			ChangeState(FrogState::SNOW1);
			return;
		}
	}

	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);

	float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	float4 CheckBotPos = NextPos + float4(0.0f, 45.0f);
	float4 CheckRightPos = NextPos + float4(15.0f, 0.0f);
	float4 CheckLeftPos = NextPos + float4(-15.0f, 0.0f);

	int BotColor = FloorColImage_->GetImagePixel(CheckBotPos);
	int RightColor = FloorColImage_->GetImagePixel(CheckRightPos);
	int LeftColor = FloorColImage_->GetImagePixel(CheckLeftPos);
	int DColor = FloorColImage_->GetImagePixel(CheckBotPos + float4(0.0f, 1.0f));

	if (RGB(0, 0, 0) != BotColor && RGB(0, 255, 0) != BotColor && CurrentState_ != FrogState::JUMP)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (RGB(0, 0, 0) == RightColor)
	{
		CurrentDir_ = FrogDir::LEFT;
		ChangeDirText_ = "Left";
		FrogAnimationRender_->ChangeAnimation("Move_" + ChangeDirText_);
		MoveDir_.x = -1.f;

		Range_ = 30.0f;
	}
	if (RGB(0, 0, 0) == LeftColor)
	{
		CurrentDir_ = FrogDir::RIGHT;
		ChangeDirText_ = "Right";
		FrogAnimationRender_->ChangeAnimation("Move_" + ChangeDirText_);
		MoveDir_.x = 1.f;

		Range_ = 30.0f;
	}
	if (RGB(255, 255, 255) == DColor)
	{
		ChangeState(FrogState::DOWN);
		return;
	}

	Range_ -= GameEngineTime::GetDeltaTime() * Speed_;

	FrogDir CheckDir_ = CurrentDir_;

	if (CurrentDir_ == FrogDir::LEFT)
	{
		if (Range_ <= 0)
		{
			CurrentDir_ = FrogDir::RIGHT;
			ChangeDirText_ = "Right";
			ChangeState(FrogState::IDLE);

			Range_ = 30.0f;
			return;
		}
		else
		{
			MoveDir_.x = -1.f;
		}
	}

	if (CurrentDir_ == FrogDir::RIGHT)
	{
		if (Range_ <= 0)
		{
			CurrentDir_ = FrogDir::LEFT;
			ChangeDirText_ = "Left";
			ChangeState(FrogState::IDLE);

			Range_ = 30.0f;
			return;
		}
		else
		{
			MoveDir_.x = 1.f;
		}
	}
}

void Frog::MoveUpdate()
{
	if (true == FrogCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		DamageCount_ -= 1;
		if (DamageCount_ <= 0)
		{
			ChangeState(FrogState::SNOW1);
			return;
		}
	}

	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);

	float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	float4 CheckBotPos = NextPos + float4(0.0f, 45.0f);
	float4 CheckRTopPos = NextPos + float4(15.0f, -45.0f);
	float4 CheckLTopPos = NextPos + float4(-15.0f, -45.0f);
	float4 CheckRightPos = NextPos + float4(15.0f, 0.0f);
	float4 CheckLeftPos = NextPos + float4(-15.0f, 0.0f);

	int BotColor = FloorColImage_->GetImagePixel(CheckBotPos);
	int RTopColor = FloorColImage_->GetImagePixel(CheckRTopPos);
	int LTopColor = FloorColImage_->GetImagePixel(CheckLTopPos);
	int RightColor = FloorColImage_->GetImagePixel(CheckRightPos);
	int LeftColor = FloorColImage_->GetImagePixel(CheckLeftPos);
	int DColor = FloorColImage_->GetImagePixel(CheckBotPos + float4(0.0f, 1.0f));

	if (RGB(0, 0, 0) != BotColor && RGB(0, 255, 0) != BotColor && CurrentState_ != FrogState::JUMP)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (RGB(0, 0, 0) == RightColor)
	{
		CurrentDir_ = FrogDir::LEFT;
		ChangeDirText_ = "Left";
		FrogAnimationRender_->ChangeAnimation("Move_" + ChangeDirText_);
		MoveDir_.x = -1.f;

		Range_ = 300.0f;
	}
	if (RGB(0, 0, 0) == LeftColor)
	{
		CurrentDir_ = FrogDir::RIGHT;
		ChangeDirText_ = "Right";
		FrogAnimationRender_->ChangeAnimation("Move_" + ChangeDirText_);
		MoveDir_.x = 1.f;

		Range_ = 300.0f;
	}
	if (RGB(255, 255, 255) == DColor)
	{
		if (CurrentDir_ == FrogDir::LEFT)
		{
			ChangeDirText_ = "Left";
			ChangeState(FrogState::DOWN);
			JumpTime_ = 10.0f;
			return;
		}

		if (CurrentDir_ == FrogDir::RIGHT)
		{
			ChangeDirText_ = "Right";
			ChangeState(FrogState::DOWN);
			JumpTime_ = 10.0f;
			return;
		}
	}

	Range_ -= GameEngineTime::GetDeltaTime() * Speed_;

	FrogDir CheckDir_ = CurrentDir_;

	if (CurrentDir_ == FrogDir::LEFT)
	{
		if (Range_ <= 0)
		{
			CurrentDir_ = FrogDir::RIGHT;
			ChangeDirText_ = "Right";
			ChangeState(FrogState::IDLE);

			Range_ = 300.0f;
			return;
		}
		else
		{
			MoveDir_.x = -1.f;
		}
	}

	if (CurrentDir_ == FrogDir::RIGHT)
	{
		if (Range_ <= 0)
		{
			CurrentDir_ = FrogDir::LEFT;
			ChangeDirText_ = "Left";
			ChangeState(FrogState::IDLE);

			Range_ = 300.0f;
			return;
		}
		else
		{
			MoveDir_.x = 1.f;
		}
	}

	JumpTime_ -= GameEngineTime::GetDeltaTime();
	if (JumpTime_ <= 0)
	{
		if (RGB(0, 0, 0) == RTopColor && RGB(0, 0, 0) == LTopColor)
		{
			if (CurrentDir_ == FrogDir::LEFT)
			{
				ChangeDirText_ = "Left";
				ChangeState(FrogState::JUMP);
				JumpTime_ = 10.0f;
				return;
			}

			if (CurrentDir_ == FrogDir::RIGHT)
			{
				ChangeDirText_ = "Right";
				ChangeState(FrogState::JUMP);
				JumpTime_ = 10.0f;
				return;
			}
		}
		ChangeState(FrogState::MOVE);
		return;
	}
}

void Frog::JumpUpdate()
{
	if (true == FrogCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		DamageCount_ -= 1;
		if (DamageCount_ <= 0)
		{
			ChangeState(FrogState::SNOW1);
			return;
		}
	}

	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());

	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;

	if (MoveDir_.y < 0)
	{
		return;
	}

	int Color = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 45.0f });
	int RColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ 15.0f, 0.0f });
	int LColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ -15.0f, 0.0f });
	if (RGB(0, 0, 0) == Color || RGB(0, 255, 0) == Color)
	{
		MoveDir_.y = 0.0f;
		ChangeState(FrogState::MOVE);
		return;
	}
	if (RGB(0, 0, 0) == RColor || RGB(0, 255, 0) == RColor || RGB(0, 0, 0) == LColor || RGB(0, 255, 0) == LColor)
	{
		MoveDir_.x = 0.0f;
		ChangeState(FrogState::MOVE);
		return;
	}
}

void Frog::DownUpdate()
{
	if (true == FrogCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		DamageCount_ -= 1;
		if (DamageCount_ <= 0)
		{
			ChangeState(FrogState::SNOW1);
			return;
		}
	}

	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;

	if (MoveDir_.y < 0)
	{
		return;
	}

	int Color = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 45.0f });
	if (RGB(0, 0, 0) == Color || RGB(0, 255, 0) == Color)
	{
		MoveDir_ = float4::ZERO;
		ChangeState(FrogState::MOVE);
		return;
	}
}

void Frog::AttackUpdate()
{}

void Frog::Snow1Update()
{
	if (true == FrogCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		DamageCount_ -= 1;
		if (DamageCount_ <= 0)
		{
			ChangeState(FrogState::SNOW2);
			return;
		}
	}
	if (false == FrogCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		MeltingTime_ -= GameEngineTime::GetDeltaTime();
		if (MeltingTime_ < 0)
		{
			ChangeState(FrogState::SHAKINGSNOW);
			return;
		}
	}
}

void Frog::Snow2Update()
{
	if (true == FrogCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		DamageCount_ -= 1;
		if (DamageCount_ <= 0)
		{
			ChangeState(FrogState::SNOW3);
			return;
		}
	}
	if (false == FrogCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		MeltingTime_ -= GameEngineTime::GetDeltaTime();
		if (MeltingTime_ < 0)
		{
			ChangeState(FrogState::SNOW1);
			return;
		}
	}
}

void Frog::Snow3Update()
{
	// MeltingTime_ 시간 동안 한 번이라도 부딪히면 Snow3, 한 번도 안 부딪히면 Snow2
	MeltingTime_ -= GameEngineTime::GetDeltaTime();
	if (MeltingTime_ > 0.0f)
	{
		if (true == FrogCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
		{
			MeltingTime_ = 5.0f;
			return;
		}
	}
	else if (MeltingTime_ <= 0.0f)
	{
		if (false == FrogCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
		{
			ChangeState(FrogState::SNOW2);
			FrogSnowRCollision_->Death();
			FrogSnowLCollision_->Death();
			return;
		}
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

void Frog::ShakingSnowUpdate()
{
	ShakingTime_ -= GameEngineTime::GetDeltaTime();
	if (ShakingTime_ <= 0)
	{
		ChangeState(FrogState::IDLE);
		return;
	}

	if (true == FrogCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		DamageCount_ -= 1;
		if (DamageCount_ <= 0)
		{
			ChangeState(FrogState::SNOW1);
			return;
		}
	}
}

void Frog::DefeatedUpdate()
{}

void Frog::DeathUpdate()
{}

//===========================Start==========================
void Frog::IdleStart()
{
	StartMoveCount_ -= 1;
	AnimationName_ = "Idle_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Right";
	}
	FrogAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Frog::StartMoveStart()
{
	AnimationName_ = "Move_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Right";
	}
	FrogAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Frog::MoveStart()
{
	AnimationName_ = "Move_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Right";
	}
	FrogAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Frog::JumpStart()
{
	AnimationName_ = "Jump_";
	FrogAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);

	MoveDir_ = float4::UP * 520.0f;
}

void Frog::DownStart()
{
	//AnimationName_ = "Down_";
	//FrogAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Frog::AttackStart()
{}

void Frog::Snow1Start()
{
	AnimationName_ = "Snow1";
	FrogAnimationRender_->ChangeAnimation(AnimationName_);
	FrogAnimationRender_->SetPivot({ 0,20.0f });

	DamageCount_ = 2;
	MeltingTime_ = 3.0f;
}

void Frog::Snow2Start()
{
	AnimationName_ = "Snow2";
	FrogAnimationRender_->ChangeAnimation(AnimationName_);
	FrogAnimationRender_->SetPivot({ 0,20.0f });

	DamageCount_ = 2;
	MeltingTime_ = 3.0f;
}

void Frog::Snow3Start()
{
	AnimationName_ = "Snow3";
	FrogAnimationRender_->ChangeAnimation(AnimationName_);
	FrogAnimationRender_->SetPivot({ 0,5 });

	FrogSnowRCollision_ = CreateCollision("SnowRColBox", { 5, 10 }, { -15, 0 });
	FrogSnowLCollision_ = CreateCollision("SnowLColBox", { 5, 10 }, { 15, 0 });

	MeltingTime_ = 5.0f;
}

void Frog::ShakingSnowStart()
{
	AnimationName_ = "ShakingSnow";
	FrogAnimationRender_->ChangeAnimation(AnimationName_);
	FrogAnimationRender_->SetPivot({ 0,0 });

	ShakingTime_ = 1.0f;
}

void Frog::DefeatedStart()
{
	AnimationName_ = "Frog_Defeated";
	FrogAnimationRender_->ChangeAnimation(AnimationName_);
}

void Frog::DeathStart()
{
	AnimationName_ = "Frog_Death";
	FrogAnimationRender_->ChangeAnimation(AnimationName_);
}