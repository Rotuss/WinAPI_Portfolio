#include "YellowTroll.h"
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

void YellowTroll::StartDownUpdate()
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
		ChangeState(YellowTrollState::IDLE);
		return;
	}
}

void YellowTroll::IdleUpdate()
{
	GameEngineRandom RandomValue_;
	MoveTime_ -= GameEngineTime::GetDeltaTime();
	MoveDir_ = float4::ZERO;
	if (MoveTime_ <= 0)
	{
		if (StartMoveCount_ <= 0)
		{
			ChangeState(YellowTrollState::MOVE);
			MoveTime_ = 0.3f;
			return;
		}
		else
		{
			ChangeState(YellowTrollState::STARTMOVE);
			MoveTime_ = 0.3f;
			return;
		}
	}
	if (true == YellowTrollCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(YellowTrollState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(YellowTrollState::SNOW1);
				return;
			}
		}
	}
	if (true == YellowTrollRCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = YellowTrollDir::RIGHT;
		ChangeState(YellowTrollState::DEFEATED);
		return;
	}
	else if (true == YellowTrollLCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = YellowTrollDir::LEFT;
		ChangeState(YellowTrollState::DEFEATED);
		return;
	}

	float4 CheckPos = GetPosition() + float4(0.0f, 44.0f);

	int DColor = FloorColImage_->GetImagePixel(CheckPos + float4(0.0f, 5.0f));
	if (RGB(0, 0, 0) != DColor && CurrentState_ != YellowTrollState::JUMP)
	{
		ChangeState(YellowTrollState::DOWN);
		return;
	}
}

void YellowTroll::StartMoveUpdate()
{
	if (true == YellowTrollCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(YellowTrollState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(YellowTrollState::SNOW1);
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

	if (RGB(0, 0, 0) != BotColor && CurrentState_ != YellowTrollState::JUMP)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	}
	if (RGB(0, 0, 0) == RightColor)
	{
		CurrentDir_ = YellowTrollDir::LEFT;
		ChangeDirText_ = "Left";
		YellowTrollAnimationRender_->ChangeAnimation("Move_" + ChangeDirText_);
		MoveDir_.x = -1.f;

		Range_ = 30.0f;
	}
	if (RGB(0, 0, 0) == LeftColor)
	{
		CurrentDir_ = YellowTrollDir::RIGHT;
		ChangeDirText_ = "Right";
		YellowTrollAnimationRender_->ChangeAnimation("Move_" + ChangeDirText_);
		MoveDir_.x = 1.f;

		Range_ = 30.0f;
	}
	if (RGB(255, 255, 255) == DColor)
	{
		ChangeState(YellowTrollState::DOWN);
		return;
	}

	Range_ -= GameEngineTime::GetDeltaTime() * Speed_;

	YellowTrollDir CheckDir_ = CurrentDir_;

	if (CurrentDir_ == YellowTrollDir::LEFT)
	{
		if (Range_ <= 0)
		{
			CurrentDir_ = YellowTrollDir::RIGHT;
			ChangeDirText_ = "Right";
			ChangeState(YellowTrollState::IDLE);

			Range_ = 30.0f;
			return;
		}
		else
		{
			MoveDir_.x = -1.f;
		}
	}

	if (CurrentDir_ == YellowTrollDir::RIGHT)
	{
		if (Range_ <= 0)
		{
			CurrentDir_ = YellowTrollDir::LEFT;
			ChangeDirText_ = "Left";
			ChangeState(YellowTrollState::IDLE);

			Range_ = 30.0f;
			return;
		}
		else
		{
			MoveDir_.x = 1.f;
		}
	}
}

void YellowTroll::MoveUpdate()
{
	GameEngineRandom RandomValue_;
	if (true == YellowTrollCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(YellowTrollState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(YellowTrollState::SNOW1);
				return;
			}
		}
	}
	if (true == YellowTrollRCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = YellowTrollDir::RIGHT;
		ChangeState(YellowTrollState::DEFEATED);
		return;
	}
	else if (true == YellowTrollLCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = YellowTrollDir::LEFT;
		ChangeState(YellowTrollState::DEFEATED);
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

	if (RGB(0, 0, 0) != BotColor && CurrentState_ != YellowTrollState::JUMP)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (RGB(0, 0, 0) == RightColor)
	{
		CurrentDir_ = YellowTrollDir::LEFT;
		ChangeDirText_ = "Left";
		YellowTrollAnimationRender_->ChangeAnimation("Move_" + ChangeDirText_);
		MoveDir_.x = -1.f;

		Range_ = static_cast<float>(RandomValue_.RandomInt(100, 500));
	}
	if (RGB(0, 0, 0) == LeftColor)
	{
		CurrentDir_ = YellowTrollDir::RIGHT;
		ChangeDirText_ = "Right";
		YellowTrollAnimationRender_->ChangeAnimation("Move_" + ChangeDirText_);
		MoveDir_.x = 1.f;

		Range_ = static_cast<float>(RandomValue_.RandomInt(100, 500));
	}
	if (RGB(255, 255, 255) == DColor)
	{
		if (CurrentDir_ == YellowTrollDir::LEFT)
		{
			ChangeDirText_ = "Left";
			ChangeState(YellowTrollState::DOWN);
			JumpTime_ = static_cast<float>(RandomValue_.RandomInt(1, 5));
			return;
		}

		if (CurrentDir_ == YellowTrollDir::RIGHT)
		{
			ChangeDirText_ = "Right";
			ChangeState(YellowTrollState::DOWN);
			JumpTime_ = static_cast<float>(RandomValue_.RandomInt(1, 5));
			return;
		}
	}

	Range_ -= GameEngineTime::GetDeltaTime() * Speed_;

	YellowTrollDir CheckDir_ = CurrentDir_;

	if (CurrentDir_ == YellowTrollDir::LEFT)
	{
		if (Range_ <= 0)
		{
			CurrentDir_ = YellowTrollDir::RIGHT;
			ChangeDirText_ = "Right";
			ChangeState(YellowTrollState::IDLE);

			Range_ = static_cast<float>(RandomValue_.RandomInt(100, 500));
			return;
		}
		else
		{
			MoveDir_.x = -1.f;
		}
	}

	if (CurrentDir_ == YellowTrollDir::RIGHT)
	{
		if (Range_ <= 0)
		{
			CurrentDir_ = YellowTrollDir::LEFT;
			ChangeDirText_ = "Left";
			ChangeState(YellowTrollState::IDLE);

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
			if (CurrentDir_ == YellowTrollDir::LEFT)
			{
				ChangeDirText_ = "Left";
				ChangeState(YellowTrollState::JUMP);
				JumpTime_ = static_cast<float>(RandomValue_.RandomInt(1, 5));
				return;
			}

			if (CurrentDir_ == YellowTrollDir::RIGHT)
			{
				ChangeDirText_ = "Right";
				ChangeState(YellowTrollState::JUMP);
				JumpTime_ = static_cast<float>(RandomValue_.RandomInt(1, 5));
				return;
			}
		}
		ChangeState(YellowTrollState::MOVE);
		return;
	}
}

void YellowTroll::JumpUpdate()
{
	if (true == YellowTrollCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(YellowTrollState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(YellowTrollState::SNOW1);
				return;
			}
		}
	}
	if (true == YellowTrollRCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = YellowTrollDir::RIGHT;
		ChangeState(YellowTrollState::DEFEATED);
		return;
	}
	else if (true == YellowTrollLCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = YellowTrollDir::LEFT;
		ChangeState(YellowTrollState::DEFEATED);
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
		ChangeState(YellowTrollState::IDLE);
		return;
	}
	if (RGB(0, 0, 0) == RColor || RGB(0, 0, 0) == LColor)
	{
		MoveDir_.x = 0.0f;
		return;
	}
}

void YellowTroll::DownUpdate()
{
	if (true == YellowTrollCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(YellowTrollState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(YellowTrollState::SNOW1);
				return;
			}
		}
	}
	if (true == YellowTrollRCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = YellowTrollDir::RIGHT;
		ChangeState(YellowTrollState::DEFEATED);
		return;
	}
	else if (true == YellowTrollLCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = YellowTrollDir::LEFT;
		ChangeState(YellowTrollState::DEFEATED);
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
		ChangeState(YellowTrollState::MOVE);
		return;
	}
}

void YellowTroll::Snow1Update()
{
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;

	if (true == YellowTrollSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(YellowTrollState::SNOW2);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(YellowTrollState::SNOW2);
				return;
			}
		}
	}
	if (false == YellowTrollSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		MeltingTime_ -= GameEngineTime::GetDeltaTime();
		if (MeltingTime_ < 0)
		{
			ChangeState(YellowTrollState::SHAKINGSNOW);
			return;
		}
	}
	if (true == YellowTrollRCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = YellowTrollDir::RIGHT;
		ChangeState(YellowTrollState::DEFEATED);
		return;
	}
	else if (true == YellowTrollLCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = YellowTrollDir::LEFT;
		ChangeState(YellowTrollState::DEFEATED);
		return;
	}

	int Color = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 45.0f });
	int CColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 35.0f });
	if (RGB(0, 0, 0) == Color && RGB(255, 255, 255) == CColor)
	{
		MoveDir_ = float4::ZERO;
	}
}

void YellowTroll::Snow2Update()
{
	if (true == YellowTrollSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(YellowTrollState::SNOW3);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(YellowTrollState::SNOW3);
				return;
			}
		}
	}
	if (false == YellowTrollSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		MeltingTime_ -= GameEngineTime::GetDeltaTime();
		if (MeltingTime_ < 0)
		{
			ChangeState(YellowTrollState::SNOW1);
			return;
		}
	}
	if (true == YellowTrollRCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = YellowTrollDir::RIGHT;
		ChangeState(YellowTrollState::DEFEATED);
		return;
	}
	else if (true == YellowTrollLCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = YellowTrollDir::LEFT;
		ChangeState(YellowTrollState::DEFEATED);
		return;
	}
}

void YellowTroll::Snow3Update()
{
	// MeltingTime_ 시간 동안 한 번이라도 부딪히면 Snow3, 한 번도 안 부딪히면 Snow2
	MeltingTime_ -= GameEngineTime::GetDeltaTime();
	if (MeltingTime_ > 0.0f)
	{
		if (true == YellowTrollSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
		{
			MeltingTime_ = 5.0f;
			return;
		}
	}
	else if (MeltingTime_ <= 0.0f)
	{
		if (false == YellowTrollSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
		{
			ChangeState(YellowTrollState::SNOW2);
			YellowTrollSnowRCollision_->Death();
			YellowTrollSnowLCollision_->Death();
			return;
		}
	}

	if (true == YellowTrollSnowRCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT) && true == GameEngineInput::GetInst()->IsPress("ColDamage"))
	{
		// 스노우볼이 오른쪽으로 굴러야함
		Score::ScoreUI_ += 500;
		CurrentDir_ = YellowTrollDir::RIGHT;
		ChangeState(YellowTrollState::SNOWBALL);
		return;
	}
	if (true == YellowTrollSnowLCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT) && true == GameEngineInput::GetInst()->IsPress("ColDamage"))
	{
		// 스노우볼이 왼쪽으로 굴러야함
		Score::ScoreUI_ += 500;
		CurrentDir_ = YellowTrollDir::LEFT;
		ChangeState(YellowTrollState::SNOWBALL);
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

void YellowTroll::SnowBallUpdate()
{
	SnowBallDeathTime_ -= GameEngineTime::GetDeltaTime();
	MoveDir_.y = 0.0f;
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 600);

	YellowTrollDir CheckDir_ = CurrentDir_;

	if (CurrentDir_ == YellowTrollDir::LEFT)
	{
		MoveDir_.x = -1.f;

	}

	if (CurrentDir_ == YellowTrollDir::RIGHT)
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
		CurrentDir_ = YellowTrollDir::LEFT;
		MoveDir_.x = -1.f;
	}
	if (RGB(255, 0, 0) == RightColor)
	{
		MoveDir_ = float4::ZERO;
		DeathTime_ -= GameEngineTime::GetDeltaTime();
		if (true == DeathCheck_)
		{
			YellowTrollAnimationRender_->ChangeAnimation("SnowBallEffect");
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
		CurrentDir_ = YellowTrollDir::RIGHT;
		MoveDir_.x = 1.f;
	}
	if (RGB(255, 0, 0) == LeftColor)
	{
		MoveDir_ = float4::ZERO;
		DeathTime_ -= GameEngineTime::GetDeltaTime();
		if (true == DeathCheck_)
		{
			YellowTrollAnimationRender_->ChangeAnimation("SnowBallEffect");
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
		if (CurrentDir_ == YellowTrollDir::LEFT)
		{
			MoveDir_.x = -1.f;
		}

		if (CurrentDir_ == YellowTrollDir::RIGHT)
		{
			MoveDir_.x = 1.f;
		}
	}
	if (SnowBallDeathTime_ <= 0)
	{
		DeathTime_ -= GameEngineTime::GetDeltaTime();
		if (true == DeathCheck_)
		{
			YellowTrollAnimationRender_->ChangeAnimation("SnowBallEffect");
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

void YellowTroll::ShakingSnowUpdate()
{
	if (true == YellowTrollRCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = YellowTrollDir::RIGHT;
		ChangeState(YellowTrollState::DEFEATED);
		return;
	}
	else if (true == YellowTrollLCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		CurrentDir_ = YellowTrollDir::LEFT;
		ChangeState(YellowTrollState::DEFEATED);
		return;
	}
	ShakingTime_ -= GameEngineTime::GetDeltaTime();
	if (ShakingTime_ <= 0)
	{
		ChangeState(YellowTrollState::IDLE);
		return;
	}

	if (true == YellowTrollCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(YellowTrollState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(YellowTrollState::SNOW1);
				return;
			}
		}
	}
}

void YellowTroll::DefeatedUpdate()
{
	int Color = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 45.0f });
	int CColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 35.0f });
	int RColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ 15.0f, 0.0f });
	int LColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ -15.0f, 0.0f });

	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	if (RGB(255, 255, 0) == RColor)
	{
		CurrentDir_ = YellowTrollDir::LEFT;
		MoveDir_ = float4{ -Speed_,MoveDir_.y };
	}
	if (RGB(255, 255, 0) == LColor)
	{
		CurrentDir_ = YellowTrollDir::RIGHT;
		MoveDir_ = float4{ Speed_,MoveDir_.y };
	}
	if (CurrentDir_ == YellowTrollDir::LEFT)
	{
		MoveDir_ = float4{ -Speed_,MoveDir_.y };

	}
	if (CurrentDir_ == YellowTrollDir::RIGHT)
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
		ChangeState(YellowTrollState::DEATH);
		return;
	}
}

void YellowTroll::DeathUpdate()
{
	ItemTime_ -= GameEngineTime::GetDeltaTime();
	if (ItemTime_ <= 0)
	{
		RandomItem();
		Death();
	}
}

//===========================Start==========================
void YellowTroll::StartDownStart()
{
	AnimationName_ = "Jump_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Right";
	}
	YellowTrollAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void YellowTroll::IdleStart()
{
	StartMoveCount_ -= 1;
	AnimationName_ = "Idle_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Right";
	}
	YellowTrollAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void YellowTroll::StartMoveStart()
{
	AnimationName_ = "Move_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Right";
	}
	YellowTrollAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void YellowTroll::MoveStart()
{
	AnimationName_ = "Move_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Right";
	}
	YellowTrollAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void YellowTroll::JumpStart()
{
	AnimationName_ = "Jump_";
	YellowTrollAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);

	MoveDir_ = float4::UP * 520.0f;
}

void YellowTroll::DownStart()
{
	AnimationName_ = "Jump_";
	YellowTrollAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void YellowTroll::Snow1Start()
{
	YellowTrollCollision_->Off();
	AnimationName_ = "Snow1";
	YellowTrollAnimationRender_->ChangeAnimation(AnimationName_);
	YellowTrollAnimationRender_->SetPivot({ 0,20.0f });

	YellowTrollSnowCollision_->On();

	DamageCount_ = 2;
	MeltingTime_ = 3.0f;
}

void YellowTroll::Snow2Start()
{
	YellowTrollRCollision_->On();
	YellowTrollLCollision_->On();
	AnimationName_ = "Snow2";
	YellowTrollAnimationRender_->ChangeAnimation(AnimationName_);
	YellowTrollAnimationRender_->SetPivot({ 0,20.0f });

	DamageCount_ = 2;
	MeltingTime_ = 3.0f;
}

void YellowTroll::Snow3Start()
{
	YellowTrollRCollision_->Off();
	YellowTrollLCollision_->Off();
	AnimationName_ = "Snow3";
	YellowTrollAnimationRender_->ChangeAnimation(AnimationName_);
	YellowTrollAnimationRender_->SetPivot({ 0,5 });

	YellowTrollSnowRCollision_ = CreateCollision("SnowRColBox", { 5, 10 }, { -15, 0 });
	YellowTrollSnowLCollision_ = CreateCollision("SnowLColBox", { 5, 10 }, { 15, 0 });

	MeltingTime_ = 5.0f;
}

void YellowTroll::SnowBallStart()
{
	YellowTrollSnowCollision_->Off();
	YellowTrollSnowRCollision_->Off();
	YellowTrollSnowLCollision_->Off();
	AnimationName_ = "SnowballRolling";
	YellowTrollAnimationRender_->ChangeAnimation(AnimationName_);
	YellowTrollAnimationRender_->SetPivot({ 0,0 });

	YellowTrollSnowBallCollision_ = CreateCollision("SnowBallColBox", { 60, 60 });
	YellowTrollSnowBallRCollision_ = CreateCollision("SnowBallRColBox", { 5, 10 }, { -15, 0 });
	YellowTrollSnowBallLCollision_ = CreateCollision("SnowBallLColBox", { 5, 10 }, { 15, 0 });
}

void YellowTroll::ShakingSnowStart()
{
	YellowTrollSnowCollision_->Off();
	AnimationName_ = "ShakingSnow";
	YellowTrollAnimationRender_->ChangeAnimation(AnimationName_);
	YellowTrollAnimationRender_->SetPivot({ 0,0 });

	YellowTrollCollision_->On();

	ShakingTime_ = 1.0f;
}

void YellowTroll::DefeatedStart()
{
	YellowTrollCollision_->Off();
	GameEngineSound::SoundPlayOneShot("SnowBallHitEnemy_Effect(11).mp3", 0);
	AnimationName_ = "Defeated";
	YellowTrollAnimationRender_->ChangeAnimation(AnimationName_);

	MoveDir_ = float4::UP * 800.0f;
}

void YellowTroll::DeathStart()
{
	YellowTrollCollision_->Off();
	AnimationName_ = "Death";
	YellowTrollAnimationRender_->ChangeAnimation(AnimationName_);
	YellowTrollAnimationRender_->SetPivot({ 0,20 });
}