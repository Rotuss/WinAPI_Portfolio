#include "TitleBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>

TitleBackGround::TitleBackGround()
{
}

TitleBackGround::~TitleBackGround()
{
}

void TitleBackGround::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	CreateRenderer("MainTitle.bmp");
}

void TitleBackGround::Render()
{
	DebugRectRender();
}
