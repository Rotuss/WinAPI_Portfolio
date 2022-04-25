#include "Floor2.h"
#include "BackGround.h"
#include "PlayUI.h"
#include "Nick.h"
#include "ContentsEnums.h"
#include "PlayUI.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Floor2::Floor2()
{
}

Floor2::~Floor2()
{
}

void Floor2::Loading()
{
	{
		BackGround* Actor = CreateActor<BackGround>(0);
		Actor->GetRenderer()->SetImage("Floor2.bmp");

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
		Player->SetPosition({ 400,725 });
	}
}

void Floor2::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GameEngine::GetInst().ChangeLevel("Floor1");
	}
	if (true == GameEngineInput::GetInst()->IsDown("Debug"))
	{
		GameEngineLevel::IsDebugModeSwitch();
	}
}

void Floor2::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void Floor2::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
