#include "RedDemon.h"
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

void RedDemon::StartDownUpdate()
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
		ChangeState(RedDemonState::IDLE);
		return;
	}
}

void RedDemon::IdleUpdate()
{
	MoveTime_ -= GameEngineTime::GetDeltaTime();
	MoveDir_ = float4::ZERO;
	if (MoveTime_ <= 0)
	{
		if (StartMoveCount_ <= 0)
		{
			ChangeState(RedDemonState::MOVE);
			MoveTime_ = 0.3f;
			return;
		}	
		else
		{
			ChangeState(RedDemonState::STARTMOVE);
			MoveTime_ = 0.3f;
			return;
		}
	}
	if (true == RedDemonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(RedDemonState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(RedDemonState::SNOW1);
				return;
			}
		}
	}
	if (true == RedDemonCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		ChangeState(RedDemonState::DEFEATED);
		return;
	}

	float4 CheckPos = GetPosition() + float4(0.0f, 44.0f);

	int DColor = FloorColImage_->GetImagePixel(CheckPos + float4(0.0f, 5.0f));
	if (RGB(0, 0, 0) != DColor && CurrentState_ != RedDemonState::JUMP)
	{
		ChangeState(RedDemonState::DOWN);
		return;
	}
}

void RedDemon::StartMoveUpdate()
{
	if (true == RedDemonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(RedDemonState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(RedDemonState::SNOW1);
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

	if (RGB(0, 0, 0) != BotColor && CurrentState_ != RedDemonState::JUMP)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	}
	if (RGB(0, 0, 0) == RightColor)
	{
		CurrentDir_ = RedDemonDir::LEFT;
		ChangeDirText_ = "Left";
		RedDemonAnimationRender_->ChangeAnimation("Move_" + ChangeDirText_);
		MoveDir_.x = -1.f;

		Range_ = 100.0f;
	}
	if (RGB(0, 0, 0) == LeftColor)
	{
		CurrentDir_ = RedDemonDir::RIGHT;
		ChangeDirText_ = "Right";
		RedDemonAnimationRender_->ChangeAnimation("Move_" + ChangeDirText_);
		MoveDir_.x = 1.f;

		Range_ = 100.0f;
	}
	if (RGB(255, 255, 255) == DColor)
	{
		ChangeState(RedDemonState::DOWN);
		return;
	}

	Range_ -= GameEngineTime::GetDeltaTime() * Speed_;

	RedDemonDir CheckDir_ = CurrentDir_;

	if (CurrentDir_ == RedDemonDir::LEFT)
	{
		if (Range_ <= 0)
		{
			CurrentDir_ = RedDemonDir::RIGHT;
			ChangeDirText_ = "Right";
			ChangeState(RedDemonState::IDLE);

			Range_ = 100.0f;
			return;
		}
		else
		{
			MoveDir_.x = -1.f;
		}
	}

	if (CurrentDir_ == RedDemonDir::RIGHT)
	{
		if (Range_ <= 0)
		{
			CurrentDir_ = RedDemonDir::LEFT;
			ChangeDirText_ = "Left";
			ChangeState(RedDemonState::IDLE);

			Range_ = 100.0f;
			return;
		}
		else
		{
			MoveDir_.x = 1.f;
		}
	}
}

void RedDemon::MoveUpdate()
{
	GameEngineRandom RandomValue_;
	if (true == RedDemonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(RedDemonState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(RedDemonState::SNOW1);
				return;
			}
		}
	}
	if (true == RedDemonCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		ChangeState(RedDemonState::DEFEATED);
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

	if (RGB(0, 0, 0) != BotColor && CurrentState_ != RedDemonState::JUMP)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (RGB(0, 0, 0) == RightColor)
	{
		CurrentDir_ = RedDemonDir::LEFT;
		ChangeDirText_ = "Left";
		RedDemonAnimationRender_->ChangeAnimation("Move_" + ChangeDirText_);
		MoveDir_.x = -1.f;

		Range_ = static_cast<float>(RandomValue_.RandomInt(100,500));
	}
	if (RGB(0, 0, 0) == LeftColor)
	{
		CurrentDir_ = RedDemonDir::RIGHT;
		ChangeDirText_ = "Right";
		RedDemonAnimationRender_->ChangeAnimation("Move_" + ChangeDirText_);
		MoveDir_.x = 1.f;

		Range_ = static_cast<float>(RandomValue_.RandomInt(100, 500));
	}
	if (RGB(255, 255, 255) == DColor)
	{
		if (CurrentDir_ == RedDemonDir::LEFT)
		{
			ChangeDirText_ = "Left";
			ChangeState(RedDemonState::DOWN);
			JumpTime_ = static_cast<float>(RandomValue_.RandomInt(1, 5));
			return;
		}

		if (CurrentDir_ == RedDemonDir::RIGHT)
		{
			ChangeDirText_ = "Right";
			ChangeState(RedDemonState::DOWN);
			JumpTime_ = static_cast<float>(RandomValue_.RandomInt(1, 5));
			return;
		}
	}

	Range_ -= GameEngineTime::GetDeltaTime() * Speed_;

	RedDemonDir CheckDir_ = CurrentDir_;

	if (CurrentDir_ == RedDemonDir::LEFT)
	{
		if (Range_ <= 0)
		{
			CurrentDir_ = RedDemonDir::RIGHT;
			ChangeDirText_ = "Right";
			ChangeState(RedDemonState::IDLE);

			Range_ = static_cast<float>(RandomValue_.RandomInt(100, 500));
			return;
		}
		else
		{
			MoveDir_.x = -1.f;
		}
	}

	if (CurrentDir_ == RedDemonDir::RIGHT)
	{
		if (Range_ <= 0)
		{
			CurrentDir_ = RedDemonDir::LEFT;
			ChangeDirText_ = "Left";
			ChangeState(RedDemonState::IDLE);

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
			if (CurrentDir_ == RedDemonDir::LEFT)
			{
				ChangeDirText_ = "Left";
				ChangeState(RedDemonState::JUMP);
				JumpTime_ = static_cast<float>(RandomValue_.RandomInt(1, 5));
				return;
			}

			if (CurrentDir_ == RedDemonDir::RIGHT)
			{
				ChangeDirText_ = "Right";
				ChangeState(RedDemonState::JUMP);
				JumpTime_ = static_cast<float>(RandomValue_.RandomInt(1, 5));
				return;
			}
		}
		ChangeState(RedDemonState::MOVE);
		return;
	}
}

void RedDemon::JumpUpdate()
{
	if (true == RedDemonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(RedDemonState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(RedDemonState::SNOW1);
				return;
			}
		}
	}
	if (true == RedDemonCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		ChangeState(RedDemonState::DEFEATED);
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
		//MoveDir_.y = 0.0f;
		MoveDir_ = float4::ZERO;
		ChangeState(RedDemonState::IDLE);
		return;
	}
	if (RGB(0, 0, 0) == RColor || RGB(0, 0, 0) == LColor)
	{
		MoveDir_.x = 0.0f;
		return;
	}
}

void RedDemon::DownUpdate()
{	
	if (true == RedDemonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(RedDemonState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(RedDemonState::SNOW1);
				return;
			}
		}
	}
	if (true == RedDemonCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		ChangeState(RedDemonState::DEFEATED);
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
		ChangeState(RedDemonState::MOVE);
		return;
	}
}

void RedDemon::AttackUpdate()
{}

void RedDemon::Snow1Update()
{
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;
	
	if (true == RedDemonSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(RedDemonState::SNOW2);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(RedDemonState::SNOW2);
				return;
			}
		}
	}
	if (false == RedDemonSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		MeltingTime_ -= GameEngineTime::GetDeltaTime();
		if (MeltingTime_ < 0)
		{
			ChangeState(RedDemonState::SHAKINGSNOW);
			return;
		}
	}
	if (true == RedDemonSnowCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		ChangeState(RedDemonState::DEFEATED);
		return;
	}

	int Color = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 45.0f });
	int CColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 35.0f });
	if (RGB(0, 0, 0) == Color && RGB(255, 255, 255) == CColor)
	{
		MoveDir_ = float4::ZERO;
	}
}

void RedDemon::Snow2Update()
{
	if (true == RedDemonSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(RedDemonState::SNOW3);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(RedDemonState::SNOW3);
				return;
			}
		}
	}
	if (false == RedDemonSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		MeltingTime_ -= GameEngineTime::GetDeltaTime();
		if (MeltingTime_ < 0)
		{
			ChangeState(RedDemonState::SNOW1);
			return;
		}
	}
	if (true == RedDemonSnowCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		ChangeState(RedDemonState::DEFEATED);
		return;
	}
}

void RedDemon::Snow3Update()
{
	// MeltingTime_ 시간 동안 한 번이라도 부딪히면 Snow3, 한 번도 안 부딪히면 Snow2
	MeltingTime_ -= GameEngineTime::GetDeltaTime();
	if (MeltingTime_ > 0.0f)
	{
		if (true == RedDemonSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
		{
			MeltingTime_ = 5.0f;
			return;
		}
	}
	else if(MeltingTime_ <= 0.0f)
	{
		if (false == RedDemonSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
		{
			ChangeState(RedDemonState::SNOW2);
			RedDemonSnowRCollision_->Death();
			RedDemonSnowLCollision_->Death();
			return;
		}
	}
	
	if (true == RedDemonSnowRCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT) && true == GameEngineInput::GetInst()->IsPress("ColDamage"))
	{
		// 스노우볼이 오른쪽으로 굴러야함
		Score::ScoreUI_ += 500;
		CurrentDir_ = RedDemonDir::RIGHT;
		ChangeState(RedDemonState::SNOWBALL);
		return;
	}
	if (true == RedDemonSnowLCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT) && true == GameEngineInput::GetInst()->IsPress("ColDamage"))
	{
		// 스노우볼이 왼쪽으로 굴러야함
		Score::ScoreUI_ += 500;
		CurrentDir_ = RedDemonDir::LEFT;
		ChangeState(RedDemonState::SNOWBALL);
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

void RedDemon::SnowBallUpdate()
{
	MoveDir_.y = 0.0f;
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 600);

	RedDemonDir CheckDir_ = CurrentDir_;

	if (CurrentDir_ == RedDemonDir::LEFT)
	{
		MoveDir_.x = -1.f;

	}

	if (CurrentDir_ == RedDemonDir::RIGHT)
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
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (RGB(0, 0, 0) == RightColor)
	{
		Score::ScoreUI_ += 10;
		CurrentDir_ = RedDemonDir::LEFT;
		MoveDir_.x = -1.f;
	}
	if (RGB(255, 0, 0) == RightColor)
	{
		MoveDir_ = float4::ZERO;
		DeathTime_ -= GameEngineTime::GetDeltaTime();
		if (true == DeathCheck_)
		{
			RedDemonAnimationRender_->ChangeAnimation("SnowBallEffect");
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
		CurrentDir_ = RedDemonDir::RIGHT;
		MoveDir_.x = 1.f;
	}
	if (RGB(255, 0, 0) == LeftColor)
	{
		MoveDir_ = float4::ZERO;
		DeathTime_ -= GameEngineTime::GetDeltaTime();
		if (true == DeathCheck_)
		{
			RedDemonAnimationRender_->ChangeAnimation("SnowBallEffect");
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
		if (CurrentDir_ == RedDemonDir::LEFT)
		{
			MoveDir_.x = -1.f;
		}

		if (CurrentDir_ == RedDemonDir::RIGHT)
		{
			MoveDir_.x = 1.f;
		}
	}
}

void RedDemon::ShakingSnowUpdate()
{
	if (true == RedDemonCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		ChangeState(RedDemonState::DEFEATED);
		return;
	}
	ShakingTime_ -= GameEngineTime::GetDeltaTime();
	if (ShakingTime_ <= 0)
	{
		ChangeState(RedDemonState::IDLE);
		return;
	}

	if (true == RedDemonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(RedDemonState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(RedDemonState::SNOW1);
				return;
			}
		}
	}
}

void RedDemon::DefeatedUpdate()
{
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
	if (RGB(0, 0, 0) == Color && RGB(0, 0, 0) == CColor)
	{
		return;
	}
	if (RGB(0, 0, 0) == Color)
	{
		//MoveDir_.y = 0.0f;
		MoveDir_ = float4::ZERO;
		ChangeState(RedDemonState::DEATH);
		return;
	}
	if (RGB(0, 0, 0) == RColor)
	{
		MoveDir_.x = -1.0f;
	}
	if (RGB(0, 0, 0) == LColor)
	{
		MoveDir_.x = 1.0f;
	}
}

void RedDemon::DeathUpdate()
{
	ItemTime_ -= GameEngineTime::GetDeltaTime();
	if (ItemTime_ <= 0)
	{
		RandomItem();
		Death();
	}
}

//===========================Start==========================
void RedDemon::StartDownStart()
{
	AnimationName_ = "Down_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Right";
	}
	RedDemonAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void RedDemon::IdleStart()
{
	StartMoveCount_ -= 1;
	AnimationName_ = "Idle_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Right";
	}
	RedDemonAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void RedDemon::StartMoveStart()
{
	AnimationName_ = "Move_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Right";
	}
	RedDemonAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void RedDemon::MoveStart()
{
	AnimationName_ = "Move_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Right";
	}
	RedDemonAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void RedDemon::JumpStart()
{
	AnimationName_ = "Jump_";
	RedDemonAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
	
	MoveDir_ = float4::UP * 520.0f;
}

void RedDemon::DownStart()
{
	AnimationName_ = "Down_";
	RedDemonAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void RedDemon::AttackStart()
{}

void RedDemon::Snow1Start()
{
	RedDemonCollision_->Off();
	AnimationName_ = "Snow1";
	RedDemonAnimationRender_->ChangeAnimation(AnimationName_);
	RedDemonAnimationRender_->SetPivot({ 0,20.0f });

	RedDemonSnowCollision_->On();

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

void RedDemon::SnowBallStart()
{
	RedDemonSnowCollision_->Off();
	RedDemonSnowRCollision_->Off();
	RedDemonSnowLCollision_->Off();
	AnimationName_ = "SnowballRolling";
	RedDemonAnimationRender_->ChangeAnimation(AnimationName_);
	RedDemonAnimationRender_->SetPivot({ 0,0 });

	RedDemonSnowBallCollision_ = CreateCollision("SnowBallColBox", { 60, 60 });
	RedDemonSnowBallRCollision_ = CreateCollision("SnowBallRColBox", { 5, 10 }, { -15, 0 });
	RedDemonSnowBallLCollision_ = CreateCollision("SnowBallLColBox", { 5, 10 }, { 15, 0 });
}

void RedDemon::ShakingSnowStart()
{
	RedDemonSnowCollision_->Off();
	AnimationName_ = "ShakingSnow";
	RedDemonAnimationRender_->ChangeAnimation(AnimationName_);
	RedDemonAnimationRender_->SetPivot({ 0,0 });

	RedDemonCollision_->On();
	
	DamageCount_ = 2;
	ShakingTime_ = 1.0f;
}

void RedDemon::DefeatedStart()
{
	RedDemonCollision_->Off();
	GameEngineSound::SoundPlayOneShot("SnowBallHitEnemy_Effect(11).mp3", 0);
	AnimationName_ = "Defeated";
	RedDemonAnimationRender_->ChangeAnimation(AnimationName_);

	MoveDir_ = float4::UP * 520.0f;
}

void RedDemon::DeathStart()
{
	RedDemonCollision_->Off();
	AnimationName_ = "Death";
	RedDemonAnimationRender_->ChangeAnimation(AnimationName_);
	RedDemonAnimationRender_->SetPivot({ 0,20 });
}