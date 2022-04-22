#include "TitleMainLevel.h"
#include "TitleBackGround.h"
#include "TitleLogo.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

TitleMainLevel::TitleMainLevel()
{
}

TitleMainLevel::~TitleMainLevel()
{
}

void TitleMainLevel::Loading()
{
	{
		CreateActor<TitleBackGround>(0, "TitleBackGround");
		CreateActor<TitleLogo>(1, "TitleLogo");
	}
}

void TitleMainLevel::Update()
{
}

void TitleMainLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
}

void TitleMainLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
}
