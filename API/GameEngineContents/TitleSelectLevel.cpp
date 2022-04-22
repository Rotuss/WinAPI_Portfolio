#include "TitleSelectLevel.h"
#include "SelectBackGround.h"
#include "SelectLogo.h"
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
		CreateActor<SelectBackGround>(0, "SelectBackGround");
		CreateActor<SelectLogo>(1, "SelectLogo");
	}
}

void TitleSelectLevel::Update()
{
}

void TitleSelectLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
}

void TitleSelectLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
}
