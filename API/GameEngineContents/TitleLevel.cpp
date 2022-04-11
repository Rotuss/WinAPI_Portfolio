#include "TitleLevel.h"
#include "TitleBackGround.h"
#include "TitleLogo.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Loading()
{
	CreateActor<TitleBackGround>(0);
	CreateActor<TitleLogo>(1);
}

void TitleLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GameEngine::GetInst().ChangeLevel("Floor1");
	}
}
