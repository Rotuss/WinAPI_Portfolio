#include "Nick.h"
#include "SnowBullet.h"
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
		ChangeState(NickState::ATTACK);
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
		ChangeState(NickState::ATTACK);
		return;
	}
	if (false == IsMoveKey())
	{
		ChangeState(NickState::IDLE);
		return;
	}

	float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	float4 CheckPos = NextPos + float4(0.0f, 45.0f);

	int Color = FloorColImage_->GetImagePixel(CheckPos);
	
	if (RGB(0, 0, 0) != Color) 
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	}
	// Down... color¶û °ãÄ§
	//FloorCollisionCheckMoveGround();
}

void Nick::JumpUpdate()
{
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir_ += float4::LEFT;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir_ += float4::RIGHT;
	}
	
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(NickState::ATTACK);
		return;
	}

	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;

	int Color = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 45.0f });
	if (RGB(0, 0, 0) == Color || RGB(0, 255, 0) == Color)
	{
		ChangeState(NickState::IDLE);
		return;
	}
}

void Nick::DownUpdate()
{
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir_ += float4::LEFT;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir_ += float4::RIGHT;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(NickState::ATTACK);
		return;
	}

	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;

	int Color = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0.0f, 45.0f });
	if (RGB(0, 0, 0) == Color || RGB(0, 255, 0) == Color)
	{
		ChangeState(NickState::IDLE);
		return;
	}
}

void Nick::AttackUpdate()
{
	
	/*if (true == NickAnimationRender_->IsEndAnimation())
	{
		ChangeState(NickState::IDLE);
	}
	*/
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
	
	if (false == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		ChangeState(NickState::IDLE);
		return;
	}
}

void Nick::PushUpdate()
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

}

//===========================Start==========================
void Nick::IdleStart()
{
	// ¾Ö´Ï¸ÞÀÌ¼ÇÀÌ ¹Ù²ñ
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
	AnimationName_ = "Attack_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Right";
	}
	NickAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Nick::PushStart()
{
	AnimationName_ = "Push_";
	NickAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void Nick::AppearStart()
{
	AnimationName_ = "Appear";
	NickAnimationRender_->ChangeAnimation(AnimationName_);
}

void Nick::DeathStart()
{
	AnimationName_ = "Death";
	NickAnimationRender_->ChangeAnimation(AnimationName_);
}

void Nick::FloorCollisionCheckMoveGround()
{
	float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime());
	float4 CheckPos = NextPos + float4(0.0f, 45.0f);
	
	int Color = FloorColImage_->GetImagePixel(CheckPos);
	
	if (RGB(0, 0, 0) != Color && RGB(0, 255, 0) != Color)
	{
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
		//SetMove(float4::DOWN * Gravity_ * GameEngineTime::GetDeltaTime());
	}
}