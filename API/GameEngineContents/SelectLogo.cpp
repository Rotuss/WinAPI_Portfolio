#include "SelectLogo.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>

SelectLogo::SelectLogo()
{
}

SelectLogo::~SelectLogo()
{
}

void SelectLogo::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half() - float4{ 315,-305 });
	CreateRenderer("SelectUIIcon.bmp");
}

void SelectLogo::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Left"))
	{
		SetPosition(GameEngineWindow::GetScale().Half() - float4{ 315,-305 });
		CreateRenderer("SelectUIIcon.bmp");
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Right"))
	{
		SetPosition(GameEngineWindow::GetScale().Half() - float4{ 0,-305 });
		CreateRenderer("SelectUIIcon.bmp");
	}
	
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GameEngine::GetInst().ChangeLevel("Floor1");
	}
}
