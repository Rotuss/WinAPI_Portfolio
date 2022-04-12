#include "Floor1.h"
#include "BackGround.h"
#include "PlayUI.h"
#include "Nick.h"
#include "ContentsEnums.h"
#include "PlayUI.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Floor1::Floor1()
{
}

Floor1::~Floor1()
{
}

void Floor1::Loading()
{
	{
		BackGround* Actor = CreateActor<BackGround>(0);
		Actor->GetRenderer()->SetImage("floor01.bmp");

		float4 BackActor = {};
		BackActor.x = (Actor->GetRenderer()->GetImage()->GetScale().Half().x);
		BackActor.y = (Actor->GetRenderer()->GetImage()->GetScale().Half().y);

		Actor->GetRenderer()->SetPivot(BackActor);
		Actor->CreateCollision("Next", { 100, 100 }, { 200, -300 });
		Actor->CreateCollision("Wall", { 100, 100 }, { 0, 0 });
	}

	{
		PlayUI* Actor = CreateActor<PlayUI>(0);
	}

	{
		Nick* Player = CreateActor<Nick>((int)ORDER::PLAYER, "Player");
		Player->SetPosition({100.0f, 100.0f});
	}
}

void Floor1::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GameEngine::GetInst().ChangeLevel("Floor2");
	}
}

void Floor1::LevelChangeStart()
{
}
