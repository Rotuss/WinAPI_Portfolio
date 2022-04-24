#include "Frog.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

Frog::Frog()
{
}

Frog::~Frog()
{
}

void Frog::Start()
{
	FrogCollision_ = CreateCollision("FrogHitBox", { 96, 104 });

	// 애니메이션
	FrogAnimationRender_ = CreateRenderer();

	FrogAnimationRender_->CreateAnimation("Frog_Idle_Right.bmp", "Idle_Right", 0, 0, 0.0f, false);
	FrogAnimationRender_->CreateAnimation("Frog_Idle_Left.bmp", "Idle_Left", 0, 0, 0.0f, false);

	FrogAnimationRender_->CreateAnimation("Frog_Move_Right.bmp", "Move_Right", 0, 1, 0.12f, true);
	FrogAnimationRender_->CreateAnimation("Frog_Move_Left.bmp", "Move_Left", 0, 1, 0.12f, true);

	FrogAnimationRender_->CreateAnimation("Frog_Jump_Right.bmp", "Jump_Right", 0, 0, 0.0f, false);
	FrogAnimationRender_->CreateAnimation("Frog_Jump_Left.bmp", "Jump_Left", 0, 0, 0.0f, false);

	//EnemyAnimationRender_->CreateAnimation("Frog_Jump_Right.bmp", "Down_Right", 0, 0, 0.0f, false);
	//EnemyAnimationRender_->CreateAnimation("Frog_Jump_Left.bmp", "Down_Left", 0, 0, 0.0f, false);

	FrogAnimationRender_->CreateAnimation("Frog_ThrowingFire_Right.bmp", "Attack_Right", 0, 0, 0.0f, false);
	FrogAnimationRender_->CreateAnimation("Frog_ThrowingFire_Left.bmp", "Attack_Left", 0, 0, 0.0f, false);

	FrogAnimationRender_->CreateAnimation("Frog_ShakingSnow.bmp", "ShakingSnow", 0, 1, 0.1f, true);

	FrogAnimationRender_->CreateAnimation("Frog_Defeated.bmp", "Defeated", 0, 3, 0.1f, true);

	FrogAnimationRender_->CreateAnimation("Frog_Death.bmp", "Death", 0, 0, 0.0f, false);

	FrogAnimationRender_->ChangeAnimation("Idle_Right");
	FrogAnimationRender_->SetPivotType(RenderPivot::CENTER);

	//AnimationName_ = "Idle_";
	CurrentDir_ = FrogDir::RIGHT;
	CurrentState_ = FrogState::IDLE;
}

void Frog::Render()
{
	//DebugRectRender();
}
