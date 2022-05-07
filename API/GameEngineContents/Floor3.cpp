#include "Floor3.h"
#include "BackGround.h"
#include "FloorLogo.h"
#include "PlayUI.h"
#include "Life.h"
#include "Score.h"
#include "Nick.h"
#include "Frog.h"
#include "YellowTroll.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Floor3::Floor3()
	: LogoTime_(2.0f)
	, NextFloorTime_(5.0f)
	, LogoShow_(true)
{
}

Floor3::~Floor3()
{
}

void Floor3::Loading()
{
	
}

void Floor3::Update()
{
	if (1 == Enemycount_)
	{
		NextFloorTime_ -= GameEngineTime::GetDeltaTime();
		if (NextFloorTime_ <= 0)
		{
			GameEngine::GetInst().ChangeLevel("BossEnterLevel");
		}
	}

	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GameEngine::GetInst().ChangeLevel("BossEnterLevel");
	}
	if (true == GameEngineInput::GetInst()->IsDown("Debug"))
	{
		GameEngineLevel::IsDebugModeSwitch();
	}
}

void Floor3::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	{
		BackGround* Actor = CreateActor<BackGround>(0);
		Actor->GetRenderer()->SetImage("Floor3.bmp");

		float4 BackActor = {};
		BackActor.x = (Actor->GetRenderer()->GetImage()->GetScale().Half().x);
		BackActor.y = (Actor->GetRenderer()->GetImage()->GetScale().Half().y);

		Actor->GetRenderer()->SetPivot(BackActor);
	}

	{
		PlayUI* Actor = CreateActor<PlayUI>(0);

		LifeUI = CreateActor<Life>(1);
		ScoreUI = CreateActor<Score>(1);
	}

	{
		Nick* Player = CreateActor<Nick>(10);
		Player->SetPosition({ 400,727 });
	}

	{
		// 시간 맞춰주기
		Frog* Frog0 = CreateActor<Frog>((int)ORDER::MONSTER);
		Frog0->SetPosition({ 60,0 });

		YellowTroll* YellowTroll0 = CreateActor<YellowTroll>((int)ORDER::MONSTER);
		YellowTroll0->SetPosition({ 130,0 });

		YellowTroll* YellowTroll1 = CreateActor<YellowTroll>((int)ORDER::MONSTER);
		YellowTroll1->SetPosition({ 210,0 });

		YellowTroll* YellowTroll2 = CreateActor<YellowTroll>((int)ORDER::MONSTER);
		YellowTroll2->SetPosition({ 510,0 });

		Enemycount_ = 5;
	}
}

void Floor3::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Nick::BgmPlayer_.Stop();
	Reset();
}
