#include "YellowTroll.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

YellowTroll::YellowTroll()
{
}

YellowTroll::~YellowTroll()
{
}

void YellowTroll::Start()
{
	YellowTrollCollision_ = CreateCollision("YellowTrollHitBox", { 96, 108 });

	// 애니메이션
	YellowTrollAnimationRender_ = CreateRenderer();

	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Idle_Right.bmp", "Idle_Right", 0, 0, 0.0f, false);
	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Idle_Left.bmp", "Idle_Left", 0, 0, 0.0f, false);

	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Move_Right.bmp", "Move_Right", 0, 1, 0.12f, true);
	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Move_Left.bmp", "Move_Left", 0, 1, 0.12f, true);

	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Jump_Right.bmp", "Jump_Right", 0, 1, 0.1f, false);
	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Jump_Left.bmp", "Jump_Left", 0, 1, 0.1f, false);

	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Down_Right.bmp", "Down_Right", 0, 0, 0.0f, false);
	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Down_Left.bmp", "Down_Left", 0, 0, 0.0f, false);

	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_ShakingSnow.bmp", "ShakingSnow", 0, 1, 0.1f, true);

	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Defeated.bmp", "Defeated", 0, 3, 0.1f, true);

	YellowTrollAnimationRender_->CreateAnimation("YellowTroll_Death.bmp", "Death", 0, 0, 0.0f, false);

	YellowTrollAnimationRender_->ChangeAnimation("Idle_Right");
	YellowTrollAnimationRender_->SetPivotType(RenderPivot::CENTER);

	//AnimationName_ = "Idle_";
	CurrentDir_ = YellowTrollDir::RIGHT;
	CurrentState_ = YellowTrollState::IDLE;
}

void YellowTroll::Render()
{
	//DebugRectRender();
}
