#include "GameOverLevel.h"
#include "BackGround.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

GameOverLevel::GameOverLevel()
	:Time_(5.0f)
{
}

GameOverLevel::~GameOverLevel()
{
}

void GameOverLevel::Loading()
{
}

void GameOverLevel::Update()
{
	Time_ -= GameEngineTime::GetDeltaTime();
	if (Time_ <= 0)
	{
		GameEngine::GetInst().ChangeLevel("TitleMain");
	}
}

void GameOverLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	GameEngineSound::SoundPlayOneShot("SnowBros_GameOver_Track.mp3",0);
	Time_ = 5.0f;
	{
		BackGround* Actor = CreateActor<BackGround>(0);
		Actor->GetRenderer()->CreateAnimation("GameOver.bmp", "GameOver", 0, 3, 0.3f, false);
		Actor->GetRenderer()->ChangeAnimation("GameOver");
		Actor->GetRenderer()->SetPivot(GameEngineWindow::GetScale().Half());
	}
}

void GameOverLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Reset();
}
