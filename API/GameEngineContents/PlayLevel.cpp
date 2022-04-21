#include "PlayLevel.h"
#include "BackGround.h"
#include "Nick.h"
#include "Monster.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Loading()
{
	BackGround* Back = CreateActor<BackGround>(0);
	Back->GetRenderer()->SetImage("floor01.bmp");

	CreateActor<Nick>((int)ORDER::PLAYER, "Player");
	//CreateActor<Monster>((int)ORDER::MONSTER, "Monster");
}

void PlayLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GameEngine::GetInst().ChangeLevel("Ending");
	}
}

void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
