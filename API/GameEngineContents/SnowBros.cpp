#include "SnowBros.h"
#include "TitleLevel.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

SnowBros::SnowBros()
{}

SnowBros::~SnowBros()
{}

void SnowBros::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });
	
	GameEngineImageManager::GetInst()->Load("C:\\AR40th\\WinAPI_Portfolio\\API\\Resources\\Image\\Nick_Idle.bmp", "Nick_Idle.bmp");
	
	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Play");
}

void SnowBros::GameLoop()
{
}

void SnowBros::GameEnd()
{
}
