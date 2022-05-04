#include "Nick.h"
#include "SnowBullet.h"
#include "Life.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void Nick::IdleUpdate()
{
	if (true == IsMoveKey())
	{
		ChangeState(NickState::MOVE);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Jump"))
	{
		ChangeState(NickState::JUMP);
		return;
	}
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		PrevState_ = NickState::IDLE;
		ChangeState(NickState::ATTACK);
		return;
	}

	if (true == PlayerCollision_->CollisionCheck("EnemyHitBox", CollisionType::RECT, CollisionType::RECT) 
		|| true == PlayerCollision_->CollisionCheck("FireHitBox", CollisionType::RECT, CollisionType::RECT)
		|| true == PlayerCollision_->CollisionCheck("BossHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		ChangeState(NickState::DEATH);
		return;
	}
	
	//float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	float4 CheckPos = GetPosition() + float4(0.0f, 44.0f);

	int DColor = FloorColImage_->GetImagePixel(CheckPos + float4(0.0f, 1.0f));
	
	if (RGB(0, 0, 0) != DColor && CurrentState_ != NickState::JUMP)
	{
		ChangeState(NickState::DOWN);
		return;
	}
}

void Nick::MoveUpdate()
{
	float4 MoveDir_ = float4::ZERO;
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		// -1.0f * DT
		MoveDir_ = float4::LEFT;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir_ = float4::RIGHT;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Jump"))
	{
		ChangeState(NickState::JUMP);
		return;
	}
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		PrevState_ = NickState::MOVE;
		ChangeState(NickState::ATTACK);
		return;
	}
	if (false == IsMoveKey())
	{
		ChangeState(NickState::IDLE);
		return;
	}

	if (true == PlayerCollision_->CollisionCheck("EnemyHitBox", CollisionType::RECT, CollisionType::RECT)
		|| true == PlayerCollision_->CollisionCheck("FireHitBox", CollisionType::RECT, CollisionType::RECT)
		|| true == PlayerCollision_->CollisionCheck("BossHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		ChangeState(NickState::DEATH);
		return;
	}
	
	// 원하는대로 작동이 안됨
	float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	float4 CheckBotPos = NextPos + float4(0.0f, 44.0f);
	float4 CheckTopPos = NextPos + float4(0.0f, -45.0f);
	float4 CheckRightPos = NextPos + float4(15.0f, 0.0f);
	float4 CheckLeftPos = NextPos + float4(-15.0f, 0.0f);

	int BotColor = FloorColImage_->GetImagePixel(CheckBotPos);
	//int TopColor = FloorColImage_->GetImagePixel(CheckTopPos);
	int RightColor = FloorColImage_->GetImagePixel(CheckRightPos);
	int LeftColor = FloorColImage_->GetImagePixel(CheckLeftPos);
	int DColor = FloorColImage_->GetImagePixel(CheckBotPos + float4(0.0f, 1.0f));

	if (RGB(0, 0, 0) != BotColor && CurrentState_ != NickState::JUMP)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (RGB(0, 0, 0) == RightColor || RGB(0, 0, 0) == LeftColor)
	{
		MoveDir_ = float4::ZERO;
	}
	if (RGB(255, 255, 255) == DColor)
	{
		ChangeState(NickState::DOWN);
		return;
	}

	std::vector<GameEngineCollision*> HitResult;

	if (true == PlayerCollision_->CollisionResult("SnowRColBox", HitResult, CollisionType::RECT, CollisionType::RECT))
	{
		PushTargetCollision_ = HitResult[0];
		ChangeState(NickState::PUSH);
		return;
	}
	HitResult.clear();

	if (true == PlayerCollision_->CollisionResult("SnowLColBox", HitResult, CollisionType::RECT, CollisionType::RECT))
	{
		PushTargetCollision_ = HitResult[0];
		ChangeState(NickState::PUSH);
		return;
	}
	HitResult.clear();
	//FloorCollisionCheckMoveGround();
}

void Nick::JumpUpdate()
{
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir_ = float4{ -Speed_,MoveDir_.y };
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir_ = float4{ Speed_,MoveDir_.y };
	}
	
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		PrevState_ = NickState::JUMP;
		ChangeState(NickState::ATTACK);
		return;
	}

	if (true == PlayerCollision_->CollisionCheck("EnemyHitBox", CollisionType::RECT, CollisionType::RECT)
		|| true == PlayerCollision_->CollisionCheck("FireHitBox", CollisionType::RECT, CollisionType::RECT)
		|| true == PlayerCollision_->CollisionCheck("BossHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		ChangeState(NickState::DEATH);
		return;
	}
	
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;
	
	if(MoveDir_.y < 0)
	{
		return;
	}

	int Color = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 45.0f });
	int CColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 35.0f });
	int RColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ 15.0f, 0.0f });
	int LColor = FloorColImage_->GetImagePixel(GetPosition() + float4{ -15.0f, 0.0f });
	if (RGB(0, 0, 0) == Color && RGB(255, 255, 255) == CColor)
	{
		MoveDir_ = float4::ZERO;
		ChangeState(NickState::IDLE);
		return;
	}
	if (RGB(0, 0, 0) == RColor || RGB(0, 0, 0) == LColor)
	{
		MoveDir_.x = 0.0f;
		return;
	}
}

void Nick::DownUpdate()
{
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir_ = float4{ -Speed_,MoveDir_.y };
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir_ = float4{ Speed_,MoveDir_.y };
	}

	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		PrevState_ = NickState::DOWN;
		ChangeState(NickState::ATTACK);
		return;
	}

	if (true == PlayerCollision_->CollisionCheck("EnemyHitBox", CollisionType::RECT, CollisionType::RECT)
		|| true == PlayerCollision_->CollisionCheck("FireHitBox", CollisionType::RECT, CollisionType::RECT)
		|| true == PlayerCollision_->CollisionCheck("BossHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		ChangeState(NickState::DEATH);
		return;
	}
	
	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;
	
	if (MoveDir_.y < 0)
	{
		return;
	}

	int Color = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 45.0f });
	if (RGB(0, 0, 0) == Color)
	{
		MoveDir_ = float4::ZERO;
		ChangeState(NickState::IDLE);
		return;
	}
}

void Nick::AttackUpdate()
{
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	//MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;

	if (PrevState_ == NickState::IDLE)
	{
		float4 CheckPos = GetPosition() + float4(0.0f, 44.0f);

		int DColor = FloorColImage_->GetImagePixel(CheckPos + float4(0.0f, 1.0f));

		if (RGB(0, 0, 0) != DColor && CurrentState_ != NickState::JUMP)
		{
			ChangeState(NickState::DOWN);
			return;
		}
	}
	if (PrevState_ == NickState::MOVE)
	{
		if (false == IsMoveKey())
		{
			ChangeState(NickState::IDLE);
			return;
		}
		if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
		{
			// -1.0f * DT
			MoveDir_ = float4::LEFT;
		}
		if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
		{
			MoveDir_ = float4::RIGHT;
		}
		
		// 원하는대로 작동이 안됨
		float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckBotPos = NextPos + float4(0.0f, 44.0f);
		float4 CheckTopPos = NextPos + float4(0.0f, -45.0f);
		float4 CheckRightPos = NextPos + float4(15.0f, 0.0f);
		float4 CheckLeftPos = NextPos + float4(-15.0f, 0.0f);

		int BotColor = FloorColImage_->GetImagePixel(CheckBotPos);
		//int TopColor = FloorColImage_->GetImagePixel(CheckTopPos);
		int RightColor = FloorColImage_->GetImagePixel(CheckRightPos);
		int LeftColor = FloorColImage_->GetImagePixel(CheckLeftPos);
		int DColor = FloorColImage_->GetImagePixel(CheckBotPos + float4(0.0f, 1.0f));

		if (RGB(0, 0, 0) != BotColor && CurrentState_ != NickState::JUMP)
		{
			SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
		}
		if (RGB(0, 0, 0) == RightColor || RGB(0, 0, 0) == LeftColor)
		{
			MoveDir_ = float4::ZERO;
		}
		if (RGB(255, 255, 255) == DColor)
		{
			ChangeState(NickState::DOWN);
			return;
		}
	}
	if (PrevState_ == NickState::JUMP)
	{
		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;

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
			MoveDir_ = float4::ZERO;
			ChangeState(NickState::IDLE);
			return;
		}
		if (RGB(0, 0, 0) == RColor || RGB(0, 0, 0) == LColor)
		{
			MoveDir_.x = 0.0f;
			return;
		}
	}
	if (PrevState_ == NickState::DOWN)
	{
		MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;

		if (MoveDir_.y < 0)
		{
			return;
		}

		int Color = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 45.0f });
		if (RGB(0, 0, 0) == Color)
		{
			MoveDir_ = float4::ZERO;
			ChangeState(NickState::IDLE);
			return;
		}
	}

	if (true == NickAnimationRender_->IsEndAnimation())
	{
		ChangeState(NickState::IDLE);
		return;
	}
}

void Nick::PushUpdate()
{
	if (nullptr == PushTargetCollision_)
	{
		ChangeState(NickState::IDLE);
		return;
	}
	
	float4 MoveDir_ = float4::ZERO;
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		// -1.0f * DT
		MoveDir_ = float4::LEFT;
		if (false == PlayerCollision_->NextPosCollisionCheck("SnowLColBox", MoveDir_ * GameEngineTime::GetDeltaTime() * PushSpeed_, CollisionType::RECT, CollisionType::RECT))
		{
			PushTargetCollision_ = nullptr;
			ChangeState(NickState::MOVE);
			return;
		}
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir_ = float4::RIGHT;
		if (false == PlayerCollision_->NextPosCollisionCheck("SnowRColBox", MoveDir_ * GameEngineTime::GetDeltaTime() * PushSpeed_, CollisionType::RECT, CollisionType::RECT))
		{
			PushTargetCollision_ = nullptr;
			ChangeState(NickState::MOVE);
			return;
		}
	}

	if (false == IsMoveKey())
	{
		ChangeState(NickState::IDLE);
		return;
	}

	if (true == PlayerCollision_->CollisionCheck("EnemyHitBox", CollisionType::RECT, CollisionType::RECT)
		|| true == PlayerCollision_->CollisionCheck("FireHitBox", CollisionType::RECT, CollisionType::RECT)
		|| true == PlayerCollision_->CollisionCheck("BossHitBox", CollisionType::RECT, CollisionType::RECT))
	{
		ChangeState(NickState::DEATH);
		return;
	}
	
	float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * PushSpeed_);
	float4 CheckPos = NextPos + float4(0.0f, 44.0f);

	int Color = FloorColImage_->GetImagePixel(CheckPos);
	int DColor = FloorColImage_->GetImagePixel(CheckPos + float4(0.0f, 1.0f));
	if (RGB(0, 0, 0) != Color && CurrentState_ != NickState::JUMP)
	{
		PushTargetCollision_->GetActor()->SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * PushSpeed_);
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * PushSpeed_);
	}
	if (RGB(255, 255, 255) == DColor)
	{
		ChangeState(NickState::DOWN);
		return;
	}
}

void Nick::AppearUpdate()
{
	AppTime_ -= GameEngineTime::GetDeltaTime();
	if (0.0f >= AppTime_)
	{
		if (true == IsMoveKey())
		{
			return;
		}
		ChangeState(NickState::IDLE);
		AppTime_ = 1.0f;
	}
}

void Nick::DeathUpdate()
{
	DTime_ -= GameEngineTime::GetDeltaTime();
	if (0.0f >= DTime_)
	{
		if (true == IsMoveKey())
		{
			return;
		}
		ChangeState(NickState::APPEAR);
		DTime_ = 0.5f;
	}

	if (Life::LifeUI_ < 0)
	{
		GameEngine::GetInst().ChangeLevel("GameOver");
	}
}

void Nick::NextFloorUpdate()
{
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
}

//===========================Start==========================
void Nick::IdleStart()
{
	// 애니메이션이 바뀜
	AnimationName_ = "Idle_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Right";
	}
	NickAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Nick::MoveStart()
{
	AnimationName_ = "Move_";
	NickAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Nick::JumpStart()
{
	GameEngineSound::SoundPlayOneShot("Jump_Effect(18).mp3", 0);
	AnimationName_ = "Jump_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Right";
	}
	NickAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
	MoveDir_ = float4::UP * 520.0f;
}

void Nick::DownStart()
{
	AnimationName_ = "Down_";
	NickAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Nick::AttackStart()
{
	GameEngineSound::SoundPlayOneShot("SnowBullet_Effect(22).mp3", 0);
	AnimationName_ = "Attack_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Right";
	}
	NickAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
	
	SnowBullet* Ptr = GetLevel()->CreateActor<SnowBullet>();
	Ptr->SetPosition(GetPosition());

	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	if (CurrentDir_ == NickDir::LEFT)
	{
		Ptr->SetDir(float4::LEFT);
		Ptr->SetBDir("Left");
	}
	if (CurrentDir_ == NickDir::RIGHT)
	{
		Ptr->SetDir(float4::RIGHT);
		Ptr->SetBDir("Right");
	}
}

void Nick::PushStart()
{
	AnimationName_ = "Push_";
	NickAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Nick::AppearStart()
{
	GameEngineSound::SoundPlayOneShot("Appear_effect(9).mp3", 0);
	AnimationName_ = "Appear";
	NickAnimationRender_->ChangeAnimation(AnimationName_);

	MainPlayer->SetPosition({ 400,710 });
}

void Nick::DeathStart()
{
	GameEngineSound::SoundPlayOneShot("Death_Effect(7).mp3", 0);
	AnimationName_ = "Death";
	NickAnimationRender_->ChangeAnimation(AnimationName_);

	LifeCount_ -= 1;
	Life::LifeUI_ -= 1;
}

void Nick::NextFloorStart()
{
	GameEngineSound::SoundPlayOneShot("FloorChange_Effect(19).mp3", 0);
	AnimationName_ = "Down_";
	NickAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);

	MoveDir_ = float4::UP * 600.0f;
}
/*
void Nick::FloorCollisionCheckMoveGround()
{
	float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	float4 CheckBotPos = NextPos + float4(0.0f, 44.0f);
	float4 CheckTopPos = NextPos + float4(0.0f, -45.0f);
	float4 CheckRightPos = NextPos + float4(-15.0f, 0.0f);
	float4 CheckLeftPos = NextPos + float4(15.0f, 0.0f);
	
	int BotColor = FloorColImage_->GetImagePixel(CheckBotPos);
	int TopColor = FloorColImage_->GetImagePixel(CheckTopPos);
	int RightColor = FloorColImage_->GetImagePixel(CheckRightPos);
	int LeftColor = FloorColImage_->GetImagePixel(CheckLeftPos);
	int DColor = FloorColImage_->GetImagePixel(CheckBotPos + float4{0.0f, 1.0f});
	
	if (RGB(0, 0, 0) != BotColor && RGB(0, 255, 0) != BotColor)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
		//SetMove(float4::DOWN * Gravity_ * GameEngineTime::GetDeltaTime());
	}
	if(RGB(0, 0, 0) == BotColor)
	{
		int a = 0;
	}
}
*/