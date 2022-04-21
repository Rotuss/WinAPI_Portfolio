#include "TitleSelectLevel.h"
#include "TitleBackGround.h"
#include "TitleLogo.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

TitleSelectLevel::TitleSelectLevel()
{
}

TitleSelectLevel::~TitleSelectLevel()
{
}

void TitleSelectLevel::Loading()
{
	{
		CreateActor<TitleBackGround>(0, "TitleBackGround");
		CreateActor<TitleLogo>(1, "TitleLogo");
	}
}

void TitleSelectLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Floor1"))
	{
		GameEngine::GetInst().ChangeLevel("Floor1");
	}
}

void TitleSelectLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
}

void TitleSelectLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
}
