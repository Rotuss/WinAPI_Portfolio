#include "BossFloor.h"
#include "BackGround.h"
#include "FloorLogo.h"
#include "PlayUI.h"
#include "Life.h"
#include "Score.h"
#include "Nick.h"
#include "Boss.h"
#include "ContentsEnums.h"
#include "PlayUI.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

BossFloor::BossFloor()
{
}

BossFloor::~BossFloor()
{
}

void BossFloor::Loading()
{
}

void BossFloor::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Debug"))
	{
		GameEngineLevel::IsDebugModeSwitch();
	}
}

void BossFloor::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Nick::BgmPlayer_ = GameEngineSound::SoundPlayControl("SnowBros_BossFloor_Track.mp3");
	{
		BackGround* Actor = CreateActor<BackGround>(0);
		Actor->GetRenderer()->SetImage("FloorBoss.bmp");

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
		Boss* Boss1 = CreateActor<Boss>((int)ORDER::BOSS);
		Boss1->SetPosition({ 800,0 });

		Enemycount_ = 2;
	}
}

void BossFloor::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Nick::BgmPlayer_.Stop();
	Reset();
}
