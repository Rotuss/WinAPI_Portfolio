#include "BossEnterLevel.h"
#include "BackGround.h"
#include "FloorLogo.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

BossEnterLevel::BossEnterLevel()
	: Time_(4.0f)
{
}

BossEnterLevel::~BossEnterLevel()
{
}

void BossEnterLevel::Loading()
{
	}

void BossEnterLevel::Update()
{
	Time_ -= GameEngineTime::GetDeltaTime();
	if (Time_ <= 0)
	{
		GameEngine::GetInst().ChangeLevel("BossFloor");
	}
}

void BossEnterLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	GameEngineSound::SoundPlayOneShot("SnowBros_BossFloorEnter_Track.mp3", 0);
	Time_ = 4.0f;
	BackGround* Actor = CreateActor<BackGround>(0);
	Actor->GetRenderer()->CreateAnimation("BossStageEnter.bmp", "BossStageEnter", 0, 2, 0.3f, false);
	Actor->GetRenderer()->ChangeAnimation("BossStageEnter");

	Actor->GetRenderer()->SetPivot(GameEngineWindow::GetScale().Half());
}

void BossEnterLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}
