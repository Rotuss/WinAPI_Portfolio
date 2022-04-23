#include "TitleBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>

TitleBackGround::TitleBackGround()
{
}

TitleBackGround::~TitleBackGround()
{
}

void TitleBackGround::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	TitleAnimationRender_ = CreateRenderer();
	TitleAnimationRender_->CreateAnimation("Title.bmp", "Title", 0, 2, 0.15f, false);
	TitleAnimationRender_->ChangeAnimation("Title");
}

void TitleBackGround::Render()
{
	DebugRectRender();
}
