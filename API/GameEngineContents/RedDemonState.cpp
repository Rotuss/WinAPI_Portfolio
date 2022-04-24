#include "RedDemon.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

void RedDemon::IdleUpdate()
{}

void RedDemon::MoveUpdate()
{}

void RedDemon::JumpUpdate()
{}

void RedDemon::DownUpdate()
{}

void RedDemon::AttackUpdate()
{}

void RedDemon::ShakingSnowUpdate()
{}

void RedDemon::DefeatedUpdate()
{}

void RedDemon::DeathUpdate()
{}

//===========================Start==========================
void RedDemon::IdleStart()
{
	AnimationName_ = "Idle_";
	if ("" == ChangeDirText_)
	{
		ChangeDirText_ = "Right";
	}
	RedDemonAnimationRender_->ChangeAnimation(AnimationName_ + ChangeDirText_);
}

void RedDemon::MoveStart()
{}

void RedDemon::JumpStart()
{}

void RedDemon::DownStart()
{}

void RedDemon::AttackStart()
{}

void RedDemon::ShakingSnowStart()
{}

void RedDemon::DefeatedStart()
{}

void RedDemon::DeathStart()
{}