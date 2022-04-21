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
		//Actor->GetRenderer()->SetImage("MainTitle.bmp");

		//float4 BackActor = {};
		//BackActor.x = (Actor->GetRenderer()->GetImage()->GetScale().Half().x);
		//BackActor.y = (Actor->GetRenderer()->GetImage()->GetScale().Half().y);
		//Actor->GetRenderer()->SetPivot(BackActor);
	}
}

void TitleMainLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("TitleSelect"))
	{
		GameEngine::GetInst().ChangeLevel("TitleSelect");
	}
}

void TitleMainLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
}

void TitleMainLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
}
