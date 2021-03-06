#include "Frog.h"
#include "FrogFire.h"
#include "Score.h"
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

void Frog::StartDownUpdate()
{
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;
	float4 CheckPos = GetPosition() + float4(0.0f, 44.0f);

	int DColor = FloorColImage_->GetImagePixel(CheckPos + float4(0.0f, 1.0f));
	if (RGB(0, 255, 0) != DColor)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	}
	if (RGB(0, 255, 0) == DColor)
	{
		MoveDir_ = float4::ZERO;
		ChangeState(FrogState::IDLE);
		return;
	}
}

void Frog::IdleUpdate()
{
	GameEngineRandom RandomValue_;
	MoveTime_ -= GameEngineTime::GetDeltaTime();
	AttackTime_ -= GameEngineTime::GetDeltaTime();
	MoveDir_ = float4::ZERO;
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
	if (AttackTime_ <= 0)
	{
		ChangeState(FrogState::ATTACK);
		AttackTime_ = static_cast<float>(RandomValue_.RandomInt(1, 3));
		return;
	}
	if (true == FrogCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(FrogState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(FrogState::SNOW1);
				return;
			}
		}
	}
	if (true == FrogRCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = FrogDir::RIGHT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	else if (true == FrogLCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = FrogDir::LEFT;
		ChangeState(FrogState::DEFEATED);
		return;
	}

	if (true == FrogRCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		CurrentDir_ = FrogDir::RIGHT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	else if (true == FrogLCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		CurrentDir_ = FrogDir::LEFT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	
	float4 CheckPos = GetPosition() + float4(0.0f, 44.0f);

	int DColor = FloorColImage_->GetImagePixel(CheckPos + float4(0.0f, 5.0f));
	if (RGB(0, 0, 0) != DColor && CurrentState_ != FrogState::JUMP)
	{
		ChangeState(FrogState::DOWN);
		return;
	}
}

void Frog::StartMoveUpdate()
{
	if (true == FrogCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(FrogState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(FrogState::SNOW1);
				return;
			}
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
	int DColor = FloorColImage_->GetImagePixel(CheckBotPos + float4(0.0f, 5.0f));

	if (RGB(0, 0, 0) != BotColor && CurrentState_ != FrogState::JUMP)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
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
	GameEngineRandom RandomValue_;
	if (true == FrogCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(FrogState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(FrogState::SNOW1);
				return;
			}
		}
	}
	if (true == FrogRCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = FrogDir::RIGHT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	else if (true == FrogLCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = FrogDir::LEFT;
		ChangeState(FrogState::DEFEATED);
		return;
	}

	if (true == FrogRCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		CurrentDir_ = FrogDir::RIGHT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	else if (true == FrogLCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		CurrentDir_ = FrogDir::LEFT;
		ChangeState(FrogState::DEFEATED);
		return;
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

	if (RGB(0, 0, 0) != BotColor && CurrentState_ != FrogState::JUMP)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (RGB(0, 0, 0) == RightColor)
	{
		CurrentDir_ = FrogDir::LEFT;
		ChangeDirText_ = "Left";
		FrogAnimationRender_->ChangeAnimation("Move_" + ChangeDirText_);
		MoveDir_.x = -1.f;

		Range_ = static_cast<float>(RandomValue_.RandomInt(100, 500));
	}
	if (RGB(0, 0, 0) == LeftColor)
	{
		CurrentDir_ = FrogDir::RIGHT;
		ChangeDirText_ = "Right";
		FrogAnimationRender_->ChangeAnimation("Move_" + ChangeDirText_);
		MoveDir_.x = 1.f;

		Range_ = static_cast<float>(RandomValue_.RandomInt(100, 500));
	}
	if (RGB(255, 255, 255) == DColor)
	{
		if (CurrentDir_ == FrogDir::LEFT)
		{
			ChangeDirText_ = "Left";
			ChangeState(FrogState::DOWN);
			JumpTime_ = static_cast<float>(RandomValue_.RandomInt(1, 5));
			return;
		}

		if (CurrentDir_ == FrogDir::RIGHT)
		{
			ChangeDirText_ = "Right";
			ChangeState(FrogState::DOWN);
			JumpTime_ = static_cast<float>(RandomValue_.RandomInt(1, 5));
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

			Range_ = static_cast<float>(RandomValue_.RandomInt(100, 500));
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

			Range_ = static_cast<float>(RandomValue_.RandomInt(100, 500));
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
				JumpTime_ = static_cast<float>(RandomValue_.RandomInt(1, 5));
				return;
			}

			if (CurrentDir_ == FrogDir::RIGHT)
			{
				ChangeDirText_ = "Right";
				ChangeState(FrogState::JUMP);
				JumpTime_ = static_cast<float>(RandomValue_.RandomInt(1, 5));
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
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(FrogState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(FrogState::SNOW1);
				return;
			}
		}
	}
	if (true == FrogRCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = FrogDir::RIGHT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	else if (true == FrogLCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = FrogDir::LEFT;
		ChangeState(FrogState::DEFEATED);
		return;
	}

	if (true == FrogRCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		CurrentDir_ = FrogDir::RIGHT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	else if (true == FrogLCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		CurrentDir_ = FrogDir::LEFT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());

	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;

	if (MoveDir_.y < 0)
	{
		return;
	}

	int Color = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 45.0f });
	int CColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 35.0f });
	int RColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ 15.0f, 0.0f });
	int LColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ -15.0f, 0.0f });
	if (RGB(0, 0, 0) == Color && RGB(255, 255, 255) == CColor)
	{
		MoveDir_.y = 0.0f;
		ChangeState(FrogState::IDLE);
		return;
	}
	if (RGB(0, 0, 0) == RColor || RGB(0, 0, 0) == LColor)
	{
		MoveDir_.x = 0.0f;
		return;
	}
}

void Frog::DownUpdate()
{
	if (true == FrogCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(FrogState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(FrogState::SNOW1);
				return;
			}
		}
	}
	if (true == FrogRCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = FrogDir::RIGHT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	else if (true == FrogLCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = FrogDir::LEFT;
		ChangeState(FrogState::DEFEATED);
		return;
	}

	if (true == FrogRCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		CurrentDir_ = FrogDir::RIGHT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	else if (true == FrogLCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		CurrentDir_ = FrogDir::LEFT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;

	if (MoveDir_.y < 0)
	{
		return;
	}

	int Color = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 45.0f });
	if (RGB(0, 0, 0) == Color)
	{
		MoveDir_ = float4::ZERO;
		ChangeState(FrogState::MOVE);
		return;
	}
}

void Frog::AttackUpdate()
{
	if (true == FrogCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(FrogState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(FrogState::SNOW1);
				return;
			}
		}
	}
	if (true == FrogRCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = FrogDir::RIGHT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	else if (true == FrogLCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = FrogDir::LEFT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	
	if (true == FrogRCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		CurrentDir_ = FrogDir::RIGHT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	else if (true == FrogLCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		CurrentDir_ = FrogDir::LEFT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	//SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	GameEngineRandom RandomValue_;
	AttackTime_ -= GameEngineTime::GetDeltaTime();
	if (AttackTime_ <= 0)
	{
		AttackTime_ = static_cast<float>(RandomValue_.RandomInt(1, 3));
		ChangeState(FrogState::IDLE);
		return;
	}
}

void Frog::Snow1Update()
{
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;
	
	if (true == FrogSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(FrogState::SNOW2);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(FrogState::SNOW2);
				return;
			}
		}
	}
	if (false == FrogSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		MeltingTime_ -= GameEngineTime::GetDeltaTime();
		if (MeltingTime_ < 0)
		{
			ChangeState(FrogState::SHAKINGSNOW);
			return;
		}
	}
	if (true == FrogRCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = FrogDir::RIGHT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	else if (true == FrogLCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = FrogDir::LEFT;
		ChangeState(FrogState::DEFEATED);
		return;
	}

	if (true == FrogRCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		CurrentDir_ = FrogDir::RIGHT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	else if (true == FrogLCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		CurrentDir_ = FrogDir::LEFT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	
	int Color = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 45.0f });
	int CColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 35.0f });
	if (RGB(0, 0, 0) == Color && RGB(255, 255, 255) == CColor)
	{
		MoveDir_ = float4::ZERO;
	}
}

void Frog::Snow2Update()
{
	if (true == FrogSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(FrogState::SNOW3);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(FrogState::SNOW3);
				return;
			}
		}
	}
	if (false == FrogSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		MeltingTime_ -= GameEngineTime::GetDeltaTime();
		if (MeltingTime_ < 0)
		{
			ChangeState(FrogState::SNOW1);
			return;
		}
	}
	if (true == FrogRCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = FrogDir::RIGHT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	else if (true == FrogLCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = FrogDir::LEFT;
		ChangeState(FrogState::DEFEATED);
		return;
	}

	if (true == FrogRCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		CurrentDir_ = FrogDir::RIGHT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	else if (true == FrogLCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		CurrentDir_ = FrogDir::LEFT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
}

void Frog::Snow3Update()
{
	// MeltingTime_ ???? ???? ?? ???????? ???????? Snow3, ?? ???? ?? ???????? Snow2
	MeltingTime_ -= GameEngineTime::GetDeltaTime();
	if (MeltingTime_ > 0.0f)
	{
		if (true == FrogSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
		{
			MeltingTime_ = 5.0f;
			return;
		}
	}
	else if (MeltingTime_ <= 0.0f)
	{
		if (false == FrogSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
		{
			ChangeState(FrogState::SNOW2);
			FrogSnowRCollision_->Death();
			FrogSnowLCollision_->Death();
			return;
		}
	}

	if (true == FrogRCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = FrogDir::RIGHT;
		ChangeState(FrogState::BLUESNOWBALL);
		return;
	}
	else if (true == FrogLCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = FrogDir::LEFT;
		ChangeState(FrogState::BLUESNOWBALL);
		return;
	}
	
	if (true == FrogSnowRCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT) && true == GameEngineInput::GetInst()->IsPress("ColDamage"))
	{
		// ?????????? ?????????? ????????
		Score::ScoreUI_ += 500;
		CurrentDir_ = FrogDir::RIGHT;
		ChangeState(FrogState::SNOWBALL);
		return;
	}
	if (true == FrogSnowLCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT) && true == GameEngineInput::GetInst()->IsPress("ColDamage"))
	{
		// ?????????? ???????? ????????
		Score::ScoreUI_ += 500;
		CurrentDir_ = FrogDir::LEFT;
		ChangeState(FrogState::SNOWBALL);
		return;
	}

	float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	float4 CheckPos = NextPos + float4(0.0f, 44.0f);

	int Color = FloorColImage_->GetImagePixel(CheckPos);
	int DColor = FloorColImage_->GetImagePixel(CheckPos + float4(0.0f, 0.0f));
	if (RGB(0, 0, 0) != Color)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (RGB(255, 255, 255) == DColor)
	{
		MoveDir_ = float4::DOWN * 2.0f;
		return;
	}
}

void Frog::SnowBallUpdate()
{
	SnowBallDeathTime_ -= GameEngineTime::GetDeltaTime();
	MoveDir_.y = 0.0f;
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 600);

	FrogDir CheckDir_ = CurrentDir_;

	if (CurrentDir_ == FrogDir::LEFT)
	{
		MoveDir_.x = -1.f;

	}

	if (CurrentDir_ == FrogDir::RIGHT)
	{
		MoveDir_.x = 1.f;
	}

	float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * 600);
	float4 CheckBotPos = NextPos + float4(0.0f, 45.0f);
	float4 CheckRightPos = NextPos + float4(15.0f, 0.0f);
	float4 CheckLeftPos = NextPos + float4(-15.0f, 0.0f);

	int BotColor = FloorColImage_->GetImagePixel(CheckBotPos);
	int RightColor = FloorColImage_->GetImagePixel(CheckRightPos);
	int LeftColor = FloorColImage_->GetImagePixel(CheckLeftPos);
	int DColor = FloorColImage_->GetImagePixel(CheckBotPos + float4(0.0f, 1.0f));
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 3500.0f;
	if (RGB(0, 0, 0) != BotColor)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 200);
	}
	if (RGB(0, 0, 0) == RightColor)
	{
		Score::ScoreUI_ += 10;
		CurrentDir_ = FrogDir::LEFT;
		MoveDir_.x = -1.f;
	}
	if (RGB(255, 0, 0) == RightColor)
	{
		MoveDir_ = float4::ZERO;
		DeathTime_ -= GameEngineTime::GetDeltaTime();
		if (true == DeathCheck_)
		{
			FrogAnimationRender_->ChangeAnimation("SnowBallEffect");
			DeathTime_ = 0.1f;
			DeathCheck_ = false;
		}
		if (DeathTime_ <= 0)
		{
			GameEngineSound::SoundPlayOneShot("SnowBallDeath_Effect(5).mp3", 0);
			Death();
		}
	}
	if (RGB(0, 0, 0) == LeftColor)
	{
		Score::ScoreUI_ += 10;
		CurrentDir_ = FrogDir::RIGHT;
		MoveDir_.x = 1.f;
	}
	if (RGB(255, 0, 0) == LeftColor)
	{
		MoveDir_ = float4::ZERO;
		DeathTime_ -= GameEngineTime::GetDeltaTime();
		if (true == DeathCheck_)
		{
			FrogAnimationRender_->ChangeAnimation("SnowBallEffect");
			DeathTime_ = 0.1f;
			DeathCheck_ = false;
		}
		if (DeathTime_ <= 0)
		{
			GameEngineSound::SoundPlayOneShot("SnowBallDeath_Effect(5).mp3", 0);
			Death();
		}
	}
	if (RGB(255, 255, 255) == DColor)
	{
		if (CurrentDir_ == FrogDir::LEFT)
		{
			MoveDir_.x = -1.f;
		}

		if (CurrentDir_ == FrogDir::RIGHT)
		{
			MoveDir_.x = 1.f;
		}
	}
	if (SnowBallDeathTime_ <= 0)
	{
		DeathTime_ -= GameEngineTime::GetDeltaTime();
		if (true == DeathCheck_)
		{
			FrogAnimationRender_->ChangeAnimation("SnowBallEffect");
			DeathTime_ = 0.1f;
			DeathCheck_ = false;
		}
		if (DeathTime_ <= 0)
		{
			GameEngineSound::SoundPlayOneShot("SnowBallDeath_Effect(5).mp3", 0);
			Death();
		}
	}
}

void Frog::BlueSnowBallUpdate()
{
	SnowBallDeathTime_ -= GameEngineTime::GetDeltaTime();
	MoveDir_.y = 0.0f;
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 600);

	FrogDir CheckDir_ = CurrentDir_;

	if (CurrentDir_ == FrogDir::LEFT)
	{
		MoveDir_.x = -1.f;

	}

	if (CurrentDir_ == FrogDir::RIGHT)
	{
		MoveDir_.x = 1.f;
	}

	float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * 600);
	float4 CheckBotPos = NextPos + float4(0.0f, 45.0f);
	float4 CheckRightPos = NextPos + float4(15.0f, 0.0f);
	float4 CheckLeftPos = NextPos + float4(-15.0f, 0.0f);

	int BotColor = FloorColImage_->GetImagePixel(CheckBotPos);
	int RightColor = FloorColImage_->GetImagePixel(CheckRightPos);
	int LeftColor = FloorColImage_->GetImagePixel(CheckLeftPos);
	int DColor = FloorColImage_->GetImagePixel(CheckBotPos + float4(0.0f, 1.0f));
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 3500.0f;
	if (RGB(0, 0, 0) != BotColor)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 200);
	}
	if (RGB(0, 0, 0) == RightColor)
	{
		Score::ScoreUI_ += 10;
		CurrentDir_ = FrogDir::LEFT;
		MoveDir_.x = -1.f;
	}
	if (RGB(255, 0, 0) == RightColor)
	{
		MoveDir_ = float4::ZERO;
		DeathTime_ -= GameEngineTime::GetDeltaTime();
		if (true == DeathCheck_)
		{
			FrogAnimationRender_->ChangeAnimation("SnowBallEffect");
			DeathTime_ = 0.1f;
			DeathCheck_ = false;
		}
		if (DeathTime_ <= 0)
		{
			GameEngineSound::SoundPlayOneShot("SnowBallDeath_Effect(5).mp3", 0);
			Death();
		}
	}
	if (RGB(0, 0, 0) == LeftColor)
	{
		Score::ScoreUI_ += 10;
		CurrentDir_ = FrogDir::RIGHT;
		MoveDir_.x = 1.f;
	}
	if (RGB(255, 0, 0) == LeftColor)
	{
		MoveDir_ = float4::ZERO;
		DeathTime_ -= GameEngineTime::GetDeltaTime();
		if (true == DeathCheck_)
		{
			FrogAnimationRender_->ChangeAnimation("SnowBallEffect");
			DeathTime_ = 0.1f;
			DeathCheck_ = false;
		}
		if (DeathTime_ <= 0)
		{
			GameEngineSound::SoundPlayOneShot("SnowBallDeath_Effect(5).mp3", 0);
			Death();
		}
	}
	if (RGB(255, 255, 255) == DColor)
	{
		if (CurrentDir_ == FrogDir::LEFT)
		{
			MoveDir_.x = -1.f;
		}

		if (CurrentDir_ == FrogDir::RIGHT)
		{
			MoveDir_.x = 1.f;
		}
	}
	if (SnowBallDeathTime_ <= 0)
	{
		DeathTime_ -= GameEngineTime::GetDeltaTime();
		if (true == DeathCheck_)
		{
			FrogAnimationRender_->ChangeAnimation("SnowBallEffect");
			DeathTime_ = 0.1f;
			DeathCheck_ = false;
		}
		if (DeathTime_ <= 0)
		{
			GameEngineSound::SoundPlayOneShot("SnowBallDeath_Effect(5).mp3", 0);
			Death();
		}
	}
}

void Frog::ShakingSnowUpdate()
{
	if (true == FrogRCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = FrogDir::RIGHT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	else if (true == FrogLCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = FrogDir::LEFT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	
	if (true == FrogRCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		CurrentDir_ = FrogDir::RIGHT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	else if (true == FrogLCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		CurrentDir_ = FrogDir::LEFT;
		ChangeState(FrogState::DEFEATED);
		return;
	}
	ShakingTime_ -= GameEngineTime::GetDeltaTime();
	if (ShakingTime_ <= 0)
	{
		ChangeState(FrogState::IDLE);
		return;
	}

	if (true == FrogCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(FrogState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(FrogState::SNOW1);
				return;
			}
		}
	}
}

void Frog::DefeatedUpdate()
{
	int Color = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 45.0f });
	int CColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 35.0f });
	int RColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ 15.0f, 0.0f });
	int LColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ -15.0f, 0.0f });

	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	if (RGB(255, 255, 0) == RColor)
	{
		CurrentDir_ = FrogDir::LEFT;
		MoveDir_ = float4{ -Speed_,MoveDir_.y };
	}
	if (RGB(255, 255, 0) == LColor)
	{
		CurrentDir_ = FrogDir::RIGHT;
		MoveDir_ = float4{ Speed_,MoveDir_.y };
	}
	
	if (CurrentDir_ == FrogDir::LEFT)
	{
		MoveDir_ = float4{ -Speed_,MoveDir_.y };

	}
	if (CurrentDir_ == FrogDir::RIGHT)
	{
		MoveDir_ = float4{ Speed_,MoveDir_.y };
	}
	
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;

	if (MoveDir_.y < 0)
	{
		return;
	}

	if (RGB(0, 0, 0) == Color && RGB(0, 0, 0) == CColor)
	{
		return;
	}
	if (RGB(0, 0, 0) == Color)
	{
		//MoveDir_.y = 0.0f;
		MoveDir_ = float4::ZERO;
		ChangeState(FrogState::DEATH);
		return;
	}
}

void Frog::DeathUpdate()
{
	ItemTime_ -= GameEngineTime::GetDeltaTime();
	if (ItemTime_ <= 0)
	{
		RandomItem();
		Death();
	}
}

//===========================Start==========================
void Frog::StartDownStart()
{
	AnimationName_ = "Jump_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Right";
	}
	FrogAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

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
	AnimationName_ = "Jump_";
	FrogAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Frog::AttackStart()
{
	AttackTime_ = 0.15f;
	AnimationName_ = "Attack_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Right";
	}
	FrogAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);

	FrogFire* Ptr = GetLevel()->CreateActor<FrogFire>();
	Ptr->SetPosition(GetPosition());

	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	if (CurrentDir_ == FrogDir::LEFT)
	{
		Ptr->SetDir(float4::LEFT);
		Ptr->SetBDir("Left");
	}
	if (CurrentDir_ == FrogDir::RIGHT)
	{
		Ptr->SetDir(float4::RIGHT);
		Ptr->SetBDir("Right");
	}
}

void Frog::Snow1Start()
{
	FrogCollision_->Off();
	AnimationName_ = "Snow1";
	FrogAnimationRender_->ChangeAnimation(AnimationName_);
	FrogAnimationRender_->SetPivot({ 0,20.0f });

	FrogSnowCollision_->On();

	DamageCount_ = 2;
	MeltingTime_ = 3.0f;
}

void Frog::Snow2Start()
{
	FrogRCollision_->On();
	FrogLCollision_->On();
	AnimationName_ = "Snow2";
	FrogAnimationRender_->ChangeAnimation(AnimationName_);
	FrogAnimationRender_->SetPivot({ 0,20.0f });

	DamageCount_ = 2;
	MeltingTime_ = 3.0f;
}

void Frog::Snow3Start()
{
	//FrogRCollision_->Off();
	//FrogLCollision_->Off();
	AnimationName_ = "Snow3";
	FrogAnimationRender_->ChangeAnimation(AnimationName_);
	FrogAnimationRender_->SetPivot({ 0,5 });

	FrogSnowRCollision_ = CreateCollision("SnowRColBox", { 5, 10 }, { -15, 0 });
	FrogSnowLCollision_ = CreateCollision("SnowLColBox", { 5, 10 }, { 15, 0 });

	MeltingTime_ = 5.0f;
}

void Frog::SnowBallStart()
{
	FrogSnowCollision_->Off();
	FrogSnowRCollision_->Off();
	FrogSnowLCollision_->Off();
	AnimationName_ = "SnowballRolling";
	FrogAnimationRender_->ChangeAnimation(AnimationName_);
	FrogAnimationRender_->SetPivot({ 0,0 });

	FrogSnowBallCollision_ = CreateCollision("SnowBallColBox", { 60, 60 });
	FrogSnowBallRCollision_ = CreateCollision("SnowBallRColBox", { 5, 10 }, { -15, 0 });
	FrogSnowBallLCollision_ = CreateCollision("SnowBallLColBox", { 5, 10 }, { 15, 0 });
}

void Frog::BlueSnowBallStart()
{
	FrogSnowCollision_->Off();
	FrogSnowRCollision_->Off();
	FrogSnowLCollision_->Off();
	AnimationName_ = "BlueSnowBall";
	FrogAnimationRender_->ChangeAnimation(AnimationName_);
	FrogAnimationRender_->SetPivot({ 0,0 });

	FrogBlueSnowBallCollision_ = CreateCollision("BlueSnowBallColBox", { 60, 60 });
}

void Frog::ShakingSnowStart()
{
	FrogSnowCollision_->Off();
	AnimationName_ = "ShakingSnow";
	FrogAnimationRender_->ChangeAnimation(AnimationName_);
	FrogAnimationRender_->SetPivot({ 0,0 });

	FrogCollision_->On();
	
	DamageCount_ = 2;
	ShakingTime_ = 1.0f;
}

void Frog::DefeatedStart()
{
	FrogCollision_->Off();
	FrogRCollision_->Off();
	FrogLCollision_->Off();
	GameEngineSound::SoundPlayOneShot("SnowBallHitEnemy_Effect(11).mp3", 0);
	AnimationName_ = "Defeated";
	FrogAnimationRender_->ChangeAnimation(AnimationName_);

	MoveDir_ = float4::UP * 800.0f;
}

void Frog::DeathStart()
{
	FrogCollision_->Off();
	AnimationName_ = "Death";
	FrogAnimationRender_->ChangeAnimation(AnimationName_);
	FrogAnimationRender_->SetPivot({ 0,20 });
}