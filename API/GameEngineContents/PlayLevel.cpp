#include "PlayLevel.h"
#include "BackGround.h"
#include "Player.h"
#include "Monster.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>

enum class ORDER
{
	BACKGROUND,
	PLAYER,
	MONSTER,
};

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

	CreateActor<Player>((int)ORDER::PLAYER, "Player");
	//CreateActor<Monster>((int)ORDER::MONSTER, "Monster");
}

void PlayLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Ending");
	}
}

void PlayLevel::LevelChangeStart()
{
}
