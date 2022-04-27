#include "BossFloor.h"
#include "BackGround.h"
#include "FloorLogo.h"
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

BossFloor::BossFloor()
	:BgmPlayTime_(4.0f)
{
}

BossFloor::~BossFloor()
{
}

void BossFloor::Loading()
{
	BackGround* Actor = CreateActor<BackGround>(0);
	Actor->GetRenderer()->CreateAnimation("BossStageEnter.bmp", "BossStageEnter", 0, 2, 0.3f, false);
	Actor->GetRenderer()->ChangeAnimation("BossStageEnter");

	Actor->GetRenderer()->SetPivot(GameEngineWindow::GetScale().Half());
}

void BossFloor::Update()
{
	BgmPlayTime_ -= GameEngineTime::GetDeltaTime();
	if (BgmPlayTime_ <= 0)
	{
		// 소리가 이상함. Nick 만들면 BgmPlayer_ 수정할 것
		//BgmPlayer_ = GameEngineSound::SoundPlayControl("SnowBros_BossStage_Theme1.mp3");
		BackGround* Actor = CreateActor<BackGround>(1);
		Actor->GetRenderer()->SetImage("FloorBoss.bmp");

		float4 BackActor = {};
		BackActor.x = (Actor->GetRenderer()->GetImage()->GetScale().Half().x);
		BackActor.y = (Actor->GetRenderer()->GetImage()->GetScale().Half().y);

		Actor->GetRenderer()->SetPivot(BackActor);
	}

	if (true == GameEngineInput::GetInst()->IsDown("Debug"))
	{
		GameEngineLevel::IsDebugModeSwitch();
	}
}

void BossFloor::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//GameEngineSound::SoundPlayOneShot("SnowBros_BossStageEnter_Theme.mp3", 0);
}

void BossFloor::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
