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

void TitleBackGround::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		SetPosition(GameEngineWindow::GetScale().Half());
		CreateRenderer("SelectTitle.bmp");
	}
}

void TitleBackGround::Render()
{
	DebugRectRender();
}
