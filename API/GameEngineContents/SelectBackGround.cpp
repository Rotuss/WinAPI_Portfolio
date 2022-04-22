#include "SelectBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>

SelectBackGround::SelectBackGround()
{
}

SelectBackGround::~SelectBackGround()
{
}

void SelectBackGround::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	CreateRenderer("SelectTitle.bmp");
}

void SelectBackGround::Render()
{
}
