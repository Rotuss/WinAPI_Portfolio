#include "Son.h"
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

void Son::StartUpdate()
{
	float4 StartDir = float4::ZERO;
	StartDir += float4::LEFT * GameEngineTime::GetDeltaTime() * StartSpeed_;
	Time -= GameEngineTime::GetDeltaTime();

	if (Time <= 0.1f)
	{
		StartDir = float4::DOWN * 300.0f * GameEngineTime::GetDeltaTime();

		int Color = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 45.0f });
		int CColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 35.0f });
		if (RGB(0, 0, 0) == Color && RGB(255, 255, 255) == CColor)
		{
			MoveDir_ = float4::ZERO;
			ChangeState(SonState::LANDING);
			return;
		}
	}
	else if (0.42f >= Time)
	{
		StartDir += float4::DOWN * 300.0f * GameEngineTime::GetDeltaTime();

		int Color = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 45.0f });
		int CColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 35.0f });
		if (RGB(0, 0, 0) == Color && RGB(255,255,255) == CColor)
		{
			MoveDir_ = float4::ZERO;
			ChangeState(SonState::LANDING);
			return;
		}
	}
	
	SetMove(StartDir);

	if (true == SonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(SonState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(SonState::SNOW1);
				return;
			}
		}
	}
}

void Son::MoveUpdate()
{
	if (true == SonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(SonState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(SonState::SNOW1);
				return;
			}
		}
	}
	if (true == SonCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		ChangeState(SonState::DEATH);
		return;
	}

	if (true == SonCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		ChangeState(SonState::DEATH);
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

	if (RGB(0, 0, 0) != BotColor)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (RGB(0, 0, 0) == RightColor)
	{
		CurrentDir_ = SonDir::LEFT;
		ChangeDirText_ = "Left";
		SonAnimationRender_->ChangeAnimation("Move_" + ChangeDirText_);
		MoveDir_.x = -1.f;
	}
	if (RGB(255, 0, 0) == RightColor)
	{
		Death();
	}
	if (RGB(0, 0, 0) == LeftColor)
	{
		CurrentDir_ = SonDir::RIGHT;
		ChangeDirText_ = "Right";
		SonAnimationRender_->ChangeAnimation("Move_" + ChangeDirText_);
		MoveDir_.x = 1.f;
	}
	if (RGB(255, 0, 0) == LeftColor)
	{
		Death();
	}
	if (RGB(255, 255, 255) == DColor)
	{
		if (CurrentDir_ == SonDir::LEFT)
		{
			ChangeDirText_ = "Left";
			ChangeState(SonState::DOWN);
			return;
		}

		if (CurrentDir_ == SonDir::RIGHT)
		{
			ChangeDirText_ = "Right";
			ChangeState(SonState::DOWN);
			return;
		}
	}

	SonDir CheckDir_ = CurrentDir_;

	if (CurrentDir_ == SonDir::LEFT)
	{
		MoveDir_.x = -1.f;
	}

	if (CurrentDir_ == SonDir::RIGHT)
	{
		MoveDir_.x = 1.f;
	}
}

void Son::DownUpdate()
{
	if (true == SonCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(SonState::SNOW1);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(SonState::SNOW1);
				return;
			}
		}
	}
	if (true == SonCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		ChangeState(SonState::DEATH);
		return;
	}

	if (true == SonCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		ChangeState(SonState::DEATH);
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
		ChangeState(SonState::LANDING);
		return;
	}
}

void Son::LandingUpdate()
{
	LandingTime_ -= GameEngineTime::GetDeltaTime();
	if (LandingTime_ <= 0)
	{
		if (CurrentDir_ == SonDir::LEFT && true == StartLandingCheck_)
		{
			CurrentDir_ = SonDir::RIGHT;
			ChangeDirText_ = "Right";
		}
		else if (CurrentDir_ == SonDir::RIGHT && true == StartLandingCheck_)
		{
			CurrentDir_ = SonDir::LEFT;
			ChangeDirText_ = "Left";
		}
		StartLandingCheck_ = true;
		ChangeState(SonState::MOVE);
		return;
	}
}

void Son::Snow1Update()
{
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;

	if (true == SonSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(SonState::SNOW2);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(SonState::SNOW2);
				return;
			}
		}
	}
	if (false == SonSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		MeltingTime_ -= GameEngineTime::GetDeltaTime();
		if (MeltingTime_ < 0)
		{
			DamageCount_ = 2;
			SonSnowCollision_->Off();
			SonCollision_->On();
			ChangeState(SonState::MOVE);
			return;
		}
	}
	if (true == SonSnowCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		ChangeState(SonState::DEATH);
		return;
	}

	if (true == SonCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		ChangeState(SonState::DEATH);
		return;
	}
	
	int Color = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 45.0f });
	int CColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 35.0f });
	if (RGB(0, 0, 0) == Color && RGB(255, 255, 255) == CColor)
	{
		MoveDir_ = float4::ZERO;
	}
}

void Son::Snow2Update()
{
	if (true == SonSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 10;
		if (false == BluePotion::BPCheck_)
		{
			DamageCount_ -= 1;
			if (DamageCount_ <= 0)
			{
				ChangeState(SonState::SNOW3);
				return;
			}
		}
		else if (true == BluePotion::BPCheck_)
		{
			DamageCount_ -= 2;
			if (DamageCount_ <= 0)
			{
				ChangeState(SonState::SNOW3);
				return;
			}
		}
	}
	if (false == SonSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		MeltingTime_ -= GameEngineTime::GetDeltaTime();
		if (MeltingTime_ < 0)
		{
			ChangeState(SonState::SNOW1);
			return;
		}
	}
	if (true == SonSnowCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 1000;
		ChangeState(SonState::DEATH);
		return;
	}

	if (true == SonCollision_->CollisionCheck("BlueSnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		Score::ScoreUI_ += 8000;
		ChangeState(SonState::DEATH);
		return;
	}
}

void Son::Snow3Update()
{
	// MeltingTime_ 시간 동안 한 번이라도 부딪히면 Snow3, 한 번도 안 부딪히면 Snow2
	MeltingTime_ -= GameEngineTime::GetDeltaTime();
	if (MeltingTime_ > 0.0f)
	{
		if (true == SonSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
		{
			MeltingTime_ = 5.0f;
			return;
		}
	}
	else if (MeltingTime_ <= 0.0f)
	{
		if (false == SonSnowCollision_->CollisionCheck("BulletHitBox", CollisionType::RECT, CollisionType::RECT))
		{
			ChangeState(SonState::SNOW2);
			SonSnowRCollision_->Death();
			SonSnowLCollision_->Death();
			return;
		}
	}

	if (true == SonRCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		// 스노우볼이 오른쪽으로 굴러야함
		Score::ScoreUI_ += 1000;
		CurrentDir_ = SonDir::RIGHT;
		ChangeState(SonState::BLUESNOWBALL);
		return;
	}
	if (true == SonLCollision_->CollisionCheck("SnowBallColBox", CollisionType::RECT, CollisionType::RECT))
	{
		// 스노우볼이 왼쪽으로 굴러야함
		Score::ScoreUI_ += 1000;
		CurrentDir_ = SonDir::LEFT;
		ChangeState(SonState::BLUESNOWBALL);
		return;
	}
	
	if (true == SonSnowRCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT) && true == GameEngineInput::GetInst()->IsPress("ColDamage"))
	{
		// 스노우볼이 오른쪽으로 굴러야함
		Score::ScoreUI_ += 500;
		CurrentDir_ = SonDir::RIGHT;
		ChangeState(SonState::SNOWBALL);
		return;
	}
	if (true == SonSnowLCollision_->CollisionCheck("PlayerHitBox", CollisionType::RECT, CollisionType::RECT) && true == GameEngineInput::GetInst()->IsPress("ColDamage"))
	{
		// 스노우볼이 왼쪽으로 굴러야함
		Score::ScoreUI_ += 500;
		CurrentDir_ = SonDir::LEFT;
		ChangeState(SonState::SNOWBALL);
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

void Son::SnowBallUpdate()
{
	MoveDir_.y = 0.0f;
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 600);

	SonDir CheckDir_ = CurrentDir_;

	if (CurrentDir_ == SonDir::LEFT)
	{
		MoveDir_.x = -1.f;

	}

	if (CurrentDir_ == SonDir::RIGHT)
	{
		MoveDir_.x = 1.f;
	}

	if (true == SonSnowBallCollision_->CollisionCheck("BossHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		GameEngineSound::SoundPlayOneShot("SnowBallDeath_Effect(5).mp3", 0);
		Death();
	}
	if (true == SonSnowBallCollision_->CollisionCheck("BossHeadHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		GameEngineSound::SoundPlayOneShot("SnowBallDeath_Effect(5).mp3", 0);
		Death();
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
		CurrentDir_ = SonDir::LEFT;
		MoveDir_.x = -1.f;
	}
	if (RGB(255, 0, 0) == RightColor)
	{
		MoveDir_ = float4::ZERO;
		DeathTime_ -= GameEngineTime::GetDeltaTime();
		if (true == DeathCheck_)
		{
			SonAnimationRender_->ChangeAnimation("SnowBallEffect");
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
		CurrentDir_ = SonDir::RIGHT;
		MoveDir_.x = 1.f;
	}
	if (RGB(255, 0, 0) == LeftColor)
	{
		MoveDir_ = float4::ZERO;
		DeathTime_ -= GameEngineTime::GetDeltaTime();
		if (true == DeathCheck_)
		{
			SonAnimationRender_->ChangeAnimation("SnowBallEffect");
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
		if (CurrentDir_ == SonDir::LEFT)
		{
			MoveDir_.x = -1.f;
		}

		if (CurrentDir_ == SonDir::RIGHT)
		{
			MoveDir_.x = 1.f;
		}
	}
}

void Son::BlueSnowBallUpdate()
{
	MoveDir_.y = 0.0f;
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * 600);

	SonDir CheckDir_ = CurrentDir_;

	if (CurrentDir_ == SonDir::LEFT)
	{
		MoveDir_.x = -1.f;

	}

	if (CurrentDir_ == SonDir::RIGHT)
	{
		MoveDir_.x = 1.f;
	}

	if (true == SonBlueSnowBallCollision_->CollisionCheck("BossHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		GameEngineSound::SoundPlayOneShot("SnowBallDeath_Effect(5).mp3", 0);
		Death();
	}
	if (true == SonBlueSnowBallCollision_->CollisionCheck("BossHeadHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		GameEngineSound::SoundPlayOneShot("SnowBallDeath_Effect(5).mp3", 0);
		Death();
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
		CurrentDir_ = SonDir::LEFT;
		MoveDir_.x = -1.f;
	}
	if (RGB(255, 0, 0) == RightColor)
	{
		MoveDir_ = float4::ZERO;
		DeathTime_ -= GameEngineTime::GetDeltaTime();
		if (true == DeathCheck_)
		{
			SonAnimationRender_->ChangeAnimation("SnowBallEffect");
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
		CurrentDir_ = SonDir::RIGHT;
		MoveDir_.x = 1.f;
	}
	if (RGB(255, 0, 0) == LeftColor)
	{
		MoveDir_ = float4::ZERO;
		DeathTime_ -= GameEngineTime::GetDeltaTime();
		if (true == DeathCheck_)
		{
			SonAnimationRender_->ChangeAnimation("SnowBallEffect");
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
		if (CurrentDir_ == SonDir::LEFT)
		{
			MoveDir_.x = -1.f;
		}

		if (CurrentDir_ == SonDir::RIGHT)
		{
			MoveDir_.x = 1.f;
		}
	}
}

void Son::DeathUpdate()
{
	RandomItem();
	Death();
}

//===========================Start==========================
void Son::StartStart()
{}

void Son::MoveStart()
{
	SonSnowCollision_->Off();
	AnimationName_ = "Move_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Left";
	}
	SonAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
	SonAnimationRender_->SetPivot({ 0,0 });

	MoveDir_ = float4::ZERO;
}

void Son::DownStart()
{
	AnimationName_ = "Down_";
	SonAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Son::LandingStart()
{
	AnimationName_ = "Landing_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Left";
	}
	SonAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
	SonAnimationRender_->SetPivot({ 0,20.0f });

	LandingTime_ = 0.1f;
}

void Son::Snow1Start()
{
	SonCollision_->Off();
	AnimationName_ = "Snow1";
	SonAnimationRender_->ChangeAnimation(AnimationName_);
	SonAnimationRender_->SetPivot({ 0,20.0f });

	SonSnowCollision_->On();

	DamageCount_ = 2;
	MeltingTime_ = 3.0f;
}

void Son::Snow2Start()
{
	AnimationName_ = "Snow2";
	SonAnimationRender_->ChangeAnimation(AnimationName_);
	SonAnimationRender_->SetPivot({ 0,20.0f });

	DamageCount_ = 2;
	MeltingTime_ = 3.0f;
}

void Son::Snow3Start()
{
	AnimationName_ = "Snow3";
	SonAnimationRender_->ChangeAnimation(AnimationName_);
	SonAnimationRender_->SetPivot({ 0,5 });

	SonSnowRCollision_ = CreateCollision("SnowRColBox", { 5, 10 }, { -15, 0 });
	SonSnowLCollision_ = CreateCollision("SnowLColBox", { 5, 10 }, { 15, 0 });

	MeltingTime_ = 5.0f;
}

void Son::SnowBallStart()
{
	SonSnowCollision_->Off();
	SonSnowRCollision_->Off();
	SonSnowLCollision_->Off();
	AnimationName_ = "SnowballRolling";
	SonAnimationRender_->ChangeAnimation(AnimationName_);
	SonAnimationRender_->SetPivot({ 0,0 });

	SonSnowBallCollision_ = CreateCollision("SnowBallColBox", { 60, 60 });
	SonSnowBallRCollision_ = CreateCollision("SnowBallRColBox", { 5, 10 }, { -15, 0 });
	SonSnowBallLCollision_ = CreateCollision("SnowBallLColBox", { 5, 10 }, { 15, 0 });
}

void Son::BlueSnowBallStart()
{
	SonSnowCollision_->Off();
	SonSnowRCollision_->Off();
	SonSnowLCollision_->Off();
	AnimationName_ = "BlueSnowBall";
	SonAnimationRender_->ChangeAnimation(AnimationName_);
	SonAnimationRender_->SetPivot({ 0,0 });

	SonBlueSnowBallCollision_ = CreateCollision("BlueSnowBallColBox", { 60, 60 });
}

void Son::DeathStart()
{
	SonCollision_->Off();
	SonRCollision_->Off();
	SonLCollision_->Off();
}