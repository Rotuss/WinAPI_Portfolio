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
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir_ = float4::UP;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir_ = float4::DOWN;
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
	SetMove(MoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	FloorCollisionCheckMoveGround();
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

	int Color = FloorColImage_->GetImagePixel(GetPosition() + float4{ 0,45 });
	if (RGB(0, 0, 0) == Color || RGB(0, 255, 0) == Color)
	{
		Gravity_ = 10.0f;
		MoveDir_.Normal2D();

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
	}
	if (CurrentDir_ == NickDir::RIGHT)
	{
		Ptr->SetDir(float4::RIGHT);
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

}

void Nick::DeathUpdate()
{

}

//===========================Start==========================
void Nick::IdleStart()
{
	// 애니메이션이 바뀜
	AnimationName_ = "Idle_";
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

}

void Nick::DeathStart()
{

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