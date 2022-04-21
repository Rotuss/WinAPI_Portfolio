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
	{
		SetPosition(GameEngineWindow::GetScale().Half());
		CreateRenderer("MainTitle.bmp");
	}
}

void TitleBackGround::Render()
{
	if (true == GameEngineInput::GetInst()->IsPress("TitleSelect"))
	{
		SetPosition(GameEngineWindow::GetScale().Half());
		CreateRenderer("SelectTitle.bmp");
	}
	DebugRectRender();
}
