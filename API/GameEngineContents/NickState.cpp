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

	if (true == GameEngineInput::GetInst()->IsDown("SnowBullet"))
	{
		ChangeState(NickState::ATTACK);
		return;
	}
}

void Nick::AttackUpdate()
{
}

//===========================Start==========================
void Nick::IdleStart()
{
	// 애니메이션이 바뀜
	// AnimationName_ = "Idle_";
}

void Nick::MoveStart()
{
}

void Nick::AttackStart()
{
}