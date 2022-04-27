#include "Floor2.h"
#include "BackGround.h"
#include "PlayUI.h"
#include "Nick.h"
#include "RedDemon.h"
#include "Frog.h"
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
	}

	{
		PlayUI* Actor = CreateActor<PlayUI>(0);
	}

	{
		Nick* Player = CreateActor<Nick>((int)ORDER::PLAYER, "Player");
		Player->SetPosition({ 400,710 });
	}

	{
		RedDemon* RedDemon0 = CreateActor<RedDemon>((int)ORDER::MONSTER);
		RedDemon0->SetPosition({ 420,600 });

		RedDemon* RedDemon1 = CreateActor<RedDemon>((int)ORDER::MONSTER);
		RedDemon1->SetPosition({ 50,472 });

		RedDemon* RedDemon2 = CreateActor<RedDemon>((int)ORDER::MONSTER);
		RedDemon2->SetPosition({ 975,472 });

		Frog* Frog0 = CreateActor<Frog>((int)ORDER::MONSTER);
		Frog0->SetPosition({ 320,340 });

		Frog* Frog1 = CreateActor<Frog>((int)ORDER::MONSTER);
		Frog1->SetPosition({ 704,340 });
	}
}

void Floor2::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GameEngine::GetInst().ChangeLevel("Floor3");
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
