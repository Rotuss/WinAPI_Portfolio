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
	if (true == GameEngineInput::GetInst()->IsDown("SnowBullet"))
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
		MoveDir_ += float4::LEFT;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir_ += float4::RIGHT;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir_ += float4::UP;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir_ += float4::DOWN;
	}
	if (0.3f <= MoveDir_.Len2D())
	{
		MoveDir_.Range2D(0.3f);
	}
	//MoveDir_ *= 0.9f;

	if (true == GameEngineInput::GetInst()->IsDown("Jump"))
	{
		ChangeState(NickState::JUMP);
		return;
	}
	if (true == GameEngineInput::GetInst()->IsDown("SnowBullet"))
	{
		ChangeState(NickState::ATTACK);
		return;
	}
	if (false == IsMoveKey())
	{
		MoveDir_ += -MoveDir_ * GameEngineTime::GetDeltaTime();
		if (0.005f >= MoveDir_.Len2D())
		{
			MoveDir_ = float4::ZERO;
			return;
		}
		SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
		return;
	}
	
	float4 CheckPos_;
	{
		float4 NextPos = GetPosition() + (MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPos = NextPos + float4(0.0f, 45.0f);

		int Color = FloorColImage_->GetImagePixel(CheckPos);

		if (RGB(0, 0, 0) != Color)
		{
			SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
		}
	}
	//SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
}

void Nick::JumpUpdate()
{
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir_ += float4::LEFT * GameEngineTime::GetDeltaTime() * AccSpeed_;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir_ += float4::RIGHT * GameEngineTime::GetDeltaTime() * AccSpeed_;
	}

	MoveDir_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 1000.0f;
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
		if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
		{
			MoveDir_ += float4::LEFT;
		}
		Ptr->SetDir(float4::LEFT);
	}
	if (CurrentDir_ == NickDir::RIGHT)
	{
		if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
		{
			MoveDir_ += float4::RIGHT;
		}
		Ptr->SetDir(float4::RIGHT);
	}
	
	if (false == GameEngineInput::GetInst()->IsDown("SnowBullet"))
	{
		ChangeState(NickState::MOVE);
		return;
	}
}

//===========================Start==========================
void Nick::IdleStart()
{
	// 애니메이션이 바뀜
	// AnimationName_ = "Idle_";
	if (CurrentDir_ == NickDir::LEFT)
	{
		AnimationName_ = "Nick_Idle_Left";
		NickAnimationRender_->ChangeAnimation(AnimationName_);
	}
	else if (CurrentDir_ == NickDir::RIGHT)
	{
		AnimationName_ = "Nick_Idle_Right";
		NickAnimationRender_->ChangeAnimation(AnimationName_);
	}
}

void Nick::MoveStart()
{
}

void Nick::JumpStart()
{
	MoveDir_ = float4::UP * 500.0f;
}

void Nick::AttackStart()
{
}